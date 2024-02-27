// Fill out your copyright notice in the Description page of Project Settings.


#include "Staff.h"
#include "Components/StaticMeshComponent.h"
#include "SpellProjectileBase.h"

// Sets default values
AStaff::AStaff()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(Root);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AStaff::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AStaff::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStaff::CastSpell(TArray<TSubclassOf<ASpellProjectileBase>> AvailableSpells, int SpellIndex, AActor* TargetActor)
{
	if (AvailableSpells.IsValidIndex(SpellIndex))
	{
		FTransform SpawnTransform = ProjectileSpawnPoint->GetComponentTransform();
		ASpellProjectileBase* Spell = GetWorld()->SpawnActorDeferred<ASpellProjectileBase>(
			AvailableSpells[SpellIndex],
			SpawnTransform,
			this
		);

		if (TargetActor && Spell)
		{
			Spell->SetTargetActor(TargetActor);
		}

		if (Spell)
		{
			Spell->FinishSpawning(SpawnTransform);
		}
	}
}


