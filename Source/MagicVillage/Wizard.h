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

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, Category = "Speed")
	float MaxWalkSpeed = 600.0f;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float MaxLockedOnSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	TArray<AActor*> TargetActorsCandidates;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	float TargetFocusCameraOffset;

	AActor* TargetActor = nullptr;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void CastSpell(const FInputActionValue& Value);
	void LockOnTarget(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Getters
	class AStaff* GetStaff() const;
	TArray<TSubclassOf<class ASpellProjectileBase>> GetAvailableSpells() const;
	AActor* GetTargetActor() const;
	float GetCurrentSpellIndex() const;
	UFUNCTION(BlueprintPure)
	bool GetIsLockedOnTarget() const;

	void ResetIsCastingSpell();
	void HandleDeath();

private:

	UPROPERTY(EditDefaultsOnly, Category = "Staff")
	TSubclassOf<class AStaff> StaffClass;

	UPROPERTY()
	class AStaff* Staff;

	UPROPERTY(EditAnywhere, Category = "Spells")
	TArray<TSubclassOf<class ASpellProjectileBase>> AvailableSpells;

	UPROPERTY(EditAnywhere, Category = "Animation");
	class UAnimMontage* CastSpellMontage;

	UPROPERTY(EditAnywhere)
	bool bIsCastingSpell = false;

	float CurrentSpellIndex = 0;

	bool bIsLockedOnTarget = false;
};
