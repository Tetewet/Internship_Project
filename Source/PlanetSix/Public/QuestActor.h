// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "QuestActor.generated.h"


UENUM(BlueprintType)
enum EObjectiveType 
{
	None = 0 UMETA(DisplayName = "None"),
	Kill = 1 UMETA(DisplayName = "Kill"),
	Gathering = 2 UMETA(DisplayName = "Gather"),
	TalkToNpc = 4 UMETA(DisplayName = "Talktonpc"),
	Location = 8 UMETA(DisplayName = "Location") //change to delegates 
};

USTRUCT(BlueprintType)
struct FObjectiveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	     FText ObjectiveDescription;
	
	//Type OF objective
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		TEnumAsByte<EObjectiveType> Objectivetype;

	//Target of the objective
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	//ID of Enemy,Number of Enemies,Also items 
	TMap<int,int> Targets;

	//Check if objective is complete
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool IsCompleted;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FString LocationToGo;

};

USTRUCT(BlueprintType)
struct FQuestData :public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	    int QuestID;//=questdatatable.questID

	//this is the name of the quest 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FText QuestTitleName;

	//Quest description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FText QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool IsStoryQuest;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		int AtObjectiveNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool IsQuestCompleted = false;

	//array of objective so that each quest can have a multiple objectives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		TArray<FObjectiveData> objectives;

	bool operator==(const FQuestData& Q) const;

	static FQuestData Empty() {
		FQuestData q;
		q.QuestID = -1;
		return q;
	}

};

///Quest Data FORCEINLINES
FORCEINLINE bool FQuestData::operator==(const FQuestData& Q) const
{
	return QuestID == Q.QuestID;
}

UCLASS()
class PLANETSIX_API AQuestActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AQuestActor();

	bool IsQuestActive=false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	FName QuestID;

	//The Component of the data table to be able to be read in Unreal
	FQuestData* QuestDataPointer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
	class UDataTable* QuestDatatable;

	FQuestData QuestData;

	//FText QuestNameText;
	//FText QuestDescriptionText;


	//Function to organize the quests in the  editor it attaches the location to the parent 
	UFUNCTION(CallInEditor, BlueprintCallable)
		void OrganiseQuestInEditor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
