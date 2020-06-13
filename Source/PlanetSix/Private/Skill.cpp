// Fill out your copyright notice in the Description page of Project Settings.


#include "Skill.h"
#include "Engine/Texture2D.h"
#include "PlanetSixCharacter.h"

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

// Called every frame
void ASkill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Duration -= DeltaTime;
	ActivationTime -= DeltaTime;
}

/** Inflict Damage to the receiver depending on the caster's abilitydamage.
@PARAMS DamageReceiver is the person who will receive damage.*/
void ASkill::DoDamage(ABaseCharacter* DamageReceiver)
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