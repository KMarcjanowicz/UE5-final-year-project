// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TextRenderComponent.h"
#include "AiEnemyCharacter.generated.h"

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

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = AI, meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* Label;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Function to change the label text above the head of the character
	void ChangeTextOnLabel(FString _TextToChange);
};
