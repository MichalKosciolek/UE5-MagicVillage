// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MagicVillageGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAGICVILLAGE_API AMagicVillageGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void PawnDied(APawn* DeadPawn);
};
