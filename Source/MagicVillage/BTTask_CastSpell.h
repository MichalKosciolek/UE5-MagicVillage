// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_CastSpell.generated.h"

/**
 * 
 */
UCLASS()
class MAGICVILLAGE_API UBTTask_CastSpell : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_CastSpell();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
