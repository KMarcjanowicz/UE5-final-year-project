// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTChangeSpeedOfPawn.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTChangeSpeedOfPawn : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTChangeSpeedOfPawn();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float Speed;

	virtual FString GetStaticDescription() const override;
};
