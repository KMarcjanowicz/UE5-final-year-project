// Fill out your copyright notice in the Description page of Project Settings.


#include "BTRotateToPoint.h"
#include "AIPatrolController.h"
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
	AAIPatrolController* AIController = Cast<AAIPatrolController>(_OwnerComp.GetAIOwner());

	if (AIController) 
	{
		//get AI Pawn
		const APawn* AIPawn{ AIController->GetPawn() };

		//Black Board comp get it
		UBlackboardComponent* BlackBoardComp = AIController->GetBlackboardComp();

		//get the next location to which the actor will need to go
		AAIPatrolPoint* CurrentPoint = Cast<AAIPatrolPoint>(BlackBoardComp->GetValueAsObject("LocationToGo"));

		FRotator NewRotation = UKismetMathLibrary::FindLookAtRotation(AIPawn->GetActorLocation(), CurrentPoint->GetActorLocation());

		NewRotation.Pitch = 0;

		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		UKismetSystemLibrary::MoveComponentTo(AIPawn->GetRootComponent(), AIPawn->GetActorLocation(), NewRotation, false, false, 0.5f, true,
		EMoveComponentAction::Type::Move, LatentInfo);

		//Signal the behaviour tree comp
		FinishLatentTask(_OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
