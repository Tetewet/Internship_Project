// Fill out your copyright notice in the Description page of Project Settings.


#include "Item_base.h"
#include "InventoryComponent.h"


// Sets default values
AItem_base::AItem_base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = sphereCollider;
	mesh->AttachToComponent(sphereCollider, FAttachmentTransformRules::KeepRelativeTransform);

	//init sphere
	sphereCollider->InitSphereRadius(70.0f);
	sphereCollider->SetCollisionProfileName(TEXT("Item"));


}

// Called when the game starts or when spawned
void AItem_base::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AItem_base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FItemData AItem_base::ToItemInv()
{
	//return  NewObject<UitemInv>(GetTransientPackage(), MakeUniqueObjectName(GetTransientPackage(), UitemInv::StaticClass(), TEXT("Item")));
	//auto item = FitemInv(1,TEXT("item"),2.0f,3.0f,1);

	//return item;
	return FItemData(id, displayName, weight, value, quantity,icon);
}

