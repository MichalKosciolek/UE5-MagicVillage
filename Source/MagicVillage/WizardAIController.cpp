// Fill out your copyright notice in the Description page of Project Settings.


#include "WizardAIController.h"
#include "Wizard.h"
#include "HealthComponent.h"

bool AWizardAIController::IsDead() const
{
	AWizard* ControlledWizard = Cast<AWizard>(GetPawn());
	if (ControlledWizard)
	{
		return ControlledWizard->GetHealthComponent()->GetIsDead();
	}

	return true;
}
