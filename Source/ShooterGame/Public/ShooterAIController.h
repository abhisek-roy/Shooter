// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;
	bool IsDead() const;
	
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior = nullptr; 

	FVector PlayerLocation;
	FVector LastKnownPlayerLocation;
};