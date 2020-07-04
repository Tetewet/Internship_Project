// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlanetSixCharacter.h"
#include "PlanetSixGameInstance.generated.h"

/**
 *
 */
UCLASS()
class PLANETSIX_API UPlanetSixGameInstance : public UGameInstance
{
    GENERATED_BODY()

private:


    //PlayerCharacter values
    FPlayerInfo PlayerInfo;

public:

    UFUNCTION(BlueprintCallable)
        void SetPlayerInfo(FPlayerInfo info);

    UFUNCTION(BlueprintCallable)
        FPlayerInfo GetPlayerInfo();

    UFUNCTION(BlueprintCallable)
        void ReloadNetwork();

    //Quest Manager Functions
    UFUNCTION(BlueprintCallable)
        FQuestData GetCurrentQuest();

    UFUNCTION(BlueprintCallable)
        void SetCurrentQuest(FQuestData Quest);

  
    UFUNCTION(BlueprintCallable)
        bool GetQuestRegistered(FQuestData Quest);

    UFUNCTION(BlueprintCallable)
        void MoveToNextObjective();

    UFUNCTION(BlueprintCallable)
        void ReduceCurrentTargetNumber(int ID);

    UFUNCTION(BlueprintCallable)
        int ReduceItemNumber(int ID, int Quantity);

    
    UFUNCTION(BlueprintCallable)
        void AddQuest(FQuestData quest);
    

    UFUNCTION(BlueprintCallable)
        void AddItemsToinventoryplayer(TArray<FItemBaseData> Items);



};
