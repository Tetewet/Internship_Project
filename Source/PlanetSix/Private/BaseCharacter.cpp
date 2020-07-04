// This work is the sole property of 2Pow6 Games.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ABaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	RespawnPoint = GetActorTransform();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsDead())
	{
		Death();
	}
	//HealthRegenTime -= DeltaTime;
	/*if (HealthRegenTime <= 0)
	{
		HealthRegen(RecoveryValue);
		HealthRegenTime = 2.f;
	}*/
}

void ABaseCharacter::ReloadShields_Implementation(float DeltaTime)
{
	ShieldRegenTime -= DeltaTime;
	if (ShieldRegenTime <= 0)
	{
		ShieldRegen(RecoveryValue);
		ShieldRegenTime = 2.f;
	}
}

void ABaseCharacter::ReceiveDamage_Implementation(float Damage)
{
	if (Attributes->Shield.GetCurrentValue() > 0)
	{
		Attributes->Shield.SetCurrentValue(Attributes->Shield.GetCurrentValue() - (Damage * (1 - (Attributes->ArmorReduction.GetCurrentValue() / 100))));
	}
	else if (Attributes->Health.GetCurrentValue() > 0)
	{
		Attributes->Health.SetCurrentValue(Attributes->Health.GetCurrentValue() - (Damage * (1 - (Attributes->ArmorReduction.GetCurrentValue() / 100))));
	}
	//HealthRegenTime = RecoveryTime;
	ShieldRegenTime = RecoveryTime;
}

void ABaseCharacter::HealthRegen(float Regen)
{
	if (Attributes->Health.GetCurrentValue() < Attributes->Health.GetMaxValue())
	{
		Attributes->Health.SetCurrentValue(Attributes->Health.GetCurrentValue() + Regen);
	}
	else
	{
		Attributes->Health.SetCurrentValue(Attributes->Health.GetMaxValue());
	}
}

void ABaseCharacter::ShieldRegen(float Regen)
{
	if (Attributes->Shield.GetCurrentValue() < Attributes->Shield.GetMaxValue())
	{
		Attributes->Shield.SetCurrentValue(Attributes->Shield.GetCurrentValue() + Regen);
	}
	else
	{
		Attributes->Shield.SetCurrentValue(Attributes->Shield.GetMaxValue());
	}
}

float ABaseCharacter::WeaponDamage()
{
	return Attributes->WeaponDamage.GetCurrentModifier() == 0 ? Attributes->WeaponDamage.GetCurrentValue() + FMath::CeilToFloat(FMath::Sqrt(Attributes->Level.GetCurrentValue() * 10)) : Attributes->WeaponDamage.GetCurrentValue() + FMath::CeilToFloat(FMath::Sqrt(Attributes->Level.GetCurrentValue() * 10))* Attributes->WeaponDamage.GetCurrentModifier();
}

bool ABaseCharacter::IsDead()
{

	return Attributes->Health.GetCurrentValue() <= 0;
}

void ABaseCharacter::Death()
{

}

