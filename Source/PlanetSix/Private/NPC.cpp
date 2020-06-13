// Fill out your copyright notice in the Description page of Project Settings.

#include "NPC.h"
#include"Engine.h"
#include "PlanetSixPlayerState.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::Orange,text)

// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Declaring Box Component 
	boxcomponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = boxcomponent;
	
	//Declare TextRender
	textrenderInteraction = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXTRENDERInteraction"));
	textrenderInteraction->AttachToComponent(boxcomponent, FAttachmentTransformRules::KeepRelativeTransform);

	textrenderQuest = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TEXTRENDERQuest"));
	textrenderQuest->AttachToComponent(boxcomponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Declaring Skeleton of Npc
	skeleton = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletonMesh"));
	skeleton->AttachToComponent(boxcomponent, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
	//Set the visibility of the text Press F to Interact to true 
	textrenderInteraction->SetVisibility(false);
	bOnInteraction = false;
	
	if (AnimIdle) 
	{
		//Play an animtion on begin play for the NPC 
		skeleton->PlayAnimation(AnimIdle, true);
	}

	if (QuestID.IsNone()) 
	{
		print("No Quest Assigned for the NPC  ", 9);
		textrenderQuest->SetVisibility(false);

	}
	
	//Call The child actors attached to the NPC 
	static const FString ContextString(TEXT("QuestDataTableCpp"));
	QuestDataPointer = QuestDatatable->FindRow<FQuestData>(QuestID, ContextString, true);

	if (QuestDataPointer)
	{
		NPCQuest.IsStoryQuest = QuestDataPointer->IsStoryQuest;
		NPCQuest.objectives = QuestDataPointer->objectives;
		NPCQuest.QuestDescription = QuestDataPointer->QuestDescription;
		NPCQuest.QuestID = QuestDataPointer->QuestID;
		NPCQuest.QuestTitleName = QuestDataPointer->QuestTitleName;

		print("Validating " + NPCQuest.QuestTitleName.ToString(), 9);

	}

}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Add rotation to the text NOT YET PERFECT	
	/*auto camera = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	textrender->SetWorldRotation(camera->GetCameraRotation());
	textrender->AddLocalRotation(FRotator(0, 180, 0));*/
	if (AnimIdle) 
	{
		if (bOnInteraction)
		{
			skeleton->PlayAnimation(AnimInteract, false);
		}
		else if (!bOnInteraction)
		{
			skeleton->PlayAnimation(AnimIdle, true);
		}
	
	}
	
}

void ANPC::NotifyActorBeginOverlap(AActor* OtherActor) //on ActorOverlap with the third person character 
{
	//auto x = Cast<ACharacter>(OtherActor);
	//
	//if (x) 
	//{

	//	/*if (x->GetPlayerState() == UGameplayStatics::GetPlayerControllerFromID(GetWorld(),0)->PlayerState) 
	//	{
	//		auto y = Cast<APlanetSixPlayerState>(x->GetPlayerState());
	//		print(y->GetPlayerName(), -1);
	//	}*/
	//}

}


void ANPC::NotifyActorEndOverlap(AActor* OtherActor)
{
	
	bOnInteraction = false;

}
