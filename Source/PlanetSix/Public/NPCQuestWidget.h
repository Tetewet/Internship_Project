// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "NPC.h"
#include "Engine/DataTable.h"
#include "Engine.h"
#include "Components/EditableTextBox.h"
#include "NPCQuestWidget.generated.h"

class UButton;

UCLASS()
class PLANETSIX_API UNPCQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))  
		UButton* Accept;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
		UButton* Reject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
		UTextBlock* TextDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
		UTextBlock* TextName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget)) 
		UTextBlock* TextObjectives1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) /*, meta = (BindWidget)*/
		UTextBlock* TextObjectives2;

	//Reference of NPC 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuestData QuestData;


public:

	UNPCQuestWidget(const FObjectInitializer& ObjectInitializer);

	void NativeConstruct() override;


	UFUNCTION(BlueprintCallable)
		void AcceptQuest();

	UFUNCTION(BlueprintCallable)
		void RejectQuest();
	

	UFUNCTION()
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	

};
