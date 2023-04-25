// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PointLight.h"
#include "Components/PointLightComponent.h"


//////////////////////////////////////////////////////////////////////////
// AGameCharacter

AGameCharacter::AGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	GetCapsuleComponent()->bHiddenInGame = false;

	// set our turn rate for input
	TurnRateGamepad = 50.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 60.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->MaxWalkSpeedCrouched = 300.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SocketOffset = FVector3d(0.0f, 0.0f, 300.0f);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	FollowCamera->SetRelativeRotation(FQuat(0.0f, -30.0f, 0.0f, 0.0f));

	//Throwable spawn reference
	ThrowableReferenceComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ThrowableRef"));
	ThrowableReferenceComponent->SetupAttachment(RootComponent);
	ThrowableReferenceComponent->SetRelativeLocation(FVector(40.0f, 0.0f, 50.0f));

	//Spline reference
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("PreditionPath"));
	SplineComponent->SetupAttachment(RootComponent);



	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	// Additional Logic

	// for crouching logic
	bIsCrouching = false;

	// for throwing logic
	bIsAiming = false;

	ThrowForce = 800.0f;

	RockAmount = 0;

	DetectionRate = 0.25f;

	ViewTargets.SetNum(5);
	ViewTargets.Insert(TEXT("Head"), 0);
	ViewTargets.Insert(TEXT("LeftHand"), 1);
	ViewTargets.Insert(TEXT("LeftFoot"), 2);
	ViewTargets.Insert(TEXT("RightHand"), 3);
	ViewTargets.Insert(TEXT("RightFoot"), 4);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AGameCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AGameCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AGameCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &AGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AGameCharacter::TouchStopped);
}

void AGameCharacter::Tick(float _DeltaSeconds)
{
	Super::Tick(_DeltaSeconds);

	bIsVisibleInLight = false;

	for (AActor* Actor : PointLights) {
		APointLight* PointLight = Cast<APointLight>(Actor);

		if (PointLight) {

			float Distance = (PointLight->GetActorLocation() - this->GetActorLocation()).Size();

			if (Distance < PointLight->PointLightComponent->AttenuationRadius) {
				FCollisionQueryParams QueryParams;
				QueryParams.AddIgnoredActor(this);
				QueryParams.bTraceComplex = true;

				FHitResult Hit;
				if (!GetWorld()->LineTraceSingleByChannel(Hit, this->GetActorLocation(), PointLight->GetActorLocation(), ECC_Visibility, QueryParams)) {
					//we are visible in the light!
					bIsVisibleInLight = true;
					break;
				}
			}
		}
	}
}

void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, APointLight::StaticClass(), PointLights);
}

void AGameCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void AGameCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void AGameCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AGameCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AGameCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGameCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AGameCharacter::ClickCrouch()
{
	if (!bIsCrouching) {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("Crouch!")));
		Crouch(true);
		bIsCrouching = true;
	}
	else {
		UnCrouch();
		bIsCrouching = false;
	}
}

int32 AGameCharacter::GetRockAmount()
{
	return RockAmount;
}

void AGameCharacter::SetRockAmount(int32 _Amount)
{
	RockAmount = _Amount;
}

// custom view target for AI Perception
bool AGameCharacter::CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor, const bool* bWasVisible, int32* UserData) const
{
	static const FName NAME_AILineOfSight = FName(TEXT("TestPawnLineOfSight"));

	FHitResult HitResult;

	for (int32 i = 0; i < ViewTargets.Num(); i++) {

		FVector SocketLocation = GetMesh()->GetSocketLocation(ViewTargets[i]);

		const bool bHitSocket = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, SocketLocation,
			FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));


		NumberOfLoSChecksPerformed++;

		if (bHitSocket == false || (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsOwnedBy(this)))
		{
			OutSeenLocation = SocketLocation;
			OutSightStrength = 1;
			return true;
		}

		const bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, ObserverLocation, GetActorLocation(),
			FCollisionObjectQueryParams(ECC_TO_BITFIELD(ECC_WorldStatic) | ECC_TO_BITFIELD(ECC_WorldDynamic)), FCollisionQueryParams(NAME_AILineOfSight, true, IgnoreActor));

		NumberOfLoSChecksPerformed++;

		if (bHit == false || (HitResult.GetActor() != nullptr && HitResult.GetActor()->IsOwnedBy(this)))
		{
			OutSeenLocation = GetActorLocation();
			OutSightStrength = 1;
			return true;
		}
	}

	OutSightStrength = 0;
	return false;
}

void AGameCharacter::NextViewTarget()
{
	Index < ViewTargets.Num() - 1 ? Index++ : Index = 0;
	TargetBone = ViewTargets[Index];
}
