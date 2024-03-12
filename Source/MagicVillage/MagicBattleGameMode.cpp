// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBattleGameMode.h"
#include "EngineUtils.h"
#include "WizardAIController.h"
#include "Wizard.h"

void AMagicBattleGameMode::PawnDied(APawn* DeadPawn)
{
	Super::PawnDied(DeadPawn);

	// Checking if DeadPawn is Player
	APlayerController* PlayerController = Cast<APlayerController>(DeadPawn->GetController());
	if (PlayerController)
	{
		EndGame(false);
	}

	// Checking if all AI are dead
	for (AWizardAIController* AIController : TActorRange<AWizardAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			return;
		}
	}

	EndGame(true);

}

void AMagicBattleGameMode::EndGame(bool bIsPlayerWinner)
{
	if (bIsPlayerWinner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player won"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player lost"));
	}

}