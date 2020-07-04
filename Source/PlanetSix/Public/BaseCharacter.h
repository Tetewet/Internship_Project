// This work is the sole property of 2Pow6 Games.

#pragma once

#include "CoreMinimal.h"
#include "AttributesComponent.h"
#include "QuestActor.h"
#include "ClassComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

#pragma region(USTRUCTS)
USTRUCT(BlueprintType)
struct PLANETSIX_API FPlayerInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		FString UserName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		TArray<FQuestData> QuestsRegistered;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		FQuestData QuestAccepted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Info")
		TMap<int,int> InventoryItemsID;

};


#pragma endregion

UCLASS(config = Game)
class PLANETSIX_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	/** Property replication */
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Player's attributes. */
	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		UAttributesComponent* Attributes;

	/** Player's class. */
	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		UClassComponent* Class;

	///** Character's regeneration of health*/
	//UPROPERTY(BlueprintReadWrite, Category = "Attributes")
	//	float HealthRegenTime;

	/** Character's regeneration of shields*/
	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		float ShieldRegenTime;

	/** Character's time after which he will start recovering*/
	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		float RecoveryTime = 8.f;

	/** Character's value of recovery*/
	UPROPERTY(BlueprintReadWrite, Category = "Attributes")
		float RecoveryValue = 5.f;

	FTransform RespawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Method that lowers the health of the character it is called upon */
	UFUNCTION(BlueprintCallable, Server, Reliable)
		void ReceiveDamage(float Damage);
	void ReceiveDamage_Implementation(float Damage);
	/** Method that reloads shields over time on the server*/
	UFUNCTION(BlueprintCallable, Server, Reliable)
		void ReloadShields(float DeltaSeconds);
	void ReloadShields_Implementation(float DeltaSeconds);
	/** Method that heals the character it is called upon */
	UFUNCTION(BlueprintCallable)
		void HealthRegen(float Regen);
	/** Method that heals the character it is called upon */
	UFUNCTION(BlueprintCallable)
		void ShieldRegen(float Regen);
	/** Method that returns weapon damage  */
	UFUNCTION(BlueprintCallable)
		float WeaponDamage();
	/** Method to check if dead  */
	UFUNCTION(BlueprintCallable)
		bool IsDead();
	/** Method that is called upon death  */
	UFUNCTION(BlueprintCallable)
		virtual void Death();
};

