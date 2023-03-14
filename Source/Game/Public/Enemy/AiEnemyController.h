// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
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
class GAME_API AAiEnemyController : public AAIController
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

	UFUNCTION()
		void OnPerception(AActor* _Actor, FAIStimulus _Stimulus);

	/* A Sight Sense */
	class UAISenseConfig_Sight* Sight;

	virtual void OnPossess(APawn* _InPawn) override;


	/* Inline getter functions */
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; };
	FORCEINLINE UBehaviorTreeComponent* GetBehaviourTree() const { return BehaviorTreeComp; };
};
