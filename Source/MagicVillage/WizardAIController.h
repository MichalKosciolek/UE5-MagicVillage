// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WizardAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAGICVILLAGE_API AWizardAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	bool IsDead() const;

	UPROPERTY(EditAnywhere)
	UBehaviorTree* BehaviorTree;
};
