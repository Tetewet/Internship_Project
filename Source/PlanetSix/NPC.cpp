// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include "Components/BoxComponent.h"
#include"Engine.h"

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ScenecomponentRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	ScenecomponentRoot -> AttachToComponent(skeleton, FAttachmentTransformRules::KeepRelativeTransform);
	ScenecomponentRoot = RootComponent;
	
	//Declare Mesh Component
	/*MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);*/

	//Declaring Box Component 
	boxcomponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	boxcomponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	

	//Declare TextRender
	textrender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXTRENDER"));
	textrender->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	skeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonMesh"));
	skeleton->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	


}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	textrender->SetVisibility(false);
	skeleton->PlayAnimation(AnimHI, false);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add rotation to the text NOT YET PERFECT	
	/*auto camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	textrender->SetWorldRotation(camera->GetCameraRotation());
	textrender->AddLocalRotation(FRotator(0, 180, 0));*/

}

void ANPC::NotifyActorBeginOverlap(AActor* OtherActor) //on ActorOverlap with the third person character 
{
	auto Character = Cast<APlanetSixCharacter>(OtherActor);
	Character->bIsInPerimiterOfNPC = true;
	

	if (Character != nullptr && Character->bIsInPerimiterOfNPC ==true)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Show me text"));
		//set visible the Text renderer of the NPC
		textrender->SetVisibility(true);
	}
}

void ANPC::NotifyActorEndOverlap(AActor* OtherActor)
{
	auto Character = Cast<APlanetSixCharacter>(OtherActor);
	Character->bIsInPerimiterOfNPC = false;

	if (Character != nullptr) 
	{
		//character->widgetDialogue->RemoveFromParent();
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("bye bye text"));
		textrender->SetVisibility(false);
	}
}
