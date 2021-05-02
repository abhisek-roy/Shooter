// Copyright Abhisek Roy. All Rights Reserved.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();
}


void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick( DeltaTime );

    auto AIPlayer = Cast<AShooterCharacter>(GetPawn());
    if(!AIPlayer) return;
    if(AIPlayer->IsDead())
    {
        AIPlayer->DetachFromControllerPendingDestroy();
    }else
    {
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0);
        if(!PlayerPawn) return;

        if(LineOfSightTo( PlayerPawn, FVector(0), false)) 
        {
            MoveToActor(PlayerPawn, AcceptanceRadius);
            SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
        }else
        {
            ClearFocus(EAIFocusPriority::Gameplay);
            StopMovement();
        }
    }
}
