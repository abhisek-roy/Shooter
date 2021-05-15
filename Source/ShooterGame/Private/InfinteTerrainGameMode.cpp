// Copyright Abhisek Roy. All Rights Reserved.


#include "InfinteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfinteTerrainGameMode::AInfinteTerrainGameMode()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfinteTerrainGameMode::PopulateBoundsVolumePool() 
{
    auto VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
		AddToPool(*VolumeIterator);
		++VolumeIterator;
	}
}

void AInfinteTerrainGameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd) 
{
    NavMeshBoundsVolumePool->Add(VolumeToAdd);
}

