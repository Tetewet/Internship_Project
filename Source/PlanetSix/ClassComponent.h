// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ClassComponent.generated.h"

UENUM(BlueprintType)
enum class EClassName : uint8
{
	None UMETA(DisplayName = "None"),
	//pirate faction classes :
	Pir_Surgeon UMETA(DisplayName = "Pir_Surgeon"),
	Pir_QuarterMaster UMETA(DisplayName = "Pir_QuarterMaster"),
	Pir_Gunner UMETA(DisplayName = "Pir_Gunner"),
	//vanguard faction classes :
	Van_Physicien UMETA(DisplayName = "Van_Physicien"),
	Van_Brigadier UMETA(DisplayName = "Van_Brigadier"),
	Van_Volontaire UMETA(DisplayName = "Van_Volontaire"),
	//Unionists faction classes :
	Uni_Sanitar UMETA(DisplayName = "Uni_Sanitar"),
	Uni_Comissar UMETA(DisplayName = "Uni_Comissar"),
	Uni_Comrade UMETA(DisplayName = "Uni_Comrade")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PLANETSIX_API UClassComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UClassComponent();
	//getter for the class name
	EClassName GetClassName();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		FName ClassName;
	UPROPERTY(VisibleAnywhere)
		FString ClassDescription;
	UPROPERTY(VisibleAnywhere)
		EClassName ClassEnumName;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
