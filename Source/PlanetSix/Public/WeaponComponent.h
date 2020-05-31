// This work is the sole property of 2Pow6 Games.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

/** Base Attributes for all characters. */
UENUM(BlueprintType)
enum class EAmmoType : uint8
{
	None UMETA(DisplayName = "None"),
	PrimaryAmmo UMETA(DisplayName = "Primary Ammo"),
	SecondaryAmmo UMETA(DisplayName = "Secondary Ammo"),
	TertiaryAmmo UMETA(DisplayName = "Tertiary Ammo"),
};

USTRUCT(BlueprintType)
struct PLANETSIX_API FAmmoData
{
	GENERATED_USTRUCT_BODY()

		FAmmoData()
		: CurrentAmmo(1.f)
		, MaxAmmo(1.f)
	{}

	FAmmoData(float DefaultValue)
		: CurrentAmmo(DefaultValue)
		, MaxAmmo(DefaultValue * 10)
	{}

	/** getter for CurrentValue */
	float GetCurrentValue() const { return CurrentAmmo; };
	/** getter for MaxValue */
	float GetMaxValue() const { return MaxAmmo; };

	/** setter for CurrentValue */
	virtual void SetCurrentValue(const float NewValue) { CurrentAmmo = NewValue; };
	/** setter for MaxValue */
	virtual void SetMaxValue(const float NewValue) { MaxAmmo = NewValue; };

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float MaxAmmo;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANETSIX_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** primary ammo currently stored in the backpack. when reloading, this is the ammo used. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
		FAmmoData PrimaryAmmo;

	/** secondary ammo currently stored in the backpack. when reloading, this is the ammo used. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
		FAmmoData SecondaryAmmo;

	/** tertiary ammo currently stored in the backpack. when reloading, this is the ammo used. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
		FAmmoData TertiaryAmmo;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Get the primary Ammo in the bag */
	UFUNCTION(BlueprintPure)
		float GetPrimaryAmmo() { return PrimaryAmmo.GetCurrentValue(); }
	/** Get the secondary Ammo in the bag */
	UFUNCTION(BlueprintPure)
		float GetSecondaryAmmo() { return SecondaryAmmo.GetCurrentValue(); }
	/** Get the tertiary Ammo in the bag */
	UFUNCTION(BlueprintPure)
		float GetTertiaryAmmo() { return TertiaryAmmo.GetCurrentValue(); }

	/** Get the primary Ammo in the bag */
	UFUNCTION(Blueprintable)
		void SetPrimaryAmmo(float NewValue) { PrimaryAmmo.SetCurrentValue(NewValue); }
	/** Get the secondary Ammo in the bag */
	UFUNCTION(Blueprintable)
		void SetSecondaryAmmo(float NewValue) { SecondaryAmmo.SetCurrentValue(NewValue); }
	/** Get the tertiary Ammo in the bag */
	UFUNCTION(Blueprintable)
		void SetTertiaryAmmo(float NewValue) { TertiaryAmmo.SetCurrentValue(NewValue); }
};
