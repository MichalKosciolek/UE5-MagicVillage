// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBattleGameMode.h"
#include "EngineUtils.h"
#include "WizardAIController.h"
#include "Wizard.h"
#include "Kismet/GameplayStatics.h"
#include "WizardPlayerController.h"
#include "Blueprint/UserWidget.h"

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
	int Counter = 0;
	for (AWizardAIController* AIController : TActorRange<AWizardAIController>(GetWorld()))
	{
		if (!AIController->IsDead())
		{
			Counter++;
		}
	}

	NumberOfEnemies = Counter;
	if (Counter == 0)
	{
		EndGame(true);
	}
}

int AMagicBattleGameMode::GetNumberOfEnemies() const
{
	return NumberOfEnemies;
}

void AMagicBattleGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AMagicBattleGameMode::HandleGameStart()
{
	Super::HandleGameStart();

	AWizardPlayerController* PlayerController = Cast<AWizardPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	// Creating Start Screen
	UUserWidget* StartScreen = CreateWidget(PlayerController, StartScreenClass);
	if (StartScreen)
	{
		StartScreen->AddToViewport();
	}

	// Setting timer to enable player input
	if (PlayerController)
	{
		PlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableHandle;
		FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
			PlayerController,
			&AWizardPlayerController::SetPlayerEnabledState,
			true
		);
		GetWorldTimerManager().SetTimer(PlayerEnableHandle, PlayerEnableDelegate, StartDelay, false);
	}

	// Counting Enemies
	for (AWizardAIController* AIController: TActorRange<AWizardAIController>(GetWorld()))
	{
		NumberOfEnemies++;
	}
}

void AMagicBattleGameMode::EndGame(bool bIsPlayerWinner)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		if(Controller->IsPlayerController())
		{
			Controller->GameHasEnded(Controller->GetPawn(), bIsPlayerWinner);
		}
		else
		{
			Controller->GameHasEnded(Controller->GetPawn(), !bIsPlayerWinner);
		}
	}
}