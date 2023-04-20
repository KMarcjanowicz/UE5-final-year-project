// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "../Interfaces/SightPerceptionInterface.h"
#include "AiEnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAiEnemyController : public AAIController, public ISightPerceptionInterface
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Component

	/* Perception Component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UAIPerceptionComponent* PerceptionComp;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FString State;
public:
	AAiEnemyController(const FObjectInitializer& _ObjectInitializer);

	/* Character to control */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class AAiEnemyCharacter* Agent;

	/* Blackboard component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBlackboardComponent* BlackboardComp;

	/* Behavior tree component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BehaviorTreeComp;

	/* keys for the blackboard */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName LocationToGoKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName PlayerKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName LastKnownLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName InvestigatingState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName SeeTarget;

	UFUNCTION()
		void OnPerception(AActor* _Actor, FAIStimulus _Stimulus);

	/* A Sight Sense */
	class UAISenseConfig_Sight* Sight;

	/* A Hearing Sense */
	class UAISenseConfig_Hearing* Hearing;

	/* stimuli ID */
	FAISenseID SightID;
	FAISenseID HearingID;

	/* percentage of how much the enemy is alarmed - PayDay style */
	UPROPERTY(BlueprintReadWrite, Category = AI, meta = (AllowPrivateAccess = "true"))
		float AlarmedPercentage = 0.0f;

	virtual void OnPossess(APawn* _InPawn) override;

	/* Inline getter functions */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; };
	FORCEINLINE UBehaviorTreeComponent* GetBehaviourTree() const { return BehaviorTreeComp; };
	FORCEINLINE FString GetAIState() const { return State; };

	/* Set AI state (also call the function in Character to change the label) */
	UFUNCTION(BlueprintCallable, Category = "AI")
		void SetAIState(FString _State);

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "StimuliInterface")
		void InvestigateOnSight(); virtual void InvestigateOnSight_Implementation() override;



};
