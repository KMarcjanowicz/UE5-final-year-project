// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "../Interfaces/SightPerceptionInterface.h"
#include "AiEnemyController.generated.h"


UENUM()
enum class EAIStates : uint8 {
	S_Normal		UMETA(DisplayName = "Normal"),
	S_Investigate	UMETA(DisplayName = "Investigate"),
	S_Chase			UMETA(DisplayName = "Chase")
};

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

	virtual void OnPossess(APawn* _InPawn) override;


	/* Inline getter functions */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; };
	FORCEINLINE UBehaviorTreeComponent* GetBehaviourTree() const { return BehaviorTreeComp; };

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "StimuliInterface")
		void InvestigateOnSight(); virtual void InvestigateOnSight_Implementation() override;
};
