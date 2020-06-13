// This work is the sole property of 2Pow6 Games.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "inventoryWidget.generated.h"

/**
 *
 */
UCLASS()
class PLANETSIX_API UinventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintImplementableEvent)
    void addItemToViewport(int numOfQuestItemInInv);


};
