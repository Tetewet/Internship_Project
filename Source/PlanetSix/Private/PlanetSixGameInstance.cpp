// Fill out your copyright notice in the Description page of Project Settings.


#include "PlanetSixGameInstance.h"
#include "PlanetSixPlayerState.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)


void UPlanetSixGameInstance::SetPlayerInfo(FPlayerInfo info)
{
	PlayerInfo = info;

	ReloadNetwork();
}

FPlayerInfo UPlanetSixGameInstance::GetPlayerInfo()
{
	return PlayerInfo;
}

FQuestData UPlanetSixGameInstance::GetCurrentQuest()
{
	return PlayerInfo.QuestAccepted;
}

void UPlanetSixGameInstance::ReduceCurrentTargetNumber(int ID)
{
	 PlayerInfo.QuestAccepted.objectives[PlayerInfo.QuestAccepted.AtObjectiveNumber].Targets[ID]--;
	 print("Targets reduced by one",-1);
	 ReloadNetwork();

}

void UPlanetSixGameInstance::MoveToNextObjective()
{
	PlayerInfo.QuestAccepted.AtObjectiveNumber++;
	if (PlayerInfo.QuestAccepted.AtObjectiveNumber >= PlayerInfo.QuestAccepted.objectives.Num()) {
		PlayerInfo.QuestAccepted.IsQuestCompleted = true;
		Cast<APlanetSixCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->QuestCompletedWidget->AddToViewport();
		for (FQuestData q : PlayerInfo.QuestsRegistered) 
		{
			if (q.QuestID == PlayerInfo.QuestAccepted.QuestID) {
				q.IsQuestCompleted = true;
				PlayerInfo.QuestAccepted = FQuestData::Empty();
					break;
			}
		}
	}
	ReloadNetwork();

}



void UPlanetSixGameInstance::SetCurrentQuest(FQuestData Quest)
{
	PlayerInfo.QuestAccepted = Quest;
	print("Setting Quest" + PlayerInfo.QuestAccepted.QuestTitleName.ToString(), -1);
	ReloadNetwork();

}

void UPlanetSixGameInstance::AddQuest(FQuestData Quest)
{
	if (!PlayerInfo.QuestsRegistered.Contains(Quest)) {
		
		PlayerInfo.QuestsRegistered.Add(Quest);
		PlayerInfo.QuestsRegistered.Sort([](const FQuestData& a, const FQuestData& b) {return a.QuestID < b.QuestID; });
		ReloadNetwork();
	}
	else {
		print("Quest already registered", -1);
	}
}

void UPlanetSixGameInstance::ReloadNetwork()
{
	APlanetSixPlayerState* PlayerState = GetPrimaryPlayerController()->GetPlayerState<APlanetSixPlayerState>();
	PlayerState->ReloadPlayerInfo();

}
