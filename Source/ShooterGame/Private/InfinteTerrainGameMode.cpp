// Copyright Abhisek Roy. All Rights Reserved.


#include "InfinteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"

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
    UE_LOG(LogTemp, Warning, TEXT("Found Actor: %s"), *VolumeToAdd->GetName());
}
