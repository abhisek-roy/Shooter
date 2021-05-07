// Copyright Abhisek Roy. All Rights Reserved.


#include "BTTask_UpdateNextWaypoint.h"
#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_UpdateNextWaypoint::UBTTask_UpdateNextWaypoint() 
{
    NodeName = TEXT("Update Next Waypoint");
}


EBTNodeResult::Type UBTTask_UpdateNextWaypoint::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    auto BlackboardComp = OwnerComp.GetBlackboardComponent();

    AShooterAIController* AIOwner = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
    
    if(AIOwner != nullptr)
    {
        auto Num = AIOwner->PatrolPoints.Num();
        if (Num > 0)
        {
            int32 NextIndex = (BlackboardComp->GetValueAsInt(WayPointIndex.SelectedKeyName) + 1) % Num;

            BlackboardComp->SetValueAsObject(NextWayPoint.SelectedKeyName, AIOwner->PatrolPoints[NextIndex]);
            BlackboardComp->SetValueAsInt( WayPointIndex.SelectedKeyName, NextIndex);
            return EBTNodeResult::Succeeded;
        }else{
            return EBTNodeResult::Failed; 
        }
    }
    else
    {
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Failed;
}
