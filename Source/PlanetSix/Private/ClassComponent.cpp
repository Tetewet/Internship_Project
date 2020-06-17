// Fill out your copyright notice in the Description page of Project Settings.


#include "ClassComponent.h"
#include "PlanetSixCharacter.h"
#include "Skill.h"

// Sets default values for this component's properties
UClassComponent::UClassComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ClassEnumName = EClassName::Gunner;
	SkillPoints = 1;
	ClassTextName = TEXT("Gunner");
}

// Called when the game starts
void UClassComponent::BeginPlay()
{
	Super::BeginPlay();

	FString TempDescription = TEXT("BLANK"); //TODO : implement a database to change that

	//depending on the class, let's add a description to it.
	ClassDescription = TempDescription;
	
	SetIsReplicated(true);
}

// Called every frame
void UClassComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

//void UClassComponent::CastSkill(ASkill* SkillToCast, APlanetSixCharacter* Instigator)
//{
//	if (SkillToCast != nullptr && Instigator != nullptr)
//	{
//		if (IsSkillCastable(SkillToCast, Instigator))
//		{
//			/*Instigator->Attributes->Energy.SetCurrentValue(Instigator->Attributes->Energy.GetCurrentValue() - SkillToCast->GetEnergyCost());
//			FTransform NewTransform = Instigator->GetTransform();
//			NewTransform.SetLocation(Instigator->GetActorLocation() + Instigator->GetActorForwardVector() * 15.f);
//			NewTransform.SetRotation(Instigator->GetActorQuat());
//			FActorSpawnParameters SpawnParameters;
//			SpawnParameters.Instigator = Instigator;
//			SpawnParameters.Owner = Instigator;
//			const auto Transform = NewTransform;
//			const auto Spawn = SpawnParameters;
//			UWorld::SpawnActor(SkillToCast, ref Transform, ref Spawn);*/
//		}
//	}
//}

//bool UClassComponent::IsSkillCastable(ASkill* SkillToCast, APlanetSixCharacter* Instigator)
//{
//	if (SkillToCast->GetEnergyCost() <= Instigator->Attributes->Energy.GetCurrentValue())
//	{
//		return true;
//	}
//	return false;
//}