// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "InventoryComponent.h"
#include "ItemBase.generated.h"


//struct FItemData;
DECLARE_DELEGATE_RetVal_TwoParams(int, FItemPickUp, int, int)

//USTRUCT(BlueprintType)
//struct PLANETSIX_API FQuestInfo //: public UObject
//{
//	GENERATED_USTRUCT_BODY()
//
//public:
//	FQuestInfo() {};
//	FQuestInfo(int Id,int Quantity)
//		: QuestId(Id),
//		quantity(Quantity)
//	{};
//
//
//protected:
//	int QuestId;
//	int quantity;
//
//public:
//
//	
//};





UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANETSIX_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool DestroyOnPickup=true;


	FItemPickUp OnPickUp;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* mesh;
	UPROPERTY(Category = Item, VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		USphereComponent* sphereCollider;
	FRotator Rotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FItemBaseData itemData;// UMETA(ExposeOnSpawn = "true");
public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int itemId UMETA(ExposeOnSpawn = "true");

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int quantity UMETA(ExposeOnSpawn = "true");
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		FItemBaseData ToItemInv();

	void Init(FItemBaseData item);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;


	FItemBaseData* itemDataPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UDataTable* ItemDataTable;
};
