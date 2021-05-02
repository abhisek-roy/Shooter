// Copyright Abhisek Roy. All Rights Reserved.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0);
    SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
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
        if(PlayerPawn) 
        {
            MoveToActor(PlayerPawn, AcceptanceRadius, false, true, true, nullptr, false);
        }else
        {
            SetFocus(PlayerPawn, EAIFocusPriority::Move);
        }
    }
}
