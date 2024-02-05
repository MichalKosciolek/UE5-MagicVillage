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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* InputMapping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* CastSpellAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void CastSpell(const FInputActionValue& Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsCastingSpell() const;

	void ResetIsCastingSpell();

	UPROPERTY(EditDefaultsOnly, Category = "Staff")
	TSubclassOf<class AStaff> StaffClass;

	UPROPERTY()
	class AStaff* Staff;

	UPROPERTY(EditAnywhere, Category = "Spells")
	TArray<TSubclassOf<class ASpellProjectileBase>> AvailableSpells;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation");
	class UAnimMontage* CastSpellMontage;

private:
	UPROPERTY(EditAnywhere)
	bool bIsCastingSpell = false;

	AActor* TargetActor = nullptr;
};
