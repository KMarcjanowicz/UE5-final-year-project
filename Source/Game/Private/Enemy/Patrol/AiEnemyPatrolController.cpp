// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Patrol/AiEnemyPatrolController.h"

void AAiEnemyPatrolController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	/* initialize the keys */
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";

	CurrentPatrolPoint = 0;
}
