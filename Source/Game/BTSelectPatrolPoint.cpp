// Fill out your copyright notice in the Description page of Project Settings.

#include "BTSelectPatrolPoint.h"
#include "Game.h"
#include "AIPatrolPoint.h"
#include "AIPatrolController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	AAIPatrolController* AIController = Cast<AAIPatrolController>(_OwnerComp.GetAIOwner());

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

		BlackBoardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
