// 2021 Copyrighted, Abhisek Roy

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class UParticleSystemComponent;
class UAudioComponent;

UCLASS()
class SHOOTERGAME_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GunMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UParticleSystem* MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
	UAudioComponent* ShootSound = nullptr;
};

