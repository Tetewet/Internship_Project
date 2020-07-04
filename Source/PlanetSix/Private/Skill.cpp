// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "Engine/Texture2D.h"
#include "Engine/DataTable.h"
#include "DrawDebugHelpers.h"
#include "PlanetSixCharacter.h"
#include "PlanetSixEnemy.h"

// Sets default values
ASkill::ASkill()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASkill::BeginPlay()
{
	Super::BeginPlay();

	if (GetInstigator<APlanetSixCharacter>() != nullptr)
	{
		OwnerCharacter = GetInstigator<APlanetSixCharacter>();
	}

	if (ActivationTime != 0)
	{
		Duration += ActivationTime;
	}


	SetReplicates(true);
}

FString GetEnumSkillText(ENetRole Role)
{
	switch (Role)
	{
	case ROLE_None:
		return "None";
	case ROLE_SimulatedProxy:
		return "SimulatedProxy";
	case ROLE_AutonomousProxy:
		return "AutonomousProxy";
	case ROLE_Authority:
		return "Authority";
	case ROLE_MAX:
		return "ERROR";
	default:
		break;
	}
	return "ERROR";
}

// Called every frame
void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Duration -= DeltaTime;
	ActivationTime -= DeltaTime;
	CurrentCooldown -= DeltaTime;

	DrawDebugString(GetWorld(), FVector(0, 0, 50), GetEnumSkillText(GetLocalRole()), this, FColor::White, DeltaTime);
}

/** Inflict Damage to the receiver depending on the caster's abilitydamage.
@PARAMS DamageReceiver is the person who will receive damage.*/
void ASkill::DoDamage_Implementation(APlanetSixEnemy* DamageReceiver)
{
	float AbilityDamage = OwnerCharacter->Attributes->AbilityDamage.GetCurrentValue();
	//ability damage depending on their type
	AbilityDamage_Raw = AbilityDamage / DamageFactor_Raw;
	AbilityDamage_AoE = AbilityDamage / DamageFactor_AoE;
	AbilityDamage_DoT = AbilityDamage / DamageFactor_DoT;

	//random chances for critical here

	//inflict damage depending on the skill's damage type
	switch (SkillDamageType)
	{
	case ESkillDamageType::None:
		break;
	case ESkillDamageType::Raw:
		DamageReceiver->ReceiveDamage(AbilityDamage_Raw);
		break;
	case ESkillDamageType::AoE:
		DamageReceiver->ReceiveDamage(AbilityDamage_AoE);
		break;
	case ESkillDamageType::DoT:
		DamageReceiver->ReceiveDamage(AbilityDamage_DoT);
		break;
	default:
		break;
	}
}

/** Heals the receiver depending on the caster's abilitydamage.
@PARAMS HealReceiver is the person who will receive heals.*/
void ASkill::DoHealthRegen_Implementation(APlanetSixCharacter* HealReceiver)
{
	float AbilityHeal = OwnerCharacter->Attributes->AbilityDamage.GetCurrentValue();
	//ability heal depending on abilities proficiency
	AbilityDamage_Raw = AbilityHeal / DamageFactor_Raw;
	AbilityDamage_AoE = AbilityHeal / DamageFactor_AoE;
	AbilityDamage_DoT = AbilityHeal / DamageFactor_DoT;

	//random chances for critical here

	//inflict damage depending on the skill's damage type
	switch (SkillDamageType)
	{
	case ESkillDamageType::None:
		break;
	case ESkillDamageType::Raw:
		HealReceiver->HealthRegen(AbilityDamage_Raw);
		break;
	case ESkillDamageType::AoE:
		HealReceiver->HealthRegen(AbilityDamage_AoE);
		break;
	case ESkillDamageType::DoT:
		HealReceiver->HealthRegen(AbilityDamage_DoT);
		break;
	default:
		break;
	}
}


/** Heals the receiver<s shields depending on the caster's abilitydamage.
@PARAMS HealReceiver is the person who will receive shield heals.*/
void ASkill::DoShieldRegen_Implementation(APlanetSixCharacter* HealReceiver)
{
	float AbilityHeal = OwnerCharacter->Attributes->AbilityDamage.GetCurrentValue();
	//ability heal depending on abilities proficiency
	AbilityDamage_Raw = AbilityHeal / DamageFactor_Raw;
	AbilityDamage_AoE = AbilityHeal / DamageFactor_AoE;
	AbilityDamage_DoT = AbilityHeal / DamageFactor_DoT;

	//random chances for critical here

	//inflict damage depending on the skill's damage type
	switch (SkillDamageType)
	{
	case ESkillDamageType::None:
		break;
	case ESkillDamageType::Raw:
		HealReceiver->ShieldRegen(AbilityDamage_Raw);
		break;
	case ESkillDamageType::AoE:
		HealReceiver->ShieldRegen(AbilityDamage_AoE);
		break;
	case ESkillDamageType::DoT:
		HealReceiver->ShieldRegen(AbilityDamage_DoT);
		break;
	default:
		break;
	}
}