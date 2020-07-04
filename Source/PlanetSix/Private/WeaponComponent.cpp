// This work is the sole property of 2Pow6 Games.


#include "WeaponComponent.h"
#include "Engine.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
	: PrimaryAmmo(200.f)
	, SecondaryAmmo(10.f)
	, TertiaryAmmo(5.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponComponent, PrimaryAmmo);
	DOREPLIFETIME(UWeaponComponent, SecondaryAmmo);
	DOREPLIFETIME(UWeaponComponent, TertiaryAmmo);
}

// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, FString::Printf(TEXT("%f, %f, %f"), PrimaryAmmo.CurrentAmmo, SecondaryAmmo.CurrentAmmo, TertiaryAmmo.CurrentAmmo));
	PrimaryAmmo.SetCurrentValue(2000);
}

void UWeaponComponent::OnPrimaryAmmoUpdate()
{

}

void UWeaponComponent::OnSecondaryAmmoUpdate()
{

}

void UWeaponComponent::OnTertiaryAmmoUpdate()
{

}

#pragma region OnRep_Attributes
//this is all for rep_notifies : everytime a value is changed, the engine calls this for multiplayer purposes
void UWeaponComponent::OnRep_PrimaryAmmo() { UWeaponComponent::OnPrimaryAmmoUpdate(); }
void UWeaponComponent::OnRep_SecondaryAmmo() { UWeaponComponent::OnSecondaryAmmoUpdate(); }
void UWeaponComponent::OnRep_TertiaryAmmo() { UWeaponComponent::OnTertiaryAmmoUpdate(); }
#pragma endregion

float FAmmoData::GetCurrentValue() const
{
	return CurrentAmmo;
}

float FAmmoData::GetMaxValue() const
{
	return MaxAmmo;
}

void FAmmoData::SetCurrentValue(const float NewValue)
{
	CurrentAmmo = NewValue;
}

void FAmmoData::SetMaxValue(const float NewValue)
{
	MaxAmmo = NewValue;
}
