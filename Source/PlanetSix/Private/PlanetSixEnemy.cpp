// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetSixEnemy.h"
#include "PlanetSixCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/UnrealMathUtility.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

// Sets default values
APlanetSixEnemy::APlanetSixEnemy(const FObjectInitializer & ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	//Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	MovComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovComp"));
	Attributes = CreateDefaultSubobject<UAttributesComponent>(TEXT("Attributes"));
	

	/*Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetCollisionProfileName(TEXT("NoCollision"));
	Mesh->CanCharacterStepUpOn = ECB_No;	
		
	Collider->SetGenerateOverlapEvents(true);
	Collider->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	Collider->CanCharacterStepUpOn = ECB_No;
	Collider->SetNotifyRigidBodyCollision(true);*/

	AIControllerClass = AEnemyController::StaticClass();

	//RootComponent = Collider;
	//Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1,ECollisionResponse::ECR_Block);
	//Mesh->AttachToComponent(Collider, FAttachmentTransformRules::KeepRelativeTransform);

	SetReplicates(true);
}

// Called when the game starts or when spawned
void APlanetSixEnemy::BeginPlay()
{
	Super::BeginPlay();
	//Find Player
	
	
}

// Called every frame
void APlanetSixEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlanetSixEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//bool APlanetSixEnemy::IsDead(float damage) {
//
//	return Info.bIsDead;
//
//}

void APlanetSixEnemy::Death()
{
	Destroy();
}