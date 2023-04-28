// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/AiEnemyController.h"
#include "AiEnemyPatrolController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAiEnemyPatrolController : public AAiEnemyController
{
	GENERATED_BODY()

	/* array of actor points for the AI logic */
	UPROPERTY(VisibleAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> PatrolPoints;

public:

	virtual void OnPossess(APawn* _InPawn) override;

	int32 CurrentPatrolPoint;

	/* Inline getter functions */
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; };

};
