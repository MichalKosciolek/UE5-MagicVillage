// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_UpdatePlayerLocation.generated.h"

/**
 * 
 */
UCLASS()
class MAGICVILLAGE_API UBTTask_UpdatePlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_UpdatePlayerLocation();
	
};