// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"



class UTexture2D;
class AItemBase;
class APlanetSixCharacter;

USTRUCT(BlueprintType)
struct PLANETSIX_API FItemBaseData //: public UObject
{
	GENERATED_USTRUCT_BODY()

public:
	// Sets default values for this component's properties
	FItemBaseData(int Id, FString DisplayName, float Weight, float Value, int Quantity, UTexture2D* Icon)
		:id(Id),
		displayName(DisplayName),
		weight(Weight),
		value(Value),
		quantity(Quantity),
		icon(Icon)
	{}
	FItemBaseData()
		:id(0),
		displayName(),
		weight(0),
		value(0),
		quantity(0)
	{};
	FItemBaseData(FItemBaseData* original)
		:id(original->id),
		displayName(original->displayName),
		weight(original->weight),
		value(original->value),
		quantity(original->quantity),
		icon(original->icon)
	{};

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString displayName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* icon;

public:

	static int compare(FItemBaseData i1, FItemBaseData i2, ECompareField type);
		
	int getId();
	FString getDisplayName();
	float getWeight();
	float getValue();
	int getQuantity();
	UTexture2D* getIcon();

	float getTotalWeight();
	float getTotalValue();

	bool Stack(FItemBaseData other);

	FItemBaseData GetCopy(FItemBaseData original);


};

	
UENUM(BlueprintType)
enum class ESortingMode : uint8
{ 
	alphabetical UMETA(DisplayName = "Alphabetical"),
	price UMETA(DisplayName = "Price"),
	weight UMETA(DisplayName = "Weight"),
	totalPrice UMETA(DisplayName = "Total Price"),
	totalWeight UMETA(DisplayName = "Total Weight")
};


UENUM(BlueprintType)
enum class ECompareField : uint8
{
	name UMETA(DisplayName = "name"),
	price UMETA(DisplayName = "Price"),
	weight UMETA(DisplayName = "Weight"),
	id UMETA(DisplayName = "ID"),
	quantity UMETA(DisplayName = "qunatity")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANETSIX_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInventoryComponent();
	UInventoryComponent(int32 invSize);

	bool add(FItemBaseData item, int  numberOfQuestItems);
	bool addNormal(FItemBaseData item);
	bool addQuest(FItemBaseData item);

	UFUNCTION(BlueprintCallable)
		FItemBaseData swap(FItemBaseData item, int index);
	UFUNCTION(BlueprintCallable)
		FItemBaseData takeItem(int index);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 inventorySize UMETA(ExposeOnSpawn = "true");
	TArray<FItemBaseData> items;

	TArray<FItemBaseData> QuestItems;

	UFUNCTION(BlueprintCallable)
		TArray<FItemBaseData> GetItems();
	UFUNCTION(BlueprintCallable)
		TArray<FItemBaseData> GetQuestItems();

	UFUNCTION(BlueprintCallable)
		FString Test();

	APlanetSixCharacter* owner;

public:
	// Called when the game starts
	virtual void BeginPlay() override;
	int count=0;
	
	void heapify(int n, int i, ESortingMode mode);
	void heapSort(int n, ESortingMode mode);
	//int compare(FitemInv *i1, FitemInv *i2, sortingMode mode);

	

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	int GetCount();
	int GetQuestSize();

	void sort(ESortingMode mode);


};
