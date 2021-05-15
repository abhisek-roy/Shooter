// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class UActorPool;

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Pool")
	void SetPool(UActorPool* Pool);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);

private:
	bool IsEmptySpace(FVector Location, float Radius);
	void PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector Location, float Yaw, float Scale);
	FVector GetEmptyLocation(FVector MinPoint, FVector MaxPoint, float Radius);
	void PositionNavMeshBoundsVolume();

	AActor* NavMeshBoundsVolume;
	UActorPool* Pool;
};
