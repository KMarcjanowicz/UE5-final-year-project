// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIRandom.generated.h"

UCLASS()
class GAME_API AAIRandom : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIRandom();

	/* Behaviour tree for AI logic*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UPawnSensingComponent* PawnSensingComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION(BlueprintCallable)
		void OnPlayerCaught(APawn* _Pawn);

};
