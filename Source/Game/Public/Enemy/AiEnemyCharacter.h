// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AiEnemyCharacter.generated.h"

UENUM(BlueprintType)
enum class EVictory : uint8 {
	VE_Dance       UMETA(DisplayName = "Dance"),
	VE_Rain        UMETA(DisplayName = "Rain"),
	VE_Song        UMETA(DisplayName = "Song"),
};


UCLASS()
class GAME_API AAiEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAiEnemyCharacter();

	/* Behaviour tree for AI logic*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* BehaviorTree;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
