// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Blueprint/UserWidget.h"
#include "NPC.h"
#include "Engine.h"
#include "Components/EditableTextBox.h"
#include "NPCDialogueWidget.generated.h"


UCLASS()
class PLANETSIX_API UNPCDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText TextLineDialogue;

};
