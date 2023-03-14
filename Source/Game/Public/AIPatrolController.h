// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAIPatrolController : public AAIController
{
	GENERATED_BODY()

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

	/* array of actor points for the AI logic */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> PatrolPoints;

	virtual void OnPossess(APawn* _InPawn) override;

public:
	int32 CurrentPatrolPoint;

public:

	AAIPatrolController();

	void SetPlayerCaught( APawn* _Pawn);

	/* Inline getter functions */

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; };
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; };
	
};
