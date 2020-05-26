// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestActor.generated.h"

UENUM(BlueprintType)
enum class EObjectiveType :uint8 {
	None = 0 UMETA(DisplayName = "None"),
	Kill = 1 UMETA(DisplayName = "Kill"),
	Gathering = 2 UMETA(DisplayName = "Gather"),
	TalkToNpc = 4 UMETA(DisplayName = "Talktonpc"),
	Location = 8 UMETA(DisplayName = "Location")
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
		AActor* target;
	//Check if objective is complete
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool IsCompleted;

	//Number 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		int Number;

};




UCLASS()
class PLANETSIX_API AQuestActor : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AQuestActor();

	//this is the name of the quest 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FText QuestName;

	//Quest description
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FText QuestDescription;


	//Function to organize the quests in the  editor it attaches the location to the parent 
	UFUNCTION(CallInEditor, BlueprintCallable)
		void OrganiseQuestInEditor();

	//array of objective so that each quest can have a multiple objectives
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		TArray<FObjectiveData> objectives;

	//check if quest is active 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool IsActive;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		bool IsStoryQuest;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
