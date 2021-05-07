// Copyright Abhisek Roy. All Rights Reserved.


#include "BTDecorator_CanPatrol.h"
#include "PatrolGuard.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_CanPatrol::UBTDecorator_CanPatrol() 
{
    NodeName = TEXT("Update next waypoint.");
}


bool UBTDecorator_CanPatrol::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();

    AAIController* AIOwner = OwnerComp.GetAIOwner();
    APatrolGuard* AIEnemy = AIOwner ? Cast<APatrolGuard>(AIOwner->GetPawn()) : nullptr;
    if(AIEnemy != nullptr)
    {
        auto Num = AIEnemy->PatrolPoints.Num();
        if (Num > 0)
        {
            int32 NextIndex = (BlackboardComp->GetValueAsInt(WayPointIndex.SelectedKeyName) + 1) % Num;

            BlackboardComp->SetValueAsObject(NextWayPoint.SelectedKeyName, AIEnemy->PatrolPoints[NextIndex]);
            BlackboardComp->SetValueAsInt( WayPointIndex.SelectedKeyName, NextIndex);
            return true; // TODO true, once implemented
        }else{
            return false; 
        }
    }else{
        return false;
    }
}
