// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CastSpell.h"
#include "AIController.h"
#include "Wizard.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"



UBTTask_CastSpell::UBTTask_CastSpell()
{
	NodeName = TEXT("Cast Spell");
}

EBTNodeResult::Type UBTTask_CastSpell::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* AIController = OwnerComp.GetAIOwner();
	AWizard* Wizard = Cast<AWizard>(AIController->GetPawn());
	AActor* PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (!AIController || !Wizard || !PlayerActor)
	{
		return EBTNodeResult::Failed;
	}

	FInputActionValue InputValue;
	Wizard->SetTargetActor(PlayerActor);
	Wizard->CastSpell(InputValue);

	return EBTNodeResult::Succeeded;
}
