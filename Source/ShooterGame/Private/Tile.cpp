// Copyright Abhisek Roy. All Rights Reserved.


#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "NavMesh/NavMeshBoundsVolume.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MinExtent = FVector(0, -3500, 5);
	MaxExtent = FVector(7000, 3500, 5);
	NavigationBoundsOffset = FVector(3500, 0, 0);
}

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	Pool->Return(NavMeshBoundsVolume);
}

void ATile::SetPool(UActorPool* InPool)
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Setting Pool %s"), *(this->GetName()), *(InPool->GetName()));
	Pool = InPool;
	PositionNavMeshBoundsVolume();
}

void ATile::PositionNavMeshBoundsVolume()
{
	NavMeshBoundsVolume = Pool->Checkout();
	if (NavMeshBoundsVolume == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Not enough actors in pool."), *GetName());
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checked out: {%s}"), *GetName(), *NavMeshBoundsVolume->GetName());
	NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
	FNavigationSystem::Build(*GetWorld());
}

void ATile::PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale) 
{
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	float Scale = FMath::RandRange(MinScale, MaxScale);

	for(int i = 0; i < NumberToSpawn; i++)
	{
		FVector SpawnPoint = GetEmptyLocation(MinExtent, MaxExtent, Radius * Scale);
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