// Copyright Abhisek Roy. All Rights Reserved.


#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile::SetPool(UActorPool* InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;
}

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale) 
{
	FVector MinPoint(0), MaxPoint(0);
	MinPoint = FVector(0, -3500, 5);
	MaxPoint = FVector(7000, 3500, 5);

	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	float Scale = FMath::RandRange(MinScale, MaxScale);

	for(int i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint = GetEmptyLocation(MinPoint, MaxPoint, Radius * Scale);
		float RandRotation = FMath::RandRange(-180, 180);
		PlaceActor(ActorToSpawn, SpawnPoint, RandRotation, Scale);
	}
}

FVector ATile::GetEmptyLocation(FVector MinPoint, FVector MaxPoint, float Radius) 
{
	bool HasHit = true;
	FVector RandPoint(0);
	int32 MaxIter = 1;
	while(HasHit && MaxIter < 100)
	{
		RandPoint = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
		HasHit = IsEmptySpace(GetActorLocation() + RandPoint, Radius);
		MaxIter++;
		// FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
		// DrawDebugCapsule(GetWorld(), GetActorLocation() + RandPoint, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	}

	return RandPoint;
}

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector Location, float Rotation, float Scale) 
{
	AActor* ActorSpawned = GetWorld()->SpawnActor(ActorToSpawn);
	ActorSpawned->SetActorRelativeLocation(Location);
	ActorSpawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	ActorSpawned->SetActorRotation(FRotator(0, Rotation, 0));
	ActorSpawned->SetActorScale3D(FVector(Scale));
}

bool ATile::IsEmptySpace(FVector Location, float Radius)
{
	// Sphere casting
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	return HasHit;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}