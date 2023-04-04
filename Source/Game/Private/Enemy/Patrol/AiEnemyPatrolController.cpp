// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Patrol/AiEnemyPatrolController.h"
#include "Enemy/Patrol/AiEnemyPatrolCharacter.h"

void AAiEnemyPatrolController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	AAiEnemyPatrolCharacter* PatrolAgent = Cast<AAiEnemyPatrolCharacter>(Agent);

	PatrolPoints = PatrolAgent->GetPatrolPoints();
	CurrentPatrolPoint = 0;

}