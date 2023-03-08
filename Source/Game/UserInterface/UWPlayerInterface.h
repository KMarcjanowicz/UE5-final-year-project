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

	UPROPERTY(BlueprintReadWrite, Category = "Class Types", meta = (BindWidget))
		class UTextBlock* TextLabel;

	UPROPERTY(BlueprintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* CrouchButton;

	UPROPERTY(BlueprintReadWrite, Category = "Buttons", meta = (BindWidget))
		class UButton* SwitchCameraButton;


	virtual void NativeConstruct() override;

	UFUNCTION()
		void CrouchButtonPressed();

	UFUNCTION()
		void SwitchCameraButtonPressed();

protected:
	/* player Reference */
	UPROPERTY(BlueprintReadWrite, Category = "Player Reference")
		AGameCharacter* Player;
};
