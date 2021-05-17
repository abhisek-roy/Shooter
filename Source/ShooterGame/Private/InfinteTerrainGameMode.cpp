// Copyright Abhisek Roy. All Rights Reserved.


#include "InfinteTerrainGameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

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


void AInfinteTerrainGameMode::PawnKilled(APawn* PawnKilled) 
{
	Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }

    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return;
        }
    }
    EndGame(true);
}

void AInfinteTerrainGameMode::EndGame(bool bIsPlayerWinner) 
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
