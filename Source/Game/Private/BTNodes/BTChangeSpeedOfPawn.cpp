// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNodes/BTChangeSpeedOfPawn.h"
#include "Enemy/Patrol/AiEnemyPatrolController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTChangeSpeedOfPawn::UBTChangeSpeedOfPawn()
{
	NodeName = "Change Speed of Pawn";
}

EBTNodeResult::Type UBTChangeSpeedOfPawn::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory)
{
	//change movement speed of pawn
	const APawn* AIPawn{ _OwnerComp.GetAIOwner()->GetPawn() };
	UCharacterMovementComponent* AIPawnMovementComp = Cast<UCharacterMovementComponent>(AIPawn->GetMovementComponent());
	AIPawnMovementComp->MaxWalkSpeed = Speed;

	FinishLatentTask(_OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBTChangeSpeedOfPawn::GetStaticDescription() const
{
	return FString::Printf(TEXT("The Value of Speed is: %s"), *FString::SanitizeFloat(Speed));
}
