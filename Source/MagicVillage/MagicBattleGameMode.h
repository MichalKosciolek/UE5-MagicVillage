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
	virtual void ActorDied(AActor* DeadActor) override;
};
