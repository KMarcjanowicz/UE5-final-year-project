// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AiEnemyController.h"
#include "Enemy/AiEnemyCharacter.h"
#include "../../GameCharacter.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h"
#include "Runtime/AIModule/Classes/Perception/AISenseConfig_Hearing.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionTypes.h"
#include "GenericPlatform/GenericPlatformMath.h"

void AAiEnemyController::BeginPlay()
{
	Super::BeginPlay();
	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerRef = Cast<AGameCharacter>(Player);
}

void AAiEnemyController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DistanceToTarget = FVector::Dist(Agent->GetActorLocation(), PlayerRef->GetActorLocation());

	if (BlackboardComp->GetValueAsFloat(AlarmedFloatKey) != AlarmedPercentage) {
		BlackboardComp->SetValueAsFloat(AlarmedFloatKey, AlarmedPercentage);
	}
	
	if (bSeesTarget)
	{
		if (AlarmedPercentage < 100.0f) {
			AlarmedPercentage += 1 * PlayerRef->GetDetectionRate() * 100 * 1/DistanceToTarget;
		}
		else {
			AlarmedPercentage = 100.0f;
		}
	}
	else if (!bIsInvestigating) {
		if (AlarmedPercentage > 0.0f) {
			AlarmedPercentage -= 1 * 100 * 1/DistanceToTarget;
		}
		else {
			AlarmedPercentage = 0;
		}
	}
	



	Agent->AlarmedLabelComp->SetText(FText::AsNumber(FGenericPlatformMath::RoundToInt(AlarmedPercentage)));
}

AAiEnemyController::AAiEnemyController(const FObjectInitializer& _ObjectInitializer)
{
	// Setup the perception component
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	Hearing = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));

	Sight->SightRadius = 750.0f;
	Sight->LoseSightRadius = Sight->SightRadius + 500.0f;
	Sight->PeripheralVisionAngleDegrees = 45.0f;
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	Hearing->HearingRange = 1250.0f;
	Hearing->DetectionByAffiliation.bDetectEnemies = true;
	Hearing->DetectionByAffiliation.bDetectFriendlies = true;
	Hearing->DetectionByAffiliation.bDetectNeutrals = true;

	//register the sight and hearing sense to the perception component
	PerceptionComp->ConfigureSense(*Sight);
	PerceptionComp->ConfigureSense(*Hearing);
	PerceptionComp->SetDominantSense(Sight->GetSenseImplementation());



	/* initialize the BB and BT components*/
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

	/* initialize the keys */
	LocationToGoKey = "LocationToGo";
	PlayerKey = "Target";
	InvestigatingState = "bIsInvestigating";
	SeeTarget = "bSeesTarget";
	LastKnownLocation = "LastKnownLocation";
	AlarmedFloatKey = "CautionRate";

	/* stimuli ID */
	SightID = Sight->GetSenseID();
	HearingID = Hearing->GetSenseID();
}

void AAiEnemyController::OnPerception(AActor* _Actor, FAIStimulus _Stimulus)
{
	if (_Stimulus.Type == SightID) {

		if (_Actor->ActorHasTag(TEXT("Door"))) {

		}
		//cast to the pawn that caused the stimulus
		AGameCharacter* Chr = Cast<AGameCharacter>(_Actor);
		//escape the sight function if the visible target wasn't player
		if (Chr == nullptr) { return; }

		bIsInvestigating = true;

		if (bSeesTarget)
		{
			bSeesTarget = false;
		}
		else {
			bSeesTarget = true;
		}

		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("Sight!")));

		//Set the location of the stimulus into the black board
		BlackboardComp->SetValueAsVector(LastKnownLocation, _Stimulus.StimulusLocation);
		//Make AI investigate
		//turn the investigation boolean true only if sense pawn
		//false will need to be triggered by the node in the behaviour tree after investigation
		if (_Stimulus.WasSuccessfullySensed()) {
			BlackboardComp->SetValueAsBool(InvestigatingState, _Stimulus.WasSuccessfullySensed());
			BlackboardComp->SetValueAsObject(PlayerKey, Chr);
			BlackboardComp->SetValueAsBool(SeeTarget, true);
			SetFocus(_Stimulus.WasSuccessfullySensed() ? Chr : nullptr);
		}
		else {
			BlackboardComp->SetValueAsBool(SeeTarget, false);
			K2_ClearFocus();
		}
	}
	else if (_Stimulus.Type == HearingID) {

		bIsInvestigating = true;
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Yellow, FString::Printf(TEXT("Hearing!")));

		AlarmedPercentage += 10.0f;
		if (AlarmedPercentage > 100.0f) {
			AlarmedPercentage = 100.0f;
		}

		BlackboardComp->SetValueAsVector(LastKnownLocation, _Stimulus.StimulusLocation);

		//to reset the investigation task?
		if (_Stimulus.WasSuccessfullySensed()) {
			BlackboardComp->SetValueAsBool(InvestigatingState, false);
		}
		BlackboardComp->SetValueAsBool(InvestigatingState, _Stimulus.WasSuccessfullySensed());
		
	}
}

void AAiEnemyController::OnPossess(APawn* _InPawn)
{
	Super::OnPossess(_InPawn);

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("Possessed")));

	Agent = Cast<AAiEnemyCharacter>(GetPawn());
	Index = Agent->Index;

	if (Agent) {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("Agent is valid")));
		if (Agent->BehaviorTree->BlackboardAsset) {
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("Blackboard init")));
			BlackboardComp->InitializeBlackboard(*(Agent->BehaviorTree->BlackboardAsset));
		}
		BehaviorTreeComp->StartTree(*Agent->BehaviorTree);
	}

	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAiEnemyController::OnPerception);
}

void AAiEnemyController::InvestigateOnSight_Implementation()
{
	BlackboardComp->SetValueAsBool(InvestigatingState, false);
	bIsInvestigating = false;
}

void AAiEnemyController::SetAIState(FString _State)
{
	if (State != _State) {
		State = _State;
		Agent->ChangeTextOnLabel(_State);
	}
}
