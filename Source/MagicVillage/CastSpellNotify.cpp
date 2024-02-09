// Fill out your copyright notice in the Description page of Project Settings.


#include "CastSpellNotify.h"
#include "Wizard.h"
#include "Staff.h"
#include "SpellProjectileBase.h"

void UCastSpellNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp && MeshComp->GetOwner())
	{
		AWizard* Wizard = Cast<AWizard>(MeshComp->GetOwner());
		if (Wizard)
		{
			Wizard->GetStaff()->CastSpell(
				Wizard->GetAvailableSpells(), 
				Wizard->GetCurrentSpellIndex(),
				Wizard->GetTargetActor()
			);
		}
	}
}
