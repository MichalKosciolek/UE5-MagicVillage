// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicBattleGameMode.h"

void AMagicBattleGameMode::ActorDied(AActor* DeadActor)
{
	Super::ActorDied(DeadActor);
	UE_LOG(LogTemp, Warning, TEXT("Wizard died"));
}
