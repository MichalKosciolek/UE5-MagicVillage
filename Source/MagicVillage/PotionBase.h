// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionBase.generated.h"

UCLASS()
class MAGICVILLAGE_API APotionBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APotionBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotationSpeed = 50.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float BounceSpeed = 3.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float BounceHeight = 2.f;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* GrabSound;

	UFUNCTION()
	virtual void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
