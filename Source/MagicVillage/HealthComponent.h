// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAGICVILLAGE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Setters
	void SetMaxHealth(float NewMaxHealth);

	// Getters
	float GetMaxHealth() const;
	float GetHealth() const;
	UFUNCTION(BlueprintPure)
	bool GetIsDead() const;

	void Heal(float HealAmount);

private:
	UPROPERTY(EditAnywhere)
	float MaxHealth = 20.0f;
	float Health;
	bool bIsDead = false;

	class AMagicBattleGameMode* MagicBattleGameMode;

	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser);
};
