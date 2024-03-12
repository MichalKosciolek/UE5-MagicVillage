// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardAIController.h"
#include "Wizard.h"
#include "HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Kismet/GameplayStatics.h"

void AWizardAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BehaviorTree)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AWizardAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool AWizardAIController::IsDead() const
{
	AWizard* ControlledWizard = Cast<AWizard>(GetPawn());
	if (ControlledWizard)
	{
		return ControlledWizard->GetHealthComponent()->GetIsDead();
	}

	return true;
}
