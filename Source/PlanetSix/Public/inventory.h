// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "inventory.generated.h"


class UitemInv;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLANETSIX_API Uinventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	Uinventory();
	Uinventory(int invSize);

	UFUNCTION(BlueprintCallable)
	bool add(UitemInv *item);
	UFUNCTION(BlueprintCallable)
		UitemInv* swap(UitemInv *item, int index);
	UFUNCTION(BlueprintCallable)
		UitemInv* take(int index);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int inventorySize;
	TArray<UitemInv*> items;
	enum sortingMode { alphabetical, price, weight, totalPrice, totalWeight };

	UFUNCTION(BlueprintCallable)
	TArray<UitemInv*> GetItems();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void heapify(int n, int i, sortingMode mode);
	void heapSort(int n, sortingMode mode);
	int compare(UitemInv *i1, UitemInv *i2, sortingMode mode);


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void sort(sortingMode mode);
		
};

	