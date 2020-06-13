// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestActor.h"
#include "Kismet/DataTableFunctionLibrary.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

// Sets default values
AQuestActor::AQuestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*static ConstructorHelpers::FObjectFinder<UDataTable> QuestActorDataObject(TEXT("DataTable'/Game/ThirdPersonCPP/Database/QuestDataTableCpp.QuestDataTableCpp'"));
	if (QuestActorDataObject.Succeeded()) 
	{
		QuestDatatable = QuestActorDataObject.Object;
		
	}*/
}

void AQuestActor::OrganiseQuestInEditor()
{
	auto parentLocation = GetAttachParentActor()->GetActorLocation();
	SetActorLocation(parentLocation);

}

// Called when the game starts or when spawned
void AQuestActor::BeginPlay()
{
	Super::BeginPlay();

	IsQuestActive = false;
	static const FString ContextString(TEXT("QuestDataTableCpp"));
	QuestDataPointer = QuestDatatable->FindRow<FQuestData>(QuestID, ContextString, true);

	if (QuestDataPointer)
	{	
		QuestData.IsStoryQuest = QuestDataPointer->IsStoryQuest;
		QuestData.objectives = QuestDataPointer->objectives;
		QuestData.QuestDescription = QuestDataPointer->QuestDescription;
		QuestData.QuestID = QuestDataPointer->QuestID;
		QuestData.QuestTitleName = QuestDataPointer->QuestTitleName;
		
		print("Validating " + QuestData.QuestTitleName.ToString(), 9);

		//GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, TEXT("DATA TABLE BEING READ "));
		//Set the variables of the quests TEXT Title and Text Description 
	/*	QuestDescriptionText = QuestDataPointer->QuestDescription;
		QuestNameText = QuestDataPointer->QuestTitleName;*/
	
	}


}


// Called every frame
void AQuestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

