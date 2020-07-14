// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "QuestActor.h"
#include "NPC.h"
#include "NPCQuestWidget.h"
#include "AttributesComponent.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "ClassComponent.h"
#include "BaseCharacter.h"
#include "QuestBoardWidget.h"
#include "GameFramework/Character.h"
#include "PlanetSixCharacter.generated.h"

class UNPCQuestWidget;
class UNPCDialogueWidget;
class UQuestWidget;
class AQuestActor;
class APlayerController;
class ASkill;
struct FSkillData;
class AMapTravel;
class UinventoryWidget;

UCLASS(config = Game)
class APlanetSixCharacter : public ABaseCharacter
{
	GENERATED_BODY()

		virtual void BeginPlay() override;
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	float BaseTurnRate;
	float BaseLookUpRate;
public:
	APlanetSixCharacter();

	/*Incrementor For the Quest Widget Log*/
	int Incrementor = 0;

	//Specified Portal
	AMapTravel* Portal;

	//this is to create the widget of the Dialogue  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue UI")
		TSubclassOf<UUserWidget> NPCDialogueWidgetClass;

	UPROPERTY(BlueprintReadWrite)
		UNPCDialogueWidget* WidgetDialogueNPC;

#pragma region(Quests Logic)
	//this is to create the widget of the NPCQuest  
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest UI")
		TSubclassOf<UUserWidget> NPCQuestWidgetClass;

	UPROPERTY(BlueprintReadWrite)
		UNPCQuestWidget* WidgetQuestNPC;

	/*Quest Widget UI*/
	//this is to create the quest LOG 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest UI")
		TSubclassOf<UUserWidget> QuestWidgetLog;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest UI")
		TSubclassOf<UUserWidget> CurrentQuestWidget;

	UPROPERTY(BlueprintReadWrite, Category = "Quest UI")
		UUserWidget* CurrentQuest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest UI")
		TSubclassOf<UUserWidget> QuestCompletedClass;

	UPROPERTY(BlueprintReadWrite)
		UUserWidget* QuestCompletedWidget;

	//this is for the WidgetQuestLog
	UPROPERTY(BlueprintReadWrite, Category = "Quest UI")
		UUserWidget* WidgetQuestLog;

	//QuestInfos for player 
	//TArray<FQuestData> QuestInfos;

   //Quest Accepted By Player
	FQuestData QuestAccepted;


	//Reference to NPC Actor
	UPROPERTY(BlueprintReadWrite)
	ANPC* NPCReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest UI")
		TSubclassOf<UUserWidget> QuestBoardWidgetRef;

	//Reference to QuestBoardWidget
	UPROPERTY(BlueprintReadWrite, Category = "Quest UI")
		UQuestBoardWidget* QuestBoardWidget;

#pragma endregion

	/** Player's inventory. */
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		UInventoryComponent* InventoryComponent;

	/** inventory widget */
	UPROPERTY(BlueprintReadWrite, Category = "Inventory")
		UinventoryWidget* InventoryWidget;

	/** Player's weapons. */
	UPROPERTY(BlueprintReadWrite, Category = "Weapons")
		UWeaponComponent* WeaponComponent;

	/** Vector to shoot towards */
	UPROPERTY(BlueprintReadWrite, Category = "Weapons")
		FVector CameraCrosshair;

	/** Player's HUD. */
	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> MainHUD;

	//Skill Data for the player
	FSkillData* SkillData;

	UPROPERTY(EditDefaultsOnly, Category = "IGMenu")
		TSubclassOf<UUserWidget> InGameMenu;

protected:
#pragma region(Character Move & Input Actions)
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Reload the player's weapon */
	void Reload();

	/** Crouch  */

	/** Interact with object or player */
	void Interact();

	/** Melee Attack with any weapon */
	void MeleeAttack();

	/** Send a Skill */
	UFUNCTION(BlueprintCallable)
		void Skill(int32 SkillNumber);

	/** skill 1 */
	void Skill1();

	/** skill 2 */
	void Skill2();

	/** skill 3 */
	void Skill3();

	/** Open the inventory */
	void Inventory();

	/** Open the quest log */
	void QuestLog();

	/** Open the skills menu */
	void SkillsMenu();

	/** Sprint */
	void Sprint();

	/** Zoom with a distance weapon */
	void Zoom();

	/** Shoot */
	void Shoot();

	/** Change Weapon depending on 1, 2, 3 or scrollwheel */
	void ChangeWeaponScroll(float WeaponNumber);

	/** Change Weapon depending on 1, 2, 3 or scrollwheel */
	void ChangeWeapon(int32 WeaponNumber);

	/** Change Weapon depending on 1, 2, 3 or scrollwheel */
	void ChangeWeapon1();

	/** Change Weapon depending on 1, 2, 3 or scrollwheel */
	void ChangeWeapon2();

	/** Change Weapon depending on 1, 2, 3 or scrollwheel */
	void ChangeWeapon3();

	/** Open Ingame Menu*/
	void OpenIngameMenu();

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
#pragma endregion

	/** Drop item on the ground*/
	UFUNCTION(BlueprintCallable)
		bool DropItem(FItemBaseData item);

	//the distance an item is drop from the player;
	float DropDistance = 200;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void Tick(float DeltaSeconds) override;

	/** Property replication */
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	int GetNumberNeededForQuest(int itemId, int quantity);

	void ItemPickup();
	virtual void Death() override;
};
