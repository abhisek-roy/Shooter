// Copyright Abhisek Roy. All Rights Reserved.


#include "KillEmAllGameMode.h"


void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled) 
{
    Super::PawnKilled(PawnKilled);
    
    UE_LOG(LogTemp, Warning, TEXT("%f: PawnKilled."), GetWorld()->GetTimeSeconds());
}
