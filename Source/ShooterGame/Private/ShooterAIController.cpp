// Copyright Abhisek Roy. All Rights Reserved.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
#include "PatrolRoute.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
    RunBehaviorTree(AIBehavior);

    if(AIBehavior != nullptr) 
    {
        // Set up BlackBoard variables
        if(!GetPawn()) return;
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
        AActor* AIEnemy = Cast<AActor>(GetPawn());
        UPatrolRoute* PatrolRouteComp = AIEnemy ? AIEnemy->FindComponentByClass<UPatrolRoute>() : nullptr;
        if(PatrolRouteComp != nullptr)
        {
            PatrolPoints = PatrolRouteComp->GetPatrolPoints();
            auto PatrolPointsNum = PatrolPoints.Num();
            if (PatrolPointsNum > 0)
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
