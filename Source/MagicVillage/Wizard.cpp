// Fill out your copyright notice in the Description page of Project Settings.


#include "Wizard.h"
#include "Staff.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "SpellProjectileBase.h"
#include "HealthComponent.h"

// Sets default values
AWizard::AWizard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Spring Arm configuration
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 450.f;
	SpringArm->bUsePawnControlRotation = true;

	// Camera configuration
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Health Component configuration
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->SetMaxHealth(100.f);

	// Character Movement Component configuration
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 450.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;

	// Controller Rotation configuration
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	// Lock on target camera offset configuration
	TargetFocusCameraOffset = 15.0f;

}

// Called when the game starts or when spawned
void AWizard::BeginPlay()
{
	Super::BeginPlay();
	
	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	// Spawn Staff
	if (StaffClass)
	{
		Staff = GetWorld()->SpawnActor<AStaff>(StaffClass);
		Staff->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_r_Staff"));
		Staff->SetOwner(this);
	}
}

// Called every frame
void AWizard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsLockedOnTarget)
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());
		LookAtRotation.Pitch -= TargetFocusCameraOffset;
		GetController()->SetControlRotation(LookAtRotation);

		FRotator CharacterRotation(0.f, LookAtRotation.Yaw, 0.f);
		SetActorRotation(CharacterRotation);

		GetCharacterMovement()->MaxWalkSpeed = MaxLockedOnSpeed;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}

}

// Called to bind functionality to input
void AWizard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWizard::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWizard::Look);
		EnhancedInputComponent->BindAction(CastSpellAction, ETriggerEvent::Started, this, &AWizard::CastSpell);
		EnhancedInputComponent->BindAction(LockOnTargetAction, ETriggerEvent::Started, this, &AWizard::LockOnTarget);
	}

}

AStaff* AWizard::GetStaff() const
{
	return Staff;
}

TArray<TSubclassOf<ASpellProjectileBase>> AWizard::GetAvailableSpells() const
{
	return AvailableSpells;
}

AActor* AWizard::GetTargetActor() const
{
	return TargetActor;
}

float AWizard::GetCurrentSpellIndex() const
{
	return CurrentSpellIndex;
}

bool AWizard::GetIsLockedOnTarget() const
{
	return bIsLockedOnTarget;
}

void AWizard::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller)
	{
		FRotator ControllerRotation = Controller->GetControlRotation();
		FRotator Yawrotaion(0.f, ControllerRotation.Yaw, 0.f);

		// Calculate movement directions
		FVector ForwardDirection = UKismetMathLibrary::GetForwardVector(ControllerRotation);
		FVector RightDirection = UKismetMathLibrary::GetRightVector(ControllerRotation);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}

}

void AWizard::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(-LookVector.Y);
	}
}

void AWizard::CastSpell(const FInputActionValue& Value)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (Staff && AnimInstance && CastSpellMontage && !bIsCastingSpell)
	{
		bIsCastingSpell = true;
		AnimInstance->Montage_Play(CastSpellMontage);
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AWizard::ResetIsCastingSpell, 1.0f, false);
	}
}

void AWizard::LockOnTarget(const FInputActionValue& Value)
{
	if (bIsLockedOnTarget)
	{
		bIsLockedOnTarget = false;
		TargetActor = nullptr;
	}
	else
	{
		if (TargetActorsCandidates.Num() > 0)
		{
			TargetActor = TargetActorsCandidates[0];
			bIsLockedOnTarget = true;
		}
	}
}

void AWizard::ResetIsCastingSpell()
{
	bIsCastingSpell = false;
}

void AWizard::HandleDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Wizard died"));
}

