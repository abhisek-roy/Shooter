// Copyright Abhisek Roy. All Rights Reserved.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
#include "PatrolRoute.h"

AShooterAIController::AShooterAIController() 
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
    RunBehaviorTree(AIBehavior);
}

void AShooterAIController::Tick(float DeltaTime) 
{
    Super::Tick( DeltaTime );

    if (AIBehavior != nullptr && IsSetupDone == false)
    {
        SetupBBValues(GetPawn());
        IsSetupDone = true;
    }
}

void AShooterAIController::SetupBBValues(APawn* InPawn)
{
    GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), InPawn->GetActorLocation());

    if (InPawn == nullptr)
    {
        UE_LOG(LogTemp, Warning, TEXT("%f: [%s] found no pawn"), GetWorld()->GetTimeSeconds(), *GetName());
        return;
    }

    AShooterCharacter* AIEnemy = Cast<AShooterCharacter>(InPawn);
    EEnemyTypes EnemyType = AIEnemy->GetEnemyType();

    UPatrolRoute* PatrolRouteComp = AIEnemy ? AIEnemy->FindComponentByClass<UPatrolRoute>() : nullptr;
    if (PatrolRouteComp != nullptr && EnemyType == EEnemyTypes::Patrol)
    {
        PatrolPoints = PatrolRouteComp->GetPatrolPoints();
        auto PatrolPointsNum = PatrolPoints.Num();
        if (PatrolPointsNum > 0)
        {
            GetBlackboardComponent()->SetValueAsBool(TEXT("CanPatrol"), true);
        }
        else {
            GetBlackboardComponent()->ClearValue(TEXT("CanPatrol"));
        }
        GetBlackboardComponent()->SetValueAsInt(TEXT("WayPointIndex"), 0);
    }
    
    if (EnemyType == EEnemyTypes::MoveAbout)
    {
        GetBlackboardComponent()->SetValueAsBool(TEXT("ShouldRandomSearch"), true);
    }
    else
    {
        GetBlackboardComponent()->SetValueAsBool(TEXT("ShouldRandomSearch"), false);
    }
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
