// Copyright Abhisek Roy. All Rights Reserved.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    UAIPerceptionComponent* PerceptionComp = OwnerComp.GetAIOwner()->FindComponentByClass<UAIPerceptionComponent>();

    if(PerceptionComp != nullptr)
    {
        UAIPerceptionComponent::FActorPerceptionContainer::TConstIterator It = PerceptionComp->GetPerceptualDataConstIterator();
        for (; It; ++It)
        {
            const FActorPerceptionInfo& ActorPerceptionInfo = It->Value;
            AActor* DetectedActor = ActorPerceptionInfo.Target.Get();
    
            if (DetectedActor != nullptr && DetectedActor->ActorHasTag(FName("Player")))
            {
            	for (const FAIStimulus& Stimulus : ActorPerceptionInfo.LastSensedStimuli)
            	{
            		const UAISenseConfig* SenseConfig = PerceptionComp->GetSenseConfig(Stimulus.Type);
            		if (Stimulus.IsValid() && (Stimulus.IsExpired() == false) && SenseConfig)
            		{
                        UE_LOG(LogTemp, Warning, TEXT("%f: %s actors detected."), GetWorld()->GetTimeSeconds(), *DetectedActor->GetName());
            			OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), DetectedActor);
                        break;
            		}else
                    {
                        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
                    }
            	}
            }
        }
    }else
    {
        UE_LOG(LogTemp, Error, TEXT("%f: Perception component not found on %s!"), GetWorld()->GetTimeSeconds(), *OwnerComp.GetAIOwner()->GetPawn()->GetName());
    }
}
