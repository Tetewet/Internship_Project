// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClassComponent.generated.h"

class ASkill;
class APlanetSixCharacter;

UENUM(BlueprintType)
enum class EClassName : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Physician = 1 UMETA(DisplayName = "Physician"),
	Comissar = 2 UMETA(DisplayName = "Comissar"),
	Gunner = 4 UMETA(DisplayName = "Gunner"),
};

UENUM(BlueprintType)
enum class ESkillName : uint8
{
	None UMETA(DisplayName = "None"),
	Pylon UMETA(DisplayName = "Pylon")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANETSIX_API UClassComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UClassComponent();

	//getter for the class name
	UFUNCTION(BlueprintPure)
		FString GetClassName() { return ClassTextName; }
	//getter for the class name
	UFUNCTION(BlueprintPure)
		EClassName GetClassType() { return ClassEnumName; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<ASkill>> AvailableSkillsArray;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<ASkill>> EquippedSkillsArray;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	/** checker if the skill is unlocked or not. CAN NOT cast skill if false */
	bool bIsUnlocked = false;

	UPROPERTY(VisibleAnywhere)
		FString ClassTextName;
	UPROPERTY(VisibleAnywhere)
		FString ClassDescription;
	UPROPERTY(VisibleAnywhere)
		EClassName ClassEnumName;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Cast a Skill*/
	/*UFUNCTION(Blueprintable)
		void CastSkill(ASkill* SkillToCast, APlanetSixCharacter* Instigator);*/

	UFUNCTION(BlueprintPure, BlueprintGetter = "IsUnlocked")
		bool GetIsUnlocked() { return bIsUnlocked; }
	UFUNCTION(BlueprintCallable, BlueprintSetter = "IsUnlocked")
		void SetIsUnlocked(bool IsUnlocked) { bIsUnlocked = IsUnlocked; }

	/** Checks if skill is castable, AND Reduces energy when casting a skill */
	//bool IsSkillCastable(ASkill* SkillToCast, APlanetSixCharacter* Instigator);
};
