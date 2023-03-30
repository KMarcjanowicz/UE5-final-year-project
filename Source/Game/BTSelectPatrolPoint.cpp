// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectPatrolPoint.h"
#include "Game.h"
#include "AIPatrolPoint.h"
#include "Public/Enemy/Patrol/AiEnemyPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTSelectPatrolPoint::UBTSelectPatrolPoint() {
	NodeName = TEXT("Select Patrol Point");
}

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	AAiEnemyPatrolController* AIController = Cast<AAiEnemyPatrolController>(_OwnerComp.GetAIOwner());

	if (AIController) {

		/* Get Blackboard component */
		UBlackboardComponent* BlackBoardComp = AIController->GetBlackboardComp();

		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackBoardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*>AvailablePatrolPoints = AIController->GetPatrolPoints();

		AAIPatrolPoint* NextPatrolPoint = nullptr;

		if (AIController->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[++AIController->CurrentPatrolPoint]);
		}
		else //if there is no more points to go point
		{
			NextPatrolPoint = Cast<AAIPatrolPoint>(AvailablePatrolPoints[0]);
			AIController->CurrentPatrolPoint = 0;
		}
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Red, FString::Printf(TEXT("Success")));
		BlackBoardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
