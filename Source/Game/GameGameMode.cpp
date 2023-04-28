// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameGameMode.h"
#include "GameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGameGameMode::AGameGameMode()
{

}

int32 AGameGameMode::GetScore()
{
	return Score;
}

void AGameGameMode::SetScore(int32 _Amount)
{
	
	Score += _Amount;
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("Adding Score: %i"), Score));
	PlayerInterface->SetScore(Score);
}

void AGameGameMode::BeginPlay()
{
	if (IsValid(WidgetClass))
	{
		PlayerInterface = Cast<UUWPlayerInterface>(CreateWidget(GetWorld(), WidgetClass));

		if (PlayerInterface != nullptr) 
		{
			PlayerInterface->AddToViewport();
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("WPlayer interface is nullptr")));
		}
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::White, FString::Printf(TEXT("WidgetClass not valid")));
	}
}
