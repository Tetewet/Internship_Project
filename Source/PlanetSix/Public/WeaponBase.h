// This work is the sole property of 2Pow6 Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponComponent.h"
#include "WeaponBase.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class APlanetSixCharacter;

UCLASS()
class PLANETSIX_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components")
		USkeletalMeshComponent* SKMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = Mesh, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USceneComponent* MuzzleLocation;

	/** ammo currently stored in the magazine. when shooting, this is the ammo used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 AmmoInMagazine;

	/** max ammo that can fit inside a magazine. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		int32 AmmoMaxInMagazine;

	/** max ammo that can fit inside a magazine. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		EAmmoType AmmoType;

	/** Reload Speed of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float ReloadSpeed;

	/** Fire rate of the weapon */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float FireRate;

	/** Condition of the weapon : determines if the weapon jams faster or not */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Condition")
		float WeaponCondition;

	/** Is the weapon jammed */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Condition")
		bool bIsWeaponJammed = false;

	/** when shooting, percentage of recoil */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float RecoilRate;

	/** when shooting, recoil towards up */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float RecoilPitchTop;

	/** when shooting, recoil towards bottom */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float RecoilPitchBot;

	/** when shooting, recoil towards left */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float RecoilYawLeft;

	/** when shooting, recoil towards right */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Recoil")
		float RecoilYawRight;

	bool bIsRecoiling;
	float FinalRecoilPitch;
	float FinalRecoilYaw;
	float FinalRecoilYawDirection;

	//---------------------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage")
		TSubclassOf<UDamageType> DamageType;
	//---------------------------------------------------------------------------

	/** Fires the gun when activated */
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable, Category = "Shoot Mechanics")
		void Fire();
	void Fire_Implementation();

	/** Reloads the gun when activated */
	UFUNCTION(BlueprintCallable, Category = "Shoot Mechanics")
		void Reload();

	void Recoil();
	void StopRecoil();
	bool IsWeaponJammed();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	APlanetSixCharacter* OwnerPlayer;
};
