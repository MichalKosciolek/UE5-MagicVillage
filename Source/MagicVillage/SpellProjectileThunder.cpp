// Fill out your copyright notice in the Description page of Project Settings.


#include "SpellProjectileThunder.h"

ASpellProjectileThunder::ASpellProjectileThunder()
    : Super()
{
    bIsHoming = false;
    InitialSpeed = 1000.f;
    MaxSpeed = 1000.f;
}

void ASpellProjectileThunder::BeginPlay()
{
    Super::BeginPlay();

}

void ASpellProjectileThunder::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::OnHit(HitComp, OtherActor, OtherComp, NormalImpulse, Hit);
}
