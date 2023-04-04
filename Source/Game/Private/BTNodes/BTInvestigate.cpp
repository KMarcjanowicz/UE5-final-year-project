// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNodes/BTInvestigate.h"
#include "Enemy/Patrol/AiEnemyPatrolController.h"
#include "AIPatrolPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UBTInvestigate::UBTInvestigate()
{
	NodeName = TEXT("Investigate");
}

EBTNodeResult::Type UBTInvestigate::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	ISightPerceptionInterface* Interface = Cast<ISightPerceptionInterface>(_OwnerComp.GetAIOwner());

	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("I am invastigating!")));

	if (Interface)
	{
		Interface->Execute_InvestigateOnSight(_OwnerComp.GetAIOwner());

		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("I have finished investigation!")));
		//Signal the behaviour tree comp
		FinishLatentTask(_OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	/*
	*  To determine if an actor implements an interface in both C++ and Blueprints use
	* 
	if (_OwnerComp.GetAIOwner()->GetClass()->ImplementsInterface(USightPerceptionInterface::StaticClass())) {
		ISightPerceptionInterface::Execute_InvestigateOnSight(_OwnerComp.GetAIOwner());
	}
	*/
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("Investigation failed!")));
	return EBTNodeResult::Failed;
}
