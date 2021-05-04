// Copyright Abhisek Roy. All Rights Reserved.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();

    if(AIBehavior != nullptr) 
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
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
            GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
            GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
        }else
        {
            GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
        }
    }
}
