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
	FHitResult OutHit;
	FVector ShotDirection;
	bool bSuccess = GunTrace(OutHit, ShotDirection);
	
	if(bSuccess)
	{
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
			AController *OwnerController = GetOwnerController();
			CharacterHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

	// Muzzle flash and sound
	if(!ensure(MuzzleFlash)) return;
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	
	if(ShootSound) ShootSound->Play();
}

bool AGun::GunTrace(FHitResult &OutHit, FVector& ShotDirection) 
{
	AController *OwnerController = GetOwnerController();
	if (OwnerController == nullptr)
		return false;

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * Range;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	return GetWorld()->LineTraceSingleByChannel(OutHit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}
