// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Wizard.generated.h"

struct FInputActionValue;

UCLASS()
class MAGICVILLAGE_API AWizard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWizard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* CastSpellAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LockOnTargetAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* DrinkHealthPotionAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* DrinkManaPotionAction;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundBase* DrinkingPotionSound;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, Category = "Speed")
	float MaxWalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float MaxLockedOnSpeed = 200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	TArray<AActor*> TargetActorsCandidates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetFocusCameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float LockOnTargetRotationSpeed;

	UPROPERTY(EditAnywhere, Category = "Targeting")
	float MaxLockOnDistance = 10000.0f;

	AActor* TargetActor = nullptr;

	// Input functions
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LockOnTarget(const FInputActionValue& Value);
	void DrinkHealthPotion(const FInputActionValue& Value);
	void DrinkManaPotion(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void CastSpell(const FInputActionValue& Value);

	// Getters
	class AStaff* GetStaff() const;
	TArray<TSubclassOf<class ASpellProjectileBase>> GetAvailableSpells() const;

	UFUNCTION(BlueprintPure)
	AActor* GetTargetActor() const;

	float GetCurrentSpellIndex() const;

	UFUNCTION(BlueprintPure)
	bool GetIsLockedOnTarget() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	class UHealthComponent* GetHealthComponent() const;

	UFUNCTION(BlueprintPure)
	float GetManaPercent() const;

	UFUNCTION(BlueprintPure)
	int GetHealthPotions() const;

	UFUNCTION(BlueprintPure)
	int GetManaPotions() const;

	// Setters
	void SetIsLockedOnTarget(bool NewIsLockedOnTarget);
	void SetTargetActor(AActor* NewTargetActor);

	void ResetIsCastingSpell();
	void ResetIsDrinkingPotion();
	void HandleDeath();
	void PlayDrinkingPotionMontage();
	void AddManaPotion();
	void AddHealthPotion();
	AActor* ChooseTargetActor(const TArray<AActor*>& Candidates);

private:

	UPROPERTY(EditDefaultsOnly, Category = "Staff")
	TSubclassOf<class AStaff> StaffClass;

	UPROPERTY()
	class AStaff* Staff;

	UPROPERTY(EditAnywhere, Category = "Spells")
	TArray<TSubclassOf<class ASpellProjectileBase>> AvailableSpells;

	UPROPERTY(EditAnywhere, Category = "Animation");
	class UAnimMontage* CastSpellMontage;

	UPROPERTY(EditAnywhere, Category = "Animation");
	class UAnimMontage* DrinkingPotionMontage;

	UPROPERTY(EditAnywhere)
	bool bIsCastingSpell = false;

	bool bIsDrinkingPotion = false;

	UPROPERTY(EditAnywhere, Category = "Potions")
	float MaxMana = 100.0f;

	float Mana;

	UPROPERTY(EditAnywhere, Category = "Potions")
	float HealthPotionAmount = 30.0f;

	int HealthPotions;

	UPROPERTY(EditAnywhere, Category = "Potions")
	float ManaPotionAmount = 30.0f;

	int ManaPotions;

	float CurrentSpellIndex = 0;

	bool bIsLockedOnTarget = false;

	bool FinalRotationAchieved = false;

};
