// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PotionBase.h"
#include "HealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class MAGICVILLAGE_API AHealthPotion : public APotionBase
{
	GENERATED_BODY()

protected:
	virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	
};
