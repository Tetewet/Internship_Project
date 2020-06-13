// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "PlanetSixCharacter.h"
#include "ItemBase.h"
#include "Engine.h"


#pragma region Inventory

UInventoryComponent::UInventoryComponent()
{
    items = TArray<FItemBaseData>();
    items.Init(FItemBaseData(), 10);
    QuestItems = TArray<FItemBaseData>();
    //GEngine->AddOnScreenDebugMessage(1, 10, FColor::Emerald, TEXT("fewqef "));
    inventorySize = 10;
}



// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent(int32 invSize)
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    inventorySize = invSize;

    //items.Init(nullptr, inventorySize);


    // ...
}


TArray<FItemBaseData> UInventoryComponent::GetItems()
{
    return items;
}
TArray<FItemBaseData> UInventoryComponent::GetQuestItems()
{
    return QuestItems;
}

FString UInventoryComponent::Test()
{
    return FString::FromInt(items.Num());
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

int UInventoryComponent::GetCount()
{
    return count;
}

int UInventoryComponent::GetQuestSize()
{
    return QuestItems.Num();
}


// Description:
//   add an item to the inventory.
// Parameters:
//   item - Item to add to the inventory.
// Returns:
//   Return true if it was able to add the item, otherwise return false.
//
bool UInventoryComponent::addNormal(FItemBaseData item)
{
    //look for the first available spot.
    for (int i = 0; i < items.Num(); i++)
    {


        //if there is someting
        if (!items[i].getId() == 0)
        {
            //it item already in inventory
            //return items[i].Stack(item);

            if (items[i].Stack(item))
            {
                return true;
            }

        }
        //if empty
        else
        {
            //place the item
            items[i] = item;
            count++;
            return true;
        }
    }


    //if there is no spot left
    return false;
}

bool UInventoryComponent::addQuest(FItemBaseData item)
{
    //look for the first available spot.
    for (int i = 0; i < QuestItems.Num(); i++)
    {


        //if there is someting
        if (!QuestItems[i].getId() == 0)
        {
            //it item already in inventory
            //return items[i].Stack(item);

            if (QuestItems[i].Stack(item))
            {
                return true;
            }

        }
        //if empty
        else
        {
            //place the item
            QuestItems[i] = item;
            return true;
        }
    }

    QuestItems.Add(item);


    //if there is no spot left
    return false;
}

// Description:
//   add an item to the inventory.
// Parameters:
//   item - Item to add to the inventory.
//	  numberOfQuestItems - Number of items to put in the quest inventory
// Returns:
//   Return true if it was able to add the item, otherwise return false.
//
bool UInventoryComponent::add(FItemBaseData item, int  numberOfQuestItems)
{
    if (numberOfQuestItems > item.quantity)
    {
        numberOfQuestItems = item.quantity;
    }

    GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Emerald, FString::FromInt(numberOfQuestItems));
    if (numberOfQuestItems > 0)
    {
        FItemBaseData QuestItem = FItemBaseData(&item);
        QuestItem.quantity = numberOfQuestItems;
        if (!addQuest(QuestItem))
        {
            owner->ItemPickup();
        }
    }

    GEngine->AddOnScreenDebugMessage(1, 10.0f, FColor::Emerald, FString::FromInt(item.quantity - numberOfQuestItems));
    if (item.quantity - numberOfQuestItems > 0)
    {
        FItemBaseData NormalItem = FItemBaseData(&item);
        NormalItem.quantity = item.quantity - numberOfQuestItems;
        return addNormal(NormalItem);

    }
    return false;
}

// Description:
//   Place an item in a specific inventory spot.
// Parameters:
//   item - Item to add to the inventory.
//   index - Index of the inventory spot.
// Return:
//   Return the Item in that spot.
//

FItemBaseData UInventoryComponent::swap(FItemBaseData item, int index)
{
    //if the index is out of bound
    if (index < 0 || index > items.Num())
    {
        //give back the item you try to put in
        return item;
    }
    else
    {
        //it item is the same
        if (FItemBaseData::compare(item, items[index], ECompareField::id) == 0)
        {
            items[index].Stack(item);
            return FItemBaseData();


        }
        else
        {
            //place the item in the spot
            auto temp = items[index];
            items[index] = item;
            //return what was there 
            return temp;
        }
    }
}


