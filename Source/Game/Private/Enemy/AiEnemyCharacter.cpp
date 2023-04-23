// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AiEnemyCharacter.h"


// Sets default values
AAiEnemyCharacter::AAiEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TextRenderComp
	LabelComp = CreateDefaultSubobject<UTextRenderComponent>("Label");
	LabelComp->SetupAttachment(RootComponent);
	LabelComp->SetHorizontalAlignment(EHTA_Center);

	//SightLight Comp
	SightLightComp = CreateDefaultSubobject<USpotLightComponent>("SightLight");
	SightLightComp->SetupAttachment(RootComponent);
	SightLightComp->SetOuterConeAngle(45.0);
	SightLightComp->SetRelativeLocation(FVector(10.0f, 0.0f, -50.0f));

	//SpotLight Comp
	SpotLightComp = CreateDefaultSubobject<USpotLightComponent>("SpotLight");
	SpotLightComp->SetupAttachment(RootComponent);
	SpotLightComp->SetOuterConeAngle(45.0);
	SpotLightComp->SetRelativeLocation(FVector(20.0f, 0.0f, 50.0f));
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
	if (_TextToChange == "Normal") {
		LabelComp->SetTextRenderColor(FColor::Green);
		LabelComp->SetText(FText::AsCultureInvariant("..."));
	}
	else if (_TextToChange == "Investigate") {
		LabelComp->SetTextRenderColor(FColor::Yellow);
		LabelComp->SetText(FText::AsCultureInvariant("?"));
	}
	else if (_TextToChange == "Chase") {
		LabelComp->SetTextRenderColor(FColor::Red);
		LabelComp->SetText(FText::AsCultureInvariant("!"));
	}
	
}

