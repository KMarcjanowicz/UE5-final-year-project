// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API UBTRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTRandomLocation();
	
private:

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* _NodeMemory) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	float SearchRadius{ 300.0f };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		float WalkSpeed{ 100.0f };

	virtual FString GetStaticDescription() const override;
};
