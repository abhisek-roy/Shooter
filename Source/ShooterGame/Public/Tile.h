// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

USTRUCT()
struct FSpawnPosition
{
	GENERATED_USTRUCT_BODY()

	FVector Location;
	float Rotation;
	float Scale;
};

UCLASS()
class SHOOTERGAME_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, Category="Spawning")
	FVector MinExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	FVector MaxExtent;
	UPROPERTY(EditDefaultsOnly, Category = "Navigation")
	FVector NavigationBoundsOffset;

	// Delay NavMesh build to avoid stutters
	UPROPERTY(EditDefaultsOnly, Category="Spawning", meta = (ClampMin = "0", UIMin = "0"))
	float NavMeshBuildDelay = 2.0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void PlaceAIPawns(TSubclassOf<APawn> ActorToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 300);

private:
	bool IsEmptySpace(FVector Location, float Radius);

	template<class T>
	void RandomlyPlaceActors(TSubclassOf<T> ActorToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);
	
	void PlaceActor(TSubclassOf<AActor> ActorToSpawn, const FSpawnPosition& SpawnPosition);
	void PlaceActor(TSubclassOf<APawn> ActorToSpawn, const FSpawnPosition& SpawnPosition);

	FVector GetEmptyLocation(FVector MinPoint, FVector MaxPoint, float Radius);
	void PositionNavMeshBoundsVolume();
	void CleanUp();

	AActor* NavMeshBoundsVolume;
	UActorPool* Pool;
	TArray<AActor*> ActorsSpawnedList;
	FTimerHandle Timer;
};
