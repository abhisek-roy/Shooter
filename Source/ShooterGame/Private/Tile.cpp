// Copyright Abhisek Roy. All Rights Reserved.


#include "Tile.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1) 
{
	FVector MinPoint(0), MaxPoint(0);
	MinPoint = FVector(0, -3500, 50);
	MaxPoint = FVector(14000, 3500, 50);

	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);

	for(int i = 0; i < NumberToSpawn; i++)
	{
		FVector RandPoint = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
		AActor* ActorSpawned = GetWorld()->SpawnActor(ActorToSpawn);
		ActorSpawned->SetActorRelativeLocation(RandPoint);
		ActorSpawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	CastSphere(GetActorLocation(), 300);
	CastSphere(GetActorLocation() + FVector(0, 0, 1000), 300);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATile::CastSphere(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_Camera,
		FCollisionShape::MakeSphere(Radius)
	);
	FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
	DrawDebugSphere(GetWorld(), Location, Radius, 10, ResultColor, true, 100);
	return HasHit;
}
