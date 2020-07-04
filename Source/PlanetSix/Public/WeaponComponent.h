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
		: CurrentAmmo(60.f)
		, MaxAmmo(200.f)
	{}

	FAmmoData(float DefaultValue)
		: CurrentAmmo(DefaultValue * 10)
		, MaxAmmo(DefaultValue * 10)
	{}

	/** getter for CurrentValue */
	float GetCurrentValue() const;
	/** getter for MaxValue */
	float GetMaxValue() const;

	/** setter for CurrentValue */
	virtual void SetCurrentValue(const float NewValue);
	/** setter for MaxValue */
	virtual void SetMaxValue(const float NewValue);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float CurrentAmmo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
		float MaxAmmo;
};

UCLASS(ClassGroup = (Custom), meta = (Blueprintable))
class PLANETSIX_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	// Called when the game starts
	virtual void BeginPlay() override;

	/** primary ammo currently stored in the backpack. when reloading, this is the ammo used. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo", ReplicatedUsing = OnRep_PrimaryAmmo)
		FAmmoData PrimaryAmmo;
	/** secondary ammo currently stored in the backpack. when reloading, this is the ammo used. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo", ReplicatedUsing = OnRep_SecondaryAmmo)
		FAmmoData SecondaryAmmo;
	/** tertiary ammo currently stored in the backpack. when reloading, this is the ammo used. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo", ReplicatedUsing = OnRep_TertiaryAmmo)
		FAmmoData TertiaryAmmo;

public:
	
	void OnPrimaryAmmoUpdate();
	void OnSecondaryAmmoUpdate();
	void OnTertiaryAmmoUpdate();

	UFUNCTION()
		virtual void OnRep_PrimaryAmmo();
	UFUNCTION()
		virtual void OnRep_SecondaryAmmo();
	UFUNCTION()
		virtual void OnRep_TertiaryAmmo();

	UPROPERTY(VisibleAnywhere)
		class APawn* OwnerPawn;
};
