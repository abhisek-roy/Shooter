// Copyright Abhisek Roy. All Rights Reserved.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn( GetWorld(), 0);
    SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
}

