// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skill.generated.h"

class APlanetSixCharacter;
class UTexture2D;

/** Types of damage for skills.
@ Raw is blunt damage
@ AoE is area of effect (zone)
@ DoT is damage over time (every second) */
UENUM(BlueprintType)
enum class ESkillDamageType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Raw = 1 UMETA(DisplayName = "Raw Damage"),
	AoE = 2 UMETA(DisplayName = "Area of Effect Damage"),
	DoT = 4 UMETA(DisplayName = "Damage over Time")
};

/** Types of skills.
@ Instant is instant cast skill (no activation time)
@ Passive is always active
@ Casting is activation time */
UENUM(BlueprintType)
enum class ESkillType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Instant = 1 UMETA(DisplayName = "Instant Skill"),
	Passive = 2 UMETA(DisplayName = "Passive Skill"),
	Casting = 4 UMETA(DisplayName = "Casting Skill")
	//dd = 8 UMETA(DisplayName = "Non Skill")
};

/** Types of skills.
@ Locked : skill has to be unlocked before equipping it
@ Unlocked : skill is equippable
@ Equipped : skill is castable */
UENUM(BlueprintType)
enum class ESkillStatus : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Locked = 1 UMETA(DisplayName = "Locked"),
	Unlocked = 2 UMETA(DisplayName = "Unlocked"),
	Equipped = 4 UMETA(DisplayName = "Equipped")
	//dd = 8 UMETA(DisplayName = "Non Skill")
};

UCLASS()
class PLANETSIX_API ASkill : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASkill();

	UFUNCTION(BlueprintGetter = "EnergyCost")
		float GetEnergyCost() { return EnergyCost; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float OutputDamage;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		float CharacterAbilityDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlanetSixCharacter* OwnerCharacter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float EnergyCost;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ActivationTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESkillDamageType SkillDamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESkillType SkillType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ESkillStatus SkillStatus;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* SkillIcon;

	/** factor for damage scaling on raw abilities */
	const float DamageFactor_Raw = 5.f;
	/** factor for damage scaling on area of effect abilities */
	const float DamageFactor_AoE = 7.f;
	/** factor for damage scaling on damage over time abilities */
	const float DamageFactor_DoT = 8.f;

	/** calculated raw damage the skill will inflict to another character */
	float AbilityDamage_Raw;
	/** calculated area of effect damage the skill will inflict to another character */
	float AbilityDamage_AoE;
	/** calculated damage over time damage the skill will inflict to another character */
	float AbilityDamage_DoT;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
		void DoDamage(ABaseCharacter* DamageReceiver);
};
