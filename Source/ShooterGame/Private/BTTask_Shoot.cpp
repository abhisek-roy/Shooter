// Copyright Abhisek Roy. All Rights Reserved.


#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
#include "ShooterAIController.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AShooterCharacter* AIPawn = Cast<AShooterCharacter>( OwnerComp.GetAIOwner()->GetPawn() );
    
    if(AIPawn == nullptr)
    {
        return EBTNodeResult::Failed;
    }else
    {
        AIPawn->Shoot();
        return EBTNodeResult::Succeeded;
    }
}