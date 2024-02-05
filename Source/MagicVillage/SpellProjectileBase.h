// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpellProjectileBase.generated.h"

UCLASS()
class MAGICVILLAGE_API ASpellProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellProjectileBase();

	void SetTargetActor(AActor* Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bIsHoming = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UStaticMeshComponent* SpellMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystemComponent* TrailEffect;

	UPROPERTY(EditAnywhere, Category = "Speed")
	float InitialSpeed = 500.f;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float MaxSpeed = 500.f;

	AActor* TargetActor;

	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
