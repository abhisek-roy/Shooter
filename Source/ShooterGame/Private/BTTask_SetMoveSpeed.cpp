// Copyright Abhisek Roy. All Rights Reserved.


#include "BTTask_SetMoveSpeed.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"

UBTTask_SetMoveSpeed::UBTTask_SetMoveSpeed() 
{
    NodeName = TEXT("Set Move Speed");
}

EBTNodeResult::Type UBTTask_SetMoveSpeed::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    ACharacter* ControlledCharacter = Cast<ACharacter>(OwnerComp.GetAIOwner()->GetPawn());
    UCharacterMovementComponent* MovementComp = ControlledCharacter ? ControlledCharacter->GetCharacterMovement() : nullptr;
    if(MovementComp != nullptr)
    {
        MovementComp->MaxWalkSpeed = Speed;
        return EBTNodeResult::Succeeded;
    }else
    {
        return EBTNodeResult::Failed;
    }
}
