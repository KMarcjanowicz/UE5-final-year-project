
// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNodes/BTRandomLocation.h"
#include "AIRandomController.h" //-- delete afterwards
#include "Enemy/Patrol/AiEnemyPatrolController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTRandomLocation::UBTRandomLocation()
{
	NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UBTRandomLocation::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	FNavLocation Location{};

	//check if the owner has the correct interface
	if (_OwnerComp.GetAIOwner()->GetClass()->ImplementsInterface(USightPerceptionInterface::StaticClass())) {

		AAiEnemyController* AIController = Cast<AAiEnemyController>(_OwnerComp.GetAIOwner());

		const APawn* AIPawn{ _OwnerComp.GetAIOwner()->GetPawn() };

		//change movement speed of pawn
		UCharacterMovementComponent* AIPawnMovementComp = Cast<UCharacterMovementComponent>(AIPawn->GetMovementComponent());
		AIPawnMovementComp->MaxWalkSpeed = 100.0f;

		//get origin location
		const FVector OriginLocation{ AIPawn->GetActorLocation() };

		//Navigation system
		const UNavigationSystemV1* NavSystem{ UNavigationSystemV1::GetCurrent(GetWorld()) };

		if (IsValid(NavSystem) && NavSystem->GetRandomPointInNavigableRadius(OriginLocation, SearchRadius, Location))
		{
			//Black Board comp get it
			UBlackboardComponent* BlackBoardComp = AIController->GetBlackboardComp();

			BlackBoardComp->SetValueAsVector("LastKnownLocation", Location.Location);
		}

		//Signal the behaviour tree comp
		FinishLatentTask(_OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;	
	}

	return EBTNodeResult::Failed;
}