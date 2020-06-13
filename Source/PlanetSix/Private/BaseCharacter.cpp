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
}

void ABaseCharacter::ReceiveDamage(float Damage)
{
	if (Attributes->Shield.GetCurrentValue() > 0)
	{
		Attributes->Shield.SetCurrentValue(Attributes->Shield.GetCurrentValue() - (Damage * (1 - (Attributes->ArmorReduction.GetCurrentValue() / 100))));
	}
	else if (Attributes->Health.GetCurrentValue() > 0)
	{
		Attributes->Health.SetCurrentValue(Attributes->Health.GetCurrentValue() - (Damage * (1 - (Attributes->ArmorReduction.GetCurrentValue() / 100))));
	}
}

float ABaseCharacter::WeaponDamage()
{
	return Attributes->WeaponDamage.GetCurrentValue() + FMath::CeilToFloat(FMath::Sqrt(Attributes->Level.GetCurrentValue() * 10));
}

bool ABaseCharacter::IsDead()
{

	return Attributes->Health.GetCurrentValue() <= 0;
}

void ABaseCharacter::Death()
{

}

