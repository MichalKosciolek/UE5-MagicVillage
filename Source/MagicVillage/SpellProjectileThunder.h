// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpellProjectileBase.h"
#include "SpellProjectileThunder.generated.h"

/**
 * 
 */
UCLASS()
class MAGICVILLAGE_API ASpellProjectileThunder : public ASpellProjectileBase
{
	GENERATED_BODY()

public:
	ASpellProjectileThunder();

protected:
	virtual void BeginPlay() override;

	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
