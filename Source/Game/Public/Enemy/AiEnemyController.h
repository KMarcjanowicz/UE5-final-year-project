// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "AiEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAiEnemyController : public AAIController
{
	GENERATED_BODY()

protected:

	/* Perception Component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UAIPerceptionComponent* PerceptionComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	AAiEnemyController(const FObjectInitializer& _ObjectInitializer);

	/* Character to control */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class AAiEnemyCharacter* Agent;

	UFUNCTION()
		void OnPerception(AActor* _Actor, FAIStimulus _Stimulus);

	/* A Sight Sense */
	class UAISenseConfig_Sight* Sight;

	virtual void OnPossess(APawn* _InPawn) override;

};
