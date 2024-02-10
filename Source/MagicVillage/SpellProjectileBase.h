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
	float CalculateDistanceFromPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Combat")
	bool bIsHoming = false;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxReachedDistance = 5000.f;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float Damage = 20.f;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float InitialSpeed = 500.f;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float MaxSpeed = 500.f;
	UPROPERTY(EditAnywhere, Category = "Speed")
	float GravityScale = 0.f;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* BoxComp;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UStaticMeshComponent* SpellMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystem* ImpactEffect;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	class UParticleSystemComponent* TrailEffect;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundBase* LaunchSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	class USoundBase* HitSound;

	AActor* TargetActor;
	class AActor* PlayerActor;

	float CurrentDistanceFromPlayer = 0.f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
