// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"
#include "PlanetSixCharacter.h"
#include "InventoryComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
AItemBase::AItemBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;


    sphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
    mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = sphereCollider;
    mesh->AttachToComponent(sphereCollider, FAttachmentTransformRules::KeepRelativeTransform);

    itemData = FItemBaseData();


    //static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("R:/git/PlanetSix/Content/Geometry/Meshes/1M_Cube_Chamfer.1M_Cube_Chamfer"));
    //UStaticMesh* Asset = MeshAsset.Object;

    //mesh->SetStaticMesh(Asset);


    //init sphere
    sphereCollider->InitSphereRadius(70.0f);
    sphereCollider->SetCollisionProfileName(TEXT("Item"));


}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

FItemBaseData AItemBase::ToItemInv()
{
    //return  NewObject<UitemInv>(GetTransientPackage(), MakeUniqueObjectName(GetTransientPackage(), UitemInv::StaticClass(), TEXT("Item")));
    //auto item = FitemInv(1,TEXT("item"),2.0f,3.0f,1);

    //return item;
    return FItemBaseData(itemData.getId(), itemData.getDisplayName(), itemData.getWeight(), itemData.getValue(), itemData.getQuantity(), itemData.getIcon());
}

void AItemBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
    GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Purple, TEXT("colide"));
    auto Player = Cast<APlanetSixCharacter>(OtherActor);



    if (Player)
    {
        int NumberOfQuestItems = 2;

        //publish
        if (OnPickUp.IsBound())
        {
            NumberOfQuestItems = OnPickUp.Execute(itemData.getId(), itemData.getQuantity());
        }

        auto it = ToItemInv();

        if (Player->InventoryComponent->add(it, NumberOfQuestItems) && DestroyOnPickup)
        {
            this->Destroy();
        }
    }
}

void AItemBase::Init(FItemBaseData item)
{
    itemData = item;
}