// Description:
//   Take an item in a specific inventory spot.
// Parameters:
//   index - Index of the inventory spot.
// Return:
//   Return the Item in that spot.
//

FItemBaseData UInventoryComponent::takeItem(int index)
{
    return swap(FItemBaseData(), index);
}


//
//int Uinventory::compare(FitemInv* i1, FitemInv* i2, sortingMode mode)
//{
//	switch (mode)
//	{
//	case Uinventory::alphabetical:
//		return FitemInv::compare(i1, i2, 1);
//	case Uinventory::price:
//		return FitemInv::compare(i1, i2, 1);
//	case Uinventory::weight:
//		return FitemInv::compare(i1, i2, 1);
//	case Uinventory::totalPrice:
//		if (i1->getTotalValue() > i2->getTotalValue())
//		{
//			return 1;
//		}
//		else if (i1->getTotalValue() < i2->getTotalValue())
//		{
//			return -1;
//		}
//		break;
//	case Uinventory::totalWeight:
//		if (i1->getTotalWeight() > i2->getTotalWeight())
//		{
//			return 1;
//		}
//		else if (i1->getTotalWeight() < i2->getTotalWeight())
//		{
//			return -1;
//		}
//		break;
//	default:
//		break;
//	}
//
//	return 0;
//}

void UInventoryComponent::heapify(int n, int i, ESortingMode mode)
{
    int largest = i; // Initialize largest as root 
    int l = 2 * i + 1; // left = 2*i + 1 
    int r = 2 * i + 2; // right = 2*i + 2 

    // If left child is larger than root 
    //if (l < n && compare(items[i], items[largest], mode)>0)
        //largest = l;

    // If right child is larger than largest so far 
    //if (r < n && compare(items[r], items[largest], mode)>0)
        //largest = r;

    // If largest is not root 
    if (largest != i)
    {
        auto temp = items[largest];
        items[largest] = items[i];
        items[i] = temp;

        // Recursively heapify the affected sub-tree 
        heapify(n, largest, mode);
    }
}







#pragma endregion

// Sets default values for this component's properties
#pragma region ItemBaseData


FItemBaseData FItemBaseData::GetCopy(FItemBaseData original)
{
    return FItemBaseData(original.id, original.displayName, original.weight, original.value, original.quantity, original.icon);
}


int FItemBaseData::compare(FItemBaseData  i1, FItemBaseData  i2, ECompareField type)
{

    int result = 0;
    switch (type)
    {
    case ECompareField::name:
        if (i1.displayName > i2.displayName)
        {
            result = 1;
        }
        else if (i1.displayName < i2.displayName)
        {
            result = -1;
        }
        break;
    case ECompareField::price:
        if (i1.value > i2.value)
        {
            result = 1;
        }
        else if (i1.value < i2.value)
        {
            result = -1;
        }
        break;
    case ECompareField::weight:
        if (i1.weight > i2.weight)
        {
            result = 1;
        }
        else if (i1.weight < i2.weight)
        {
            result = -1;
        }
        break;
    case ECompareField::id:
        if (i1.id > i2.id)
        {
            result = 1;
        }
        else if (i1.id < i2.id)
        {
            result = -1;
        }
        break;
    case ECompareField::quantity:
        if (i1.quantity > i2.quantity)
        {
            result = 1;
        }
        else if (i1.quantity < i2.quantity)
        {
            result = -1;
        }
        break;
    default:
        break;
    }

    return result;
}


int FItemBaseData::getId()
{
    return id;
}

FString FItemBaseData::getDisplayName()
{
    return displayName;
}

float FItemBaseData::getWeight()
{
    return weight;
}

float FItemBaseData::getValue()
{
    return value;
}

int FItemBaseData::getQuantity()
{
    return quantity;
}

float FItemBaseData::getTotalWeight()
{
    return weight * quantity;
}

float FItemBaseData::getTotalValue()
{
    return value * quantity;
}

UTexture2D* FItemBaseData::getIcon()
{
    return icon;
}


bool FItemBaseData::Stack(FItemBaseData other)
{
    if (id == other.id)
    {
        quantity += other.quantity;
        return true;
    }
    else
    {
        return false;
    }
}
#pragma endregion


