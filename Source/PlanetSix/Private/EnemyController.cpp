// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyController.h"
#include "PlanetSixEnemy.h"
#include "EnemyAnimInstance.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

AEnemyController::AEnemyController()
{


	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception"));
	PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AEnemyController::SenseStuff);
	SetPerceptionComponent(*PerceptionComp);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight"));
	SightConfig->PeripheralVisionAngleDegrees = 20;
	SightConfig->SightRadius = 1500;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 20.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComp->ConfigureSense(*SightConfig);

}



void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AnimInstance = Cast<UEnemyAnimInstance>(Cast<APlanetSixEnemy>(InPawn)->GetMesh()->GetAnimInstance());
	PawnMesh = Cast<APlanetSixEnemy>(InPawn)->GetMesh();

}


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<APlanetSixCharacter> playerRef = APlanetSixCharacter::StaticClass();
	TArray<AActor*> result;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), playerRef, result);
	for (AActor* a : result) {
		Players.Add(Cast<APlanetSixCharacter>(a));
	}
	if (Players.Num() < 0) {
		print("Caught " + FString::FromInt(Players.Num()) + " players in scene", -1);
	}
}

float CountdownToShoot = 0;

void AEnemyController::Tick(float DeltaTime)
{

	if (PlayerInSight) {
		float distance = FVector::Distance(PlayerInSight->GetActorLocation(), GetPawn()->GetActorLocation());
		if (distance > 1500) {
			PlayerInSight = nullptr;
			return;
		}
		//print("Distance " + FString::SanitizeFloat(distance), 3);

		FRotator RotationHip = PawnMesh->GetSocketRotation("spine_02");

		if (!IsFollowingAPath()) {
			AnimInstance->bIsShooting = true;

			//Turning Enemy at player
			FVector Begin = GetPawn()->GetActorLocation();
			FVector End = PlayerInSight->GetActorLocation();

			FRotator EnemyRotation = GetPawn()->GetActorRotation();
			FRotator RotationToLook = UKismetMathLibrary::FindLookAtRotation(Begin, End);
			
				RotationToLook.Pitch = 0;
				RotationToLook.Roll = 0;
			if (FMath::Abs(RotationHip.Yaw - EnemyRotation.Yaw) > 90) {
				
				FRotator LerpedRotation = FMath::Lerp(EnemyRotation,RotationToLook,0.1);
				GetPawn()->SetActorRotation(LerpedRotation);
				RotationToLook.Yaw -= GetPawn()->GetActorRotation().Yaw;
				//RotationToLook.Yaw = -RotationToLook.Yaw;
				AnimInstance->RotationToAim = RotationToLook;
			}
			if (FMath::Abs(RotationHip.Yaw - EnemyRotation.Yaw) <= 90) {

				//FRotator BoneRotation = PawnMesh->GetSocketRotation("spine_02");
				
				RotationToLook.Yaw -= GetPawn()->GetActorRotation().Yaw;
				AnimInstance->RotationToAim = RotationToLook;
			}
			//print("HipRotation " + RotationHip.ToString(), -1);
		/*if (RotationToLook.Yaw < 40 || RotationToLook.Yaw >  40) {


		}*/


		//Finish turning 


		//print("Is gonna shoot", -1);

			if (CountdownToShoot < 3) {
				CountdownToShoot += DeltaTime;

			}
			else {
				CountdownToShoot = 0;
				Shoot();
				print("Shoot", -1);
			}
		}




	}
	Super::Tick(DeltaTime);
}

void AEnemyController::SenseStuff(const TArray<AActor*>& actors)
{
	if (!PlayerInSight) {
		if (Players.Num() < 0) {
			return;
		}
		for (AActor* actor : actors) {
			if (Players.Contains(actor)) {
				MoveToActor(actor, 500);
				AnimInstance->bIsShooting = false;
				PlayerInSight = Cast<APlanetSixCharacter>(actor);
				print("Moving to " + PlayerInSight->GetFName().ToString(), -1);

			}

		}
	}
	else {

		/*	if (AnimInstance->bIsShooting) {

				FVector Begin = GetPawn()->GetActorLocation();
				FVector End = PlayerInSight->GetActorLocation();

				FRotator RotationToLook = UKismetMathLibrary::FindLookAtRotation(Begin, End);
				FRotator LerpedRotation = FMath::Lerp(GetPawn()->GetActorRotation(), RotationToLook, 0.2);
				GetPawn()->SetActorRotation(LerpedRotation);


			}*/

	}

}

void AEnemyController::Shoot()
{

	if (PlayerInSight) {
		auto EnemyBase = Cast<APlanetSixEnemy>(GetPawn());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EnemyBase->ShootingSound, EnemyBase->GetActorLocation());
		AnimInstance->Montage_Play(EnemyBase->ShootAnimation);
		FVector Begin = EnemyBase->ShootingBegin;
		FVector End = EnemyBase->ShootingEnd - Begin;
		End *= 100;
		print("Shoot from " + Begin.ToString(), 4);
		print("Shoot To " + End.ToString(), 5);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(GetPawn());
		QueryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, Begin, End, ECC_Pawn, QueryParams))
		{
			auto ActorHit = Cast<APlanetSixCharacter>(Hit.GetActor());
			if (ActorHit)
			{
				print("Hit Player", -1);
				ActorHit->ReceiveDamage(EnemyBase->WeaponDamage());
			}
		}
		DrawDebugLine(GetWorld(), Begin, End, FColor::Blue, false, 1.0f, 0, 1.0f);

	}
}
