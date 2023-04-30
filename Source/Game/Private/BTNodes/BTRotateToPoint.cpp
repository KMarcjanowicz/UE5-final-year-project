// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNodes/BTRotateToPoint.h"
#include "Enemy/Patrol/AiEnemyPatrolController.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UBTRotateToPoint::UBTRotateToPoint()
{
	NodeName = TEXT("Rotate Pawn to Face Point");
}

EBTNodeResult::Type UBTRotateToPoint::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	AAiEnemyPatrolController* AIController = Cast<AAiEnemyPatrolController>(_OwnerComp.GetAIOwner());

	if (AIController) 
	{
		AIController->AIRotateToPatrolPoint();
		/*
		//get AI Pawn
		const APawn* AIPawn{ AIController->GetPawn() };

		//Black Board comp get it
		UBlackboardComponent* BlackBoardComp = AIController->GetBlackboardComp();

		FRotator NewRotation = AIController->GetCurrentPatrolPoint(AIController->CurrentPatrolPoint)->GetActorRotation();

		NewRotation.Pitch = 0;

		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(AIPawn->GetRootComponent(), AIPawn->GetRootComponent()->GetComponentLocation(), NewRotation, false, false, 0.2f, true,
		EMoveComponentAction::Type::Move, LatentInfo);
		*/

		//Signal the behaviour tree comp
		FinishLatentTask(_OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
