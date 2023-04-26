// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTUpdateCautionRate.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTUpdateCautionRate : public UBTTaskNode
{
	GENERATED_BODY()

	UBTUpdateCautionRate();

public:
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;

	virtual FString GetStaticDescription() const override;
};
