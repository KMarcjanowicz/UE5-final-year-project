// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UserInterface/UWPlayerInterface.h"
#include "GameGameMode.generated.h"


UCLASS(minimalapi)
class AGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameGameMode();

protected:

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Class Types")
	TSubclassOf<UUserWidget> WidgetClass;

public:
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Runtime")
	class UUWPlayerInterface* PlayerInterface;

public:
	virtual void BeginPlay() override;

};



