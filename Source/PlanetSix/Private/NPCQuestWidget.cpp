// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCQuestWidget.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::Orange,text)

UNPCQuestWidget::UNPCQuestWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {


}

void UNPCQuestWidget::NativeConstruct() {

	Super::NativeConstruct();

	Accept->OnClicked.AddDynamic(this, &UNPCQuestWidget::AcceptQuest);
	Reject->OnClicked.AddDynamic(this, &UNPCQuestWidget::RejectQuest);
	
	
}

void UNPCQuestWidget::AcceptQuest()
{
	QuestDataNPC->NPCQuest.IsQuestRegistered= true;
	
}

void UNPCQuestWidget::RejectQuest()
{
	
}


void UNPCQuestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TextName->SetText(QuestDataNPC->NPCQuest.QuestTitleName);
	TextDescription->SetText(QuestDataNPC->NPCQuest.QuestDescription);

	//most consuming Thing i have ever used but it works -Youcef
	for (int32 i = 0; i < QuestDataNPC->NPCQuest.objectives.Num(); i++)
	{
		TextObjectives1->SetText(QuestDataNPC->NPCQuest.objectives[i].ObjectiveDescription);
		/*TextObjectives2->SetText(QuestData.objectives[i].ObjectiveDescription);*/
	}
	
	print("Printing " + QuestDataNPC->NPCQuest.QuestTitleName.ToString(), 9);
	

}