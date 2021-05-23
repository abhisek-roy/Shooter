// Copyright Abhisek Roy. All Rights Reserved.


#include "BTTask_PlayerVisible.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTTask_PlayerVisible::UBTTask_PlayerVisible() 
{
    NodeName = TEXT("Is Player visible?");
}

EBTNodeResult::Type UBTTask_PlayerVisible::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    UObject* PlayerObj = OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey());
    AActor* Player = Cast<AActor>(PlayerObj);
    AAIController* AIOwner = OwnerComp.GetAIOwner();

    if(Player != nullptr && AIOwner !=nullptr)
    {
        if(AIOwner->LineOfSightTo(Player))
        {
            return EBTNodeResult::Succeeded;
        }
        else
        {
            return EBTNodeResult::Failed;
        }
    }else
    {
        return EBTNodeResult::Failed;
    }
    return EBTNodeResult::Failed;
}
