// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/AiEnemyCharacter.h"
#include "Components/SphereComponent.h"


// Sets default values
AAiEnemyCharacter::AAiEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//TextRenderComp
	StateLabelComp = CreateDefaultSubobject<UTextRenderComponent>("State Label");
	StateLabelComp->SetupAttachment(RootComponent);
	StateLabelComp->SetHorizontalAlignment(EHTA_Center);
	StateLabelComp->SetRelativeLocation(FVector(10.0f, 0.0f, 110.0f));

	//TextRenderComp2
	AlarmedLabelComp = CreateDefaultSubobject<UTextRenderComponent>("Alarm Label");
	AlarmedLabelComp->SetupAttachment(RootComponent);
	AlarmedLabelComp->SetHorizontalAlignment(EHTA_Center);
	AlarmedLabelComp->SetRelativeLocation(FVector(10.0f, 0.0f, 90.0f));

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

	//Debug Spheres
	/*
	SightDebug = CreateDefaultSubobject<USphereComponent>("SightDebug");
	SightDebug->SetupAttachment(RootComponent);
	SightDebug->SetSphereRadius(750.0f);
	SightDebug->ShapeColor = FColor::Green;
	SightDebug->bHiddenInGame = false;

	HearingDebug = CreateDefaultSubobject<USphereComponent>("HearingDebug");
	HearingDebug->SetupAttachment(RootComponent);
	HearingDebug->SetSphereRadius(1250.0f);
	HearingDebug->ShapeColor = FColor::Yellow;
	HearingDebug->bHiddenInGame = false;
	*/
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
		StateLabelComp->SetTextRenderColor(FColor::Green);
		AlarmedLabelComp->SetTextRenderColor(FColor::Green);
		StateLabelComp->SetText(FText::AsCultureInvariant("..."));
	}
	else if (_TextToChange == "Investigate") {
		StateLabelComp->SetTextRenderColor(FColor::Yellow);
		AlarmedLabelComp->SetTextRenderColor(FColor::Yellow);
		StateLabelComp->SetText(FText::AsCultureInvariant("?"));
	}
	else if (_TextToChange == "Chase") {
		StateLabelComp->SetTextRenderColor(FColor::Red);
		AlarmedLabelComp->SetTextRenderColor(FColor::Red);
		StateLabelComp->SetText(FText::AsCultureInvariant("!"));
	}
	
}

