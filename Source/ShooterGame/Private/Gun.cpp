// 2021 Copyrighted, Abhisek Roy


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "ShooterCharacter.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName(TEXT("Root")));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName(TEXT("GunMesh")));
	GunMesh->SetupAttachment(Root);

	ShootSound = CreateDefaultSubobject<UAudioComponent>(FName(TEXT("ShootSound")));
	ShootSound->SetupAttachment(Root);
	ShootSound->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() 
{
	// Get player viewpoint
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if(!OwnerPawn) return;

	AController* OwnerController = OwnerPawn->GetController();
	if(!OwnerController) return;

	FVector CameraLocation(0);
	FRotator CameraRotation(0);
	OwnerController->GetPlayerViewPoint(CameraLocation, CameraRotation);

	// Shot location
	FCollisionQueryParams CollisionParams(FCollisionQueryParams::DefaultQueryParam);
	CollisionParams.AddIgnoredActor(OwnerPawn);
	FHitResult OutHit;
	FVector EndPoint = CameraLocation + Range * CameraRotation.Vector();
	bool bHit = GetWorld()->LineTraceSingleByChannel(OutHit,
				CameraLocation,
				EndPoint,
				ECollisionChannel::ECC_GameTraceChannel1,
				CollisionParams, 
				FCollisionResponseParams::DefaultResponseParam
			);
	
	if(bHit)
	{
		FVector ShotDirection = - CameraRotation.Vector();

		AShooterCharacter* CharacterHit = Cast<AShooterCharacter>(OutHit.GetActor());
		if(!OutHit.GetActor()) 
		{
			return;
		}else if(!CharacterHit)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlashWorld, OutHit.Location, ShotDirection.Rotation());
		}else
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactFlashCharacter, OutHit.Location, ShotDirection.Rotation());

			FPointDamageEvent DamageEvent(Damage, OutHit, ShotDirection, nullptr);
			CharacterHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

	// Muzzle flash and sound
	if(!ensure(MuzzleFlash)) return;
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	
	if(ShootSound) ShootSound->Play();
}
