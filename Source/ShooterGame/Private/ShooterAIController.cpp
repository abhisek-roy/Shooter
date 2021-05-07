// Copyright Abhisek Roy. All Rights Reserved.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
#include "PatrolGuard.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

    if(AIBehavior != nullptr) 
    {
        RunBehaviorTree(AIBehavior);
        // SetupBlackBoard()
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        APatrolGuard* AIEnemy = Cast<APatrolGuard>(GetPawn());
        if(AIEnemy != nullptr)
        {
            auto Num = AIEnemy->PatrolPoints.Num();
            UE_LOG(LogTemp, Warning, TEXT("%f: AIPatrol has %i waypoints."), GetWorld()->GetTimeSeconds(), Num);
            if (Num > 0)
            {
                GetBlackboardComponent()->SetValueAsBool(TEXT("CanPatrol"), true);                
            }else{
                GetBlackboardComponent()->ClearValue(TEXT("CanPatrol"));
            }
            GetBlackboardComponent()->SetValueAsInt(TEXT("WayPointIndex"), 0);
        }
    }
}


void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick( DeltaTime );
}

bool AShooterAIController::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());
    if (ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }

    return true;
}
