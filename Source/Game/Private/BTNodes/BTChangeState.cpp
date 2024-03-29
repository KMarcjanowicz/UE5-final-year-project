// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNodes/BTChangeState.h"
#include "AIController.h"
#include "Enemy/AiEnemyController.h"



UBTChangeState::UBTChangeState()
{
	NodeName = "Change State of Pawn";
}

EBTNodeResult::Type UBTChangeState::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	//cast to custom controller
	AAiEnemyController* AIController = Cast<AAiEnemyController>(_OwnerComp.GetAIOwner());

	if (AIController) {
		AIController->SetAIState(State);
		FinishLatentTask(_OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}

FString UBTChangeState::GetStaticDescription() const
{
	return FString::Printf(TEXT("Current State: %s"), *State);
}
