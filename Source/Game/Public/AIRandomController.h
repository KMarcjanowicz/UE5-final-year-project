// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIRandomController.generated.h"

/**
 * 
 */
UCLASS()
class GAME_API AAIRandomController : public AAIController
{
	GENERATED_BODY()

	/* Blackboard component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBlackboardComponent* BlackboardComp;

	/* Behavior tree component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* BehaviorTreeComp;

	/* keys for the blackboard */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName LocationToGoKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		FName PlayerKey;

public:

	AAIRandomController();

	void SetPlayerCaught(APawn* _Pawn);

	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; };

protected:

	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* _InPawn) override;

};
