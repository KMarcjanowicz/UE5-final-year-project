// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/AiEnemyCharacter.h"
#include "AiEnemyPatrolCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAiEnemyPatrolCharacter : public AAiEnemyCharacter
{
	GENERATED_BODY()
	
public:
	/* array of actor points for the AI logic */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> PatrolPoints;

	FORCEINLINE TArray<AActor*> GetPatrolPoints() const { return PatrolPoints; };
};
