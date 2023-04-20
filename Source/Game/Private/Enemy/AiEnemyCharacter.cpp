// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AiEnemyCharacter.h"


// Sets default values
AAiEnemyCharacter::AAiEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Label = CreateDefaultSubobject<UTextRenderComponent>("Label");

}

// Called when the game starts or when spawned
void AAiEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAiEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAiEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAiEnemyCharacter::ChangeTextOnLabel(FString _TextToChange)
{

}

