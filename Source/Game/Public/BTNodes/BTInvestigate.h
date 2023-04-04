// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTInvestigate.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTInvestigate : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTInvestigate();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;
};
