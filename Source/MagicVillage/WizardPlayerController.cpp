// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardPlayerController.h"
#include "Blueprint/UserWidget.h"

void AWizardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}
