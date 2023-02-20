// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
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

};
