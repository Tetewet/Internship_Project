// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseCharacter.h"
#include "Components/BoxComponent.h"
#include "AttributesComponent.h"
#include "EnemyController.h"
#include "Engine.h"
#include "PlanetSixEnemy.generated.h"

class APlanetSixCharacter;

UCLASS()
class PLANETSIX_API APlanetSixEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlanetSixEnemy(const FObjectInitializer& ObjectInitializer);
protected:

	/*UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* Collider;*/

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UFloatingPawnMovement* MovComp;

protected:
	//Enemy Stats
	FEnemyInfo Info;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called to do damage calcs and check if Enemy is dead
	//bool IsDead(float damage = 0);

	virtual void Death() override;
};
