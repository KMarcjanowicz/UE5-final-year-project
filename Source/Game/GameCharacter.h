// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "Perception/AISightTargetInterface.h"
#include "Components/ChildActorComponent.h"
#include "Components/SplineComponent.h"
#include "GameCharacter.generated.h"

UCLASS(config=Game)
class AGameCharacter : public ACharacter, public IAISightTargetInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	/** First Person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FPCamera;

	/** component from which position's the throwable grenade will be spawned */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	class UChildActorComponent* ThrowableReferenceComponent;

	/** component from which the prediction of the path will be made*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = "true"))
	class USplineComponent* SplineComponent;

public:
	AGameCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	//Array of PointLight actors
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
	TArray<AActor*> PointLights;

	//Integer keeping track of how many rocks the player has in the inv
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
	int32 RockAmount;

protected:

	/* For visibility in lights */
	UPROPERTY(BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
	bool bIsVisibleInLight;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

	virtual void Tick(float _DeltaSeconds) override;

	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION()
	void ClickCrouch();

	UFUNCTION(BlueprintCallable)
	int32 GetRockAmount();

	UFUNCTION(BlueprintCallable)
	void SetRockAmount(int32 _Amount);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AimThrowObject();


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI)
		bool bIsCrouching;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		bool bIsAiming;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float ThrowForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		float DetectionRate;

	/* function to check multiple bones in the character */
	virtual bool CanBeSeenFrom(const FVector& ObserverLocation, FVector& OutSeenLocation, int32& NumberOfLoSChecksPerformed, float& OutSightStrength, const AActor* IgnoreActor = nullptr, const bool* bWasVisible = nullptr, int32* UserData = nullptr) const;

public:

	/** Current Target Bone */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName TargetBone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AI, meta = (AllowPrivateAccess = "true"))
		/* Array of Important bones */
		TArray<FName> ViewTargets;

	UFUNCTION()
	void NextViewTarget();

	int32 Index;
};

