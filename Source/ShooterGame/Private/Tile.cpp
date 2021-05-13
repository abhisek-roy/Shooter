// Copyright Abhisek Roy. All Rights Reserved.


#include "Tile.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 300) 
{
	FVector MinPoint(0), MaxPoint(0);
	MinPoint = FVector(0, -3500, 50);
	MaxPoint = FVector(14000, 3500, 50);

	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for(int i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint = GetEmptyLocation(MinPoint, MaxPoint, Radius);
		PlaceActor(ActorToSpawn, SpawnPoint);
	}
}

FVector ATile::GetEmptyLocation(FVector MinPoint, FVector MaxPoint, float Radius) 
{
	bool HasHit = true;
	FVector RandPoint(0);
	while(HasHit)
	{
		RandPoint = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
		HasHit = IsEmptySpace(GetActorLocation() + RandPoint, Radius);
		FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
		DrawDebugCapsule(GetWorld(), GetActorLocation() + RandPoint, 0, Radius, FQuat::Identity, ResultColor, true, 100);
	}

	return RandPoint;
}

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector Location) 
{
	AActor* ActorSpawned = GetWorld()->SpawnActor(ActorToSpawn);
	ActorSpawned->SetActorRelativeLocation(Location);
	ActorSpawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
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