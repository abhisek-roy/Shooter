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
	virtual void PawnKilled(APawn* PawnKilled) override;

private:
	void AddToPool( ANavMeshBoundsVolume *VolumeToAdd);
	void EndGame(bool bIsPlayerWinner);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pool")
	class UActorPool* NavMeshBoundsVolumePool;
};
