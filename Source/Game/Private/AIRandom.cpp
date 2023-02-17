// Fill out your copyright notice in the Description page of Project Settings.


#include "AIRandom.h"
#include "AIRandomController.h"
#include "Perception/PawnSensingcomponent.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
AAIRandom::AAIRandom()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.0f);
}

// Called when the game starts or when spawned
void AAIRandom::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp) {
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AAIRandom::OnPlayerCaught);
	}
}

// Called every frame
void AAIRandom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAIRandom::OnPlayerCaught(APawn* _Pawn)
{
	/* Get the reference to the player controller */
	AAIRandomController* AIController = Cast<AAIRandomController>(GetController());

	if (AIController) {
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("You have been caught!"));
		AIController->SetPlayerCaught(_Pawn);
	}
}

// Called to bind functionality to input
void AAIRandom::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

