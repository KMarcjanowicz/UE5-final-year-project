// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AiEnemyController.h"
#include "Enemy/AiEnemyCharacter.h"
#include "../../GameCharacter.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

void AAiEnemyController::BeginPlay()
{
	Super::BeginPlay();

	AAiEnemyCharacter* tmp = Cast<AAiEnemyCharacter>(GetPawn());

	if(tmp) {
		Agent = tmp;
	}
}

AAiEnemyController::AAiEnemyController(const FObjectInitializer& _ObjectInitializer)
{
	// Setup the perception component
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	Sight->SightRadius = 1000.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 70.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	//register the sight sense to the perception component
	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->SetDominantSense(Sight->GetSenseImplementation());

	/* initialize the BB and BT components*/
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAiEnemyController::OnPerception(AActor* _Actor, FAIStimulus _Stimulus)
{
	AGameCharacter* Chr = Cast<AGameCharacter>(_Actor);
	if (Chr == nullptr) { return;}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "I see you!");
	SetFocus(_Stimulus.WasSuccessfullySensed() ? Chr : nullptr);
}

void AAiEnemyController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	/* get reference to character */

	if (Agent) {
		if (Agent->BehaviorTree->BlackboardAsset) {
			BlackboardComp->InitializeBlackboard(*(Agent->BehaviorTree->BlackboardAsset));
		}
		BehaviorTreeComp->StartTree(*Agent->BehaviorTree);
	}

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAiEnemyController::OnPerception);
}
