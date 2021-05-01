// 2021 Copyrighted, Abhisek Roy


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"

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

	FVector out_Location(0);
	FRotator out_Rotation(0);
	OwnerController->GetPlayerViewPoint(out_Location, out_Rotation);

	// To visualize the camera
	DrawDebugCamera(GetWorld(), out_Location, out_Rotation, 90, 1, FColor::Red, true );
	
	// Muzzle flash and sound
	if(!ensure(MuzzleFlash)) return;
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GunMesh, TEXT("MuzzleFlashSocket"));
	
	if(ShootSound) ShootSound->Play();
}
