// Fill out your copyright notice in the Description page of Project Settings.


#include "UWPlayerInterface.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UUWPlayerInterface::NativeConstruct()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	Player = Cast<AGameCharacter>(PlayerCharacter);

	if (CrouchButton) 
	{
		CrouchButton->OnClicked.AddDynamic(this, &UUWPlayerInterface::CrouchButtonPressed);
	}

	if (SwitchCameraButton)
	{
		SwitchCameraButton->OnClicked.AddDynamic(this, &UUWPlayerInterface::SwitchCameraButtonPressed);
	}
}

void UUWPlayerInterface::CrouchButtonPressed()
{
	Player->ClickCrouch();
}

void UUWPlayerInterface::SwitchCameraButtonPressed()
{
	Player->AimThrowObject();
}

void UUWPlayerInterface::UpdateRockCounter(int32 _Amount)
{
	RockAmount = _Amount;
}
