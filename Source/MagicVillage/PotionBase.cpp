// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionBase.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APotionBase::APotionBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Capsule Component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;

	// Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(CapsuleComp);
}

// Called when the game starts or when spawned
void APotionBase::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &APotionBase::OnOverlap);
}

// Called every frame
void APotionBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotation
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += RotationSpeed * DeltaTime;
	SetActorRotation(NewRotation);

	// Bounce
	FVector NewLocation = GetActorLocation();
	NewLocation.Z += FMath::Sin(GetGameTimeSinceCreation() * BounceSpeed) * BounceHeight;
	SetActorLocation(NewLocation);

}

void APotionBase::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

