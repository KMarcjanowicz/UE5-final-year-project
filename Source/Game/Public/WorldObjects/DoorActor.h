// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class GAME_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

	UPROPERTY(Category = General, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float TimeToOpen;

	UPROPERTY(Category = General, EditAnywhere, meta = (AllowPrivateAccess = "true"))
		float TimeToClose;

	UPROPERTY(Category = General, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsInUse;

protected:

	UPROPERTY(Category = General, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		bool bIsOpen;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool GetIsOpen();
};
