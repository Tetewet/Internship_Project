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
};

USTRUCT(BlueprintType)
struct PLANETSIX_API FEnemyInfo
{
	GENERATED_USTRUCT_BODY()

public:
	int32 EnemyID;
	bool bIsDead;
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

	FTransform RespawnPoint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Method that lowers the health of the character it is called upon */
	UFUNCTION(BlueprintCallable)
		void ReceiveDamage(float Damage);
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

