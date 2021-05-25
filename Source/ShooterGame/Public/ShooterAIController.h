// Copyright Abhisek Roy. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

class UAIPerceptionComponent;

/**
 * AIController for the ShooterCharacter.
 */
UCLASS()
class SHOOTERGAME_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	AShooterAIController();
	
public:

	virtual void Tick(float DeltaTime) override;
	
	bool IsDead() const;

	UPROPERTY()
	TArray<AActor*> PatrolPoints;
	
protected:
	virtual void BeginPlay() override;
	
private:

	void SetupBBValues(APawn* InPawn);

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior = nullptr;

	FVector PlayerLocation;
	FVector LastKnownPlayerLocation;
	bool IsSetupDone = false;
};