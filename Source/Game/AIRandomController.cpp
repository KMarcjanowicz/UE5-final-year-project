// Fill out your copyright notice in the Description page of Project Settings.


#include "AIRandomController.h"
#include "AIRandom.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

AAIRandomController::AAIRandomController()
{
	/* initialize the BB and BT components*/
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	/* initialize the keys */
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";
}

void AAIRandomController::SetPlayerCaught(APawn* _Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, _Pawn);
	}
}

void AAIRandomController::BeginPlay()
{
	Super::BeginPlay();
}

void AAIRandomController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	/* get reference to character */
	AAIRandom* AICharacter = Cast<AAIRandom>(_InPawn);

	if (AICharacter) {
		if (AICharacter->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		BehaviorTreeComp->StartTree(*AICharacter->BehaviorTree);
	}
}
