// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributesComponent.h"
#include "Engine.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
	: ArmorsProficiency(1.f)
	, WeaponsProficiency(1.f)
	, AbilitiesProficiency(1.f)
	, Level(1.f)
	, Experience(1.f)
	, Health(100.f)
	, Shield(10.f)
	, ArmorReduction(25.f)
	, WeaponDamage(1.f)
	, AbilityDamage(25.f)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
	
}

void UAttributesComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UAttributesComponent, ArmorsProficiency);
	DOREPLIFETIME(UAttributesComponent, WeaponsProficiency);
	DOREPLIFETIME(UAttributesComponent, AbilitiesProficiency);
	//-----------------------------------------------------------
	DOREPLIFETIME(UAttributesComponent, Level);
	DOREPLIFETIME(UAttributesComponent, Experience);
	DOREPLIFETIME(UAttributesComponent, Health);
	DOREPLIFETIME(UAttributesComponent, Shield);
	//-----------------------------------------------------------
	DOREPLIFETIME(UAttributesComponent, ArmorReduction);
	DOREPLIFETIME(UAttributesComponent, WeaponDamage);
	DOREPLIFETIME(UAttributesComponent, AbilityDamage);
}

// Called when the game starts
void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	SetActive(true);
	SetIsReplicated(true);
}

//** getter for base value of attribute */
float FAttributesData::GetBaseValue() const
{
	return BaseValue;
}

//** getter for current value of attribute */
float FAttributesData::GetCurrentValue() const
{
	return CurrentValue;
}

float FAttributesData::GetMaxValue() const
{
	return MaxValue;
}

//** setter for current value of attribute */
void FAttributesData::SetCurrentValue(const float NewValue)
{
	CurrentValue = NewValue;
}

void FAttributesData::SetMaxValue(const float AddedValue)
{
	MaxValue = BaseValue + AddedValue;
}

int32 FAttributesData::GetCurrentModifier() const
{
	return CurrentModifier;
}

void UAttributesComponent::OnArmorsProficiencyUpdate()
{

}

void UAttributesComponent::OnWeaponsProficiencyUpdate()
{

}

void UAttributesComponent::OnAbilitiesProficiencyUpdate()
{

}

void UAttributesComponent::OnLevelUpdate()
{
	//client-specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->IsLocallyControlled())
	{
		FString levelMessage = FString::Printf(TEXT("You are now level %f ."), Level.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, levelMessage);
	}

	//server specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->GetLocalRole() == ROLE_Authority)
	{
		FString levelMessage = FString::Printf(TEXT("%s now is level %f ."), *GetFName().ToString(), Level.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, levelMessage);
	}

	//functions that occur on all machines.
	/** Any special functionality that should occur as a result of leveling should be placed here */

}

void UAttributesComponent::OnExperienceUpdate()
{
	//client-specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->IsLocallyControlled())
	{
		FString expMessage = FString::Printf(TEXT("You now have %f experience."), Experience.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, expMessage);
	}

	//server specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->GetLocalRole() == ROLE_Authority)
	{
		FString expMessage = FString::Printf(TEXT("%s now has %f experience."), *GetFName().ToString(), Experience.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, expMessage);
	}

	//functions that occur on all machines.
	/** Any special functionality that should occur as a result of gaining experience should be placed here */

}

void UAttributesComponent::OnCurrentHealthUpdate()
{
	//client-specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->IsLocallyControlled())
	{
		FString healthMessage = FString::Printf(TEXT("You now have %f health remaining."), Health.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, healthMessage);

		if (Health.GetCurrentValue() <= 0)
		{
			FString deathMessage = FString::Printf(TEXT("You are dead. Waiting for revive..."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, deathMessage);
		}
	}

	//server specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->GetLocalRole() == ROLE_Authority)
	{
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), Health.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, healthMessage);
	}

	//functions that occur on all machines.
	/** Any special functionality that should occur as a result of damage or death should be placed here */

}

void UAttributesComponent::OnCurrentShieldUpdate()
{
	//client-specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->IsLocallyControlled())
	{
		FString shieldMessage = FString::Printf(TEXT("You now have %f shield remaining."), Shield.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, shieldMessage);

		if (Shield.GetCurrentValue() <= 0)
		{
			FString zeroMessage = FString::Printf(TEXT("Your shield is depleted."));
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, zeroMessage);
		}
	}

	//server specific functionality
	if (OwnerPawn != nullptr && OwnerPawn->GetLocalRole() == ROLE_Authority)
	{
		FString shieldMessage = FString::Printf(TEXT("%s now has %f shield remaining."), *GetFName().ToString(), Shield.GetCurrentValue());
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, shieldMessage);
	}

	//functions that occur on all machines.
	/** Any special functionality that should occur as a result of damage to shield or lack of shield should be placed here */

}

void UAttributesComponent::OnArmorReductionUpdate()
{

}

void UAttributesComponent::OnWeaponDamageUpdate()
{

}

void UAttributesComponent::OnAbilityDamageUpdate()
{

}

#pragma region OnRep_Attributes
//this is all for rep_notifies : everytime a value is changed, the engine calls this for multiplayer purposes
void UAttributesComponent::OnRep_ArmorsProficiency() { UAttributesComponent::OnArmorsProficiencyUpdate(); }
void UAttributesComponent::OnRep_WeaponsProficiency() { UAttributesComponent::OnWeaponsProficiencyUpdate(); }
void UAttributesComponent::OnRep_AbilitiesProficiency() { UAttributesComponent::OnAbilitiesProficiencyUpdate(); }
//-----------------------------------------------------------------------------------------------------------------
void UAttributesComponent::OnRep_Level() { UAttributesComponent::OnLevelUpdate(); }
void UAttributesComponent::OnRep_Experience() { UAttributesComponent::OnExperienceUpdate(); }
void UAttributesComponent::OnRep_CurrentHealth() { UAttributesComponent::OnCurrentHealthUpdate(); }
void UAttributesComponent::OnRep_CurrentShield() { UAttributesComponent::OnCurrentShieldUpdate(); }
//-----------------------------------------------------------------------------------------------------------------
void UAttributesComponent::OnRep_ArmorReduction() { UAttributesComponent::OnArmorReductionUpdate(); }
void UAttributesComponent::OnRep_WeaponDamage() { UAttributesComponent::OnWeaponDamageUpdate(); }
void UAttributesComponent::OnRep_AbilityDamage() { UAttributesComponent::OnAbilityDamageUpdate(); }
#pragma endregion