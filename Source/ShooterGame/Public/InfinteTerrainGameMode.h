// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameGameModeBase.h"
#include "InfinteTerrainGameMode.generated.h"

class ANavMeshBoundsVolume;

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AInfinteTerrainGameMode : public AShooterGameGameModeBase
{
	GENERATED_BODY()
	AInfinteTerrainGameMode();

public:
	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();

private:
	void AddToPool( ANavMeshBoundsVolume *VolumeToAdd);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;
};
