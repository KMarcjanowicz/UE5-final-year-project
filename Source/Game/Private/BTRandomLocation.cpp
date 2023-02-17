// Fill out your copyright notice in the Description page of Project Settings.


#include "BTRandomLocation.h"
#include "AIRandomController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTRandomLocation::UBTRandomLocation()
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTRandomLocation::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	FNavLocation Location{};

	AAIRandomController* AIController = Cast<AAIRandomController>(_OwnerComp.GetAIOwner());

	if (AIController) {

		//get AI Pawn
		const APawn* AIPawn { AIController->GetPawn() };

		//get origin location
		const FVector OriginLocation { AIPawn->GetActorLocation() };

		//Navigation system
		const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };


		if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(OriginLocation, SearchRadius, Location))
		{
		//Black Board comp get it
		UBlackboardComponent* BlackBoardComp = AIController->GetBlackboardComp();

		BlackBoardComp->SetValueAsVector("LocationToGo", Location.Location);
		}
		
		//Signal the behaviour tree comp
		FinishLatentTask(_OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}