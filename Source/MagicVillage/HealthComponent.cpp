// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "MagicBattleGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
	MagicBattleGameMode = Cast<AMagicBattleGameMode>(UGameplayStatics::GetGameMode(this));
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::SetMaxHealth(float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

bool UHealthComponent::GetIsDead() const
{
	return bIsDead;
}

void UHealthComponent::Heal(float HealAmount)
{
	Health += HealAmount;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	Health -= Damage;
	if (Health <= 0)
	{
		bIsDead = true;
		APawn* DeadPawn = Cast<APawn>(GetOwner());
		MagicBattleGameMode->PawnDied(DeadPawn);
	}
	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
}

