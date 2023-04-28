// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include <Game/GameCharacter.h>

#include "UWPlayerInterface.generated.h"
/**
 * 
 */
UCLASS()
class GAME_API UUWPlayerInterface : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(BlueprintReadWrite, Category = "Lables", meta = (BindWidget))
		class UTextBlock* TextLabel;

	UPROPERTY(BlueprintReadWrite, Category = "Lables", meta = (BindWidget))
		class UTextBlock* RockCounter;

	UPROPERTY(BlueprintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* CrouchButton;

	UPROPERTY(BlueprintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* SwitchCameraButton;


	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CrouchButtonPressed();

	UFUNCTION(BlueprintCallable)
	void SwitchCameraButtonPressed();

protected:
	/* player Reference */
	UPROPERTY(BlueprintReadWrite, Category = "Player Reference")
		class AGameCharacter* Player;

public:
	//Integer keeping track of how many rocks the player has in the inv
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = AI)
		int32 Score;

	UFUNCTION(BlueprintCallable)
		int32 GetScore();

	UFUNCTION(BlueprintCallable)
		void SetScore(int32 _Amount);
};
