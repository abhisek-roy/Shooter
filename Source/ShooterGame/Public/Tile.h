// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor> ActorToSpawn, int32 MinSpawn = 1, int32 MaxSpawn = 1, float Radius = 300, float MinScale = 1, float MaxScale = 1);

private:
	bool IsEmptySpace(FVector Location, float Radius);
	void PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector Location, float Yaw, float Scale);
	FVector GetEmptyLocation(FVector MinPoint, FVector MaxPoint, float Radius);
};
