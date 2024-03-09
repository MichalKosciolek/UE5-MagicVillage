// Fill out your copyright notice in the Description page of Project Settings.


#include "ManaPotion.h"
#include "Kismet/GameplayStatics.h"
#include "Wizard.h"

void AManaPotion::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::OnOverlap(OverlappedActor, OtherActor);

	AActor* PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerActor && OtherActor == PlayerActor)
	{
		AWizard* Wizard = Cast<AWizard>(PlayerActor);
		if (Wizard && GrabSound)
		{
			Wizard->AddManaPotion();
			UGameplayStatics::PlaySoundAtLocation(this, GrabSound, Wizard->GetActorLocation());
			Destroy();
		}
	}
}
