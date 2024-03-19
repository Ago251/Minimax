// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePlayer.h"
#include "MinimaxMode.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePlayer::ABasePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	MinimaxMode = Cast<AMinimaxMode>(UGameplayStatics::GetGameMode(this));
}

// Called every frame
void ABasePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasePlayer::StartTurn(TArray<UButton*> Grid) {
	UE_LOG(LogTemp, Warning, TEXT("Start turn"));
	CurrentGrid = CreateStringArray(Grid);
	isYourTurn = true;
	//OnStartTurn.Broadcast(Grid);
}

void ABasePlayer::EndTurn(int32 index) {
	isYourTurn = false;
	MinimaxMode->PlayerTurnEnd(index);
}

TArray<FString> ABasePlayer::CreateStringArray(TArray<UButton*>& Grid) {
	TArray<FString> stringGrid;
	stringGrid.SetNum(9);

	for (int i = 0; i < 9; ++i) {
		stringGrid[i] = GetText(Grid[i])->GetText().ToString();
	}

	return stringGrid;
}


UTextBlock* ABasePlayer::GetText(UButton* Button)
{
	if (Button)
	{
		// Ottieni il componente figlio TextBlock direttamente
		UTextBlock* TextBlock = Cast<UTextBlock>(Button->GetChildAt(0));
		return TextBlock;
	}

	// Se il Button ? nullo o non ha un TextBlock come figlio, restituisci nullptr
	return nullptr;
}

