// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellProjectileBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ASpellProjectileBase::ASpellProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	RootComponent = BoxComp;

	SpellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpellMesh"));
	SpellMesh->SetupAttachment(BoxComp);

	TrailEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailEffect"));
	TrailEffect->SetupAttachment(BoxComp);

	ProjectileMovComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovComp"));
	ProjectileMovComp->InitialSpeed = InitialSpeed;
	ProjectileMovComp->MaxSpeed = MaxSpeed;

}

// Called when the game starts or when spawned
void ASpellProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	BoxComp->OnComponentHit.AddDynamic(this, &ASpellProjectileBase::OnHit);
	
	PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerCharacter(this, 0));

	ProjectileMovComp->bIsHomingProjectile = bIsHoming;
	ProjectileMovComp->ProjectileGravityScale = GravityScale;

	if (TargetActor)
	{
		if (bIsHoming)
		{
			ProjectileMovComp->HomingTargetComponent = TargetActor->GetRootComponent();
		}

		FVector TargetDicection = GetActorLocation() - TargetActor->GetActorLocation();
		FVector TargetUnitDirection = TargetDicection.GetSafeNormal();
		ProjectileMovComp->Velocity = TargetUnitDirection * InitialSpeed;
	}
	else
	{
		ProjectileMovComp->Velocity = PlayerActor->GetActorForwardVector() * InitialSpeed;
	}

	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}

	if (TrailEffect)
	{
		TrailEffect->Activate();
	}
	
}

// Called every frame
void ASpellProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpellProjectileBase::SetTargetActor(AActor * Target)
{
	TargetActor = Target;
}

void ASpellProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner && OtherActor && OtherActor != this && OtherActor != MyOwner && OtherActor != PlayerActor)
	{
		if (ImpactEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
				this, 
				ImpactEffect, 
				GetActorLocation(), 
				GetActorRotation()
			);
		}

		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		}
	}

	Destroy();
}