// This work is the sole property of 2Pow6 Games.


#include "WeaponBase.h"
#include "PlanetSixCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "PlanetSixGameInstance.h"
#include "Engine.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)


// Sets default values
AWeaponBase::AWeaponBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SKMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = SKMeshComponent;
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	AmmoType = EAmmoType::PrimaryAmmo;
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner() != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Owner is setup yes"));
		OwnerPlayer = Cast<APlanetSixCharacter>(GetOwner());
	}
}

void AWeaponBase::Fire_Implementation()
{
	//logic of firing : can't fire if jammed
	if (bIsWeaponJammed == false)
	{
		APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
		FVector BeginCrosshair = CameraManager->GetCameraLocation();
		FVector EndCrosshair = CameraManager->GetCameraLocation() + CameraManager->GetCameraRotation().Vector() * 10000;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(OwnerPlayer);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, BeginCrosshair, EndCrosshair, ECC_Visibility, QueryParams))
		{
			DrawDebugLine(GetWorld(), BeginCrosshair, EndCrosshair, FColor::Blue, false, 1.0f, 0, 1.0f);
			FVector StartFiringLocation = MuzzleLocation->GetComponentLocation();
			FVector EndFiringLocation = Hit.Location;
			GetWorld()->LineTraceSingleByChannel(Hit, StartFiringLocation, EndFiringLocation, ECC_Visibility, QueryParams);
			DrawDebugLine(GetWorld(), StartFiringLocation, EndFiringLocation, FColor::Red, false, 1.0f, 0, 1.0f);
			auto ActorHit = Cast<ABaseCharacter>(Hit.GetActor());
			if (ActorHit != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("LIFE OF ENEMY : %f DAMAGE INFLICTED : %f"), ActorHit->Attributes->Health.GetCurrentValue(), OwnerPlayer->WeaponDamage()));
				ActorHit->ReceiveDamage(OwnerPlayer->WeaponDamage());
				if (ActorHit->IsDead())
				{
					//To check if Quest has a Killing condition
					UPlanetSixGameInstance* GameInstance = Cast<UPlanetSixGameInstance>(GetGameInstance());
					int objectiveNumber = GameInstance->GetCurrentQuest().AtObjectiveNumber;
					FQuestData CurrentQuest = GameInstance->GetCurrentQuest();
					if (CurrentQuest.objectives.Num() > 0) {
						if (CurrentQuest.objectives[objectiveNumber].LocationToGo == UGameplayStatics::GetCurrentLevelName(GetWorld())) {
							if (CurrentQuest.objectives[objectiveNumber].Objectivetype == EObjectiveType::Kill)
							{
								if (CurrentQuest.objectives[objectiveNumber].Targets.Contains(0))
								{
									if (Cast<ABaseCharacter>(Hit.GetActor())) 
									{
										GameInstance->ReduceCurrentTargetNumber(0);
										CurrentQuest = GameInstance->GetCurrentQuest();
										print("This many targets left: " + FString::FromInt(CurrentQuest.objectives[objectiveNumber].Targets[0]), -1);

										if (CurrentQuest.objectives[objectiveNumber].Targets[0] <= 0) 
										{

											//Generic Target completed when done once // Will have to edit when more IDs are added for the enemy
											CurrentQuest.objectives[objectiveNumber].IsCompleted = true;
											GameInstance->MoveToNextObjective();
											print("Finished Objective number " + FString::FromInt(objectiveNumber + 1), -1);
											//Success
										}
									}
								}
							}
						}
					}
				}
			}
		}
		AmmoInMagazine--;
		Recoil();
	}

	//did the weapon jam ? (it should be a low percentage of chance)
	bIsWeaponJammed = IsWeaponJammed();
}

void AWeaponBase::Reload()
{
	// check if owner player has enough ammo in his bag
	//if totalammo in reserves is empty OR magazine already full, don't reload
	if (OwnerPlayer->WeaponComponent->PrimaryAmmo.GetCurrentValue() <= 0 || AmmoInMagazine >= AmmoMaxInMagazine)
	{
		return;
	}
	//reload
	else
	{
		//if totalammo in reserves and in the magazine is less than the full size of a magazine, reload what's left of ammo.
		if (OwnerPlayer->WeaponComponent->PrimaryAmmo.GetCurrentValue() + AmmoInMagazine < AmmoMaxInMagazine)
		{
			AmmoInMagazine += OwnerPlayer->WeaponComponent->PrimaryAmmo.GetCurrentValue();
			OwnerPlayer->WeaponComponent->PrimaryAmmo.SetCurrentValue(0);
		}
		//normal reload
		else
		{
			OwnerPlayer->WeaponComponent->PrimaryAmmo.SetCurrentValue(OwnerPlayer->WeaponComponent->PrimaryAmmo.GetCurrentValue() - (AmmoMaxInMagazine - AmmoInMagazine));
			AmmoInMagazine = AmmoMaxInMagazine;
		}
	}
}

void AWeaponBase::Recoil()
{

}

void AWeaponBase::StopRecoil()
{

}

bool AWeaponBase::IsWeaponJammed()
{
	return false;
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
