// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "AIController.h"
#include "BTChangeState.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTChangeState : public UBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTChangeState();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FString State;

	virtual FString GetStaticDescription() const override;
};
