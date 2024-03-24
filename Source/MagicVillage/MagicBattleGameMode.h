// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MagicVillageGameModeBase.h"
#include "MagicBattleGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MAGICVILLAGE_API AMagicBattleGameMode : public AMagicVillageGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void PawnDied(APawn* DeadPawn) override;

	UFUNCTION(BlueprintPure)
	int GetNumberOfEnemies() const;

protected:
	virtual void BeginPlay() override;

	virtual void HandleGameStart() override;

private:
	void EndGame(bool bIsPlayerWinner);

	int NumberOfEnemies = 0;

	UPROPERTY(EditAnywhere)
	float StartDelay = 3.f;

	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<class UUserWidget> StartScreenClass;
};
