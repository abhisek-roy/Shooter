// Copyright Abhisek Roy. All Rights Reserved.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Checkout()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Checkout."), *GetName());
	if(Pool.Num() == 0)
	{
		return nullptr;
	}
	return Pool.Pop();
}

void UActorPool::Return(AActor* ActorToReturn)
{
	Add(ActorToReturn);
	UE_LOG(LogTemp, Warning, TEXT("[%s] Size: %i"), *GetName(), Pool.Num());
}

void UActorPool::Add(AActor* ActorToAdd)
{
	Pool.Push(ActorToAdd);
}