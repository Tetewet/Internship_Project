// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCQuestWidget.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::Orange,text)

UNPCQuestWidget::UNPCQuestWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {


}

void UNPCQuestWidget::NativeConstruct() {

	Super::NativeConstruct();

	Accept->OnClicked.AddDynamic(this, &UNPCQuestWidget::AcceptQuest);
	Reject->OnClicked.AddDynamic(this, &UNPCQuestWidget::RejectQuest);
	
	

	/*TextName->Text = QuestData.QuestTitleName;
	TextDescription->Text = QuestData.QuestDescription;*/

	
}

void UNPCQuestWidget::AcceptQuest()
{

	RemoveFromParent();
/*	if (NPCRef) 
	{
		NPCRef->SpecifiedQuestOFNPC->IsQuestActive = true;
	}*/


	
}

void UNPCQuestWidget::RejectQuest()
{
	
	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("questrejected"));

}


void UNPCQuestWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	TextName->SetText(QuestData.QuestTitleName);
	TextDescription->SetText( QuestData.QuestDescription);

	//most consuming Thing i have ever used but it works -Youcef
	for (int32 i = 0; i < QuestData.objectives.Num(); i++)
	{
		TextObjectives1->SetText(QuestData.objectives[i].ObjectiveDescription);
		/*TextObjectives2->SetText(QuestData.objectives[i].ObjectiveDescription);*/
	}
	
	print("Printing " + QuestData.QuestTitleName.ToString(), 9);
	

}