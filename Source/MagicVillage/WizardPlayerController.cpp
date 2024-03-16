// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AWizardPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	
	HUD->RemoveFromParent();
	if (bIsWinner)
	{
		WinScreen = CreateWidget(this, WinScreenClass);
		if (WinScreen)
		{
			WinScreen->AddToViewport();
		}
	}
	else
	{
		LoseScreen = CreateWidget(this, LoseScreenClass);
		if (LoseScreen)
		{
			LoseScreen->AddToViewport();
		}
	}

	FTimerHandle ResetTimer;
	GetWorldTimerManager().SetTimer(ResetTimer, this, &AWizardPlayerController::GoToMainMenu, ResetDelay);
}

void AWizardPlayerController::GoToMainMenu()
{
	if (WinScreen)
	{
		WinScreen->RemoveFromParent();
	}
	if (LoseScreen)
	{
		LoseScreen->RemoveFromParent();
	}

	UGameplayStatics::OpenLevel(this, "MainMenuLevel");
}

void AWizardPlayerController::SetPlayerEnabledState(bool bIsPlayerEnabled)
{
	if (bIsPlayerEnabled)
	{
		GetPawn()->EnableInput(this);
	}
	else
	{
		GetPawn()->DisableInput(this);
	}
}

void AWizardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Creating HUD
	HUD = CreateWidget(this, HUDClass);
	if (HUD)
	{
		HUD->AddToViewport();
	}
}
