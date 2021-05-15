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
	FSpawnPosition SpawnPosition;

	for(int i = 0; i < NumberToSpawn; i++)
	{
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		SpawnPosition.Location = GetEmptyLocation(MinExtent, MaxExtent, Radius * SpawnPosition.Scale);
		SpawnPosition.Rotation = FMath::RandRange(-180, 180);
		PlaceActor(ActorToSpawn, SpawnPosition);
	}
}

void ATile::PlaceAIPawns(TSubclassOf<APawn> ActorToSpawn, int32 MinSpawn, int32 MaxSpawn, float Radius, float ZOffset) 
{
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	FSpawnPosition SpawnPosition;

	for(int i = 0; i < NumberToSpawn; i++)
	{
		SpawnPosition.Scale = 1;
		SpawnPosition.Location = GetEmptyLocation(MinExtent, MaxExtent, Radius * SpawnPosition.Scale);
		SpawnPosition.Rotation = FMath::RandRange(-180, 180);
		APawn* ActorSpawned = GetWorld()->SpawnActor<APawn>(ActorToSpawn);
		ActorSpawned->SetActorRelativeLocation(SpawnPosition.Location + FVector(0, 0, ZOffset));
		ActorSpawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
		ActorSpawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
		ActorSpawned->Tags.Add(FName(TEXT("Enemy")));
		ActorSpawned->SpawnDefaultController();
	}
}

TArray<FSpawnPosition> ATile::GetSpawnPoints(int32 MinSpawn, int32 MaxSpawn, float Radius, float MinScale, float MaxScale) 
{
	int32 NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	TArray<FSpawnPosition> SpawnPoints;
	FSpawnPosition SpawnPosition;

	for(int i = 0; i < NumberToSpawn; i++)
	{
		SpawnPosition.Scale = FMath::RandRange(MinScale, MaxScale);
		SpawnPosition.Location = GetEmptyLocation(MinExtent, MaxExtent, Radius * SpawnPosition.Scale);
		SpawnPosition.Rotation = FMath::RandRange(-180, 180);
		SpawnPoints.Add(SpawnPosition);
	}
	return SpawnPoints;
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

void ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, const FSpawnPosition& SpawnPosition) 
{
	AActor* ActorSpawned = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
	ActorSpawned->SetActorRelativeLocation(SpawnPosition.Location);
	ActorSpawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	ActorSpawned->SetActorRotation(FRotator(0, SpawnPosition.Rotation, 0));
	ActorSpawned->SetActorScale3D(FVector(SpawnPosition.Scale));
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