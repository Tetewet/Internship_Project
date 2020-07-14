// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Engine.h"
#include "Components/CanvasPanel.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "PlanetSixSaveGame.h"
#include "PlanetSixGameInstance.h"
#include "PlanetSixPlayerState.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {


}

void UMainMenuWidget::NativeConstruct() {
	Super::NativeConstruct();

	StartButton->OnClicked.AddDynamic(this, &UMainMenuWidget::StartGame);
	OptionsButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OpenOptions);
	ExitButton->OnClicked.AddDynamic(this, &UMainMenuWidget::ExitGame);
	

	GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
	GetWorld()->GetFirstPlayerController()->SetInputMode(FInputModeUIOnly());
}

void UMainMenuWidget::StartGame()
{
	print("Start Game", -1);

	
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, RefStartGameWidget);
	if (FoundWidgets.Num() == 0) {
		UUserWidget* StartGameWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), RefStartGameWidget);

		StartGameWidget->AddToViewport();
	}

	
	RemoveFromParent();
}

void UMainMenuWidget::OpenOptions()
{
	TArray<UUserWidget*> FoundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, RefOptionWidget);
	if (FoundWidgets.Num() == 0) {
		UUserWidget* OptionsWidget = CreateWidget<UUserWidget>(GetWorld(), RefOptionWidget);
		OptionsWidget->AddToViewport();
	}
	RemoveFromParent();

	print("OpenOptions", -1);

}

void UMainMenuWidget::ExitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetWorld()->GetFirstPlayerController(), TEnumAsByte<EQuitPreference::Type>(), false);
	print("Exit Game", -1);

}

