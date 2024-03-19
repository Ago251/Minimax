// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimaxMode.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void AMinimaxMode::BeginPlay()
{
	Super::BeginPlay();
	//Initialization
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABasePlayer::StaticClass(), FoundActors);

	if (sizeof(FoundActors) / sizeof(FoundActors[0]) > 0) {
		ABasePlayer* Pawn = Cast<ABasePlayer>(FoundActors[0]);
		if (Pawn) {
			FString PawnName = Pawn->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Nome del primo giocatore: %s"), *PawnName);
			players[0] = Pawn;
			players[0]->Icon = "O";
		}
	}

	if (sizeof(FoundActors) / sizeof(FoundActors[0]) > 1) {
		ABasePlayer* Pawn = Cast<ABasePlayer>(FoundActors[1]);
		if (Pawn) {
			FString PawnName = Pawn->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Nome del primo giocatore: %s"), *PawnName);
			players[1] = Pawn;
			players[1]->Icon = "X";
		}
	}

	//if (players[currentPlayer] != nullptr) {
	//	players[currentPlayer]->StartTurn();
	//}
}

void AMinimaxMode::StartGame(TArray<UButton*> Grid) {
	CurrentGrid = Grid;
	UE_LOG(LogTemp, Warning, TEXT("StartGame"));
	currentPlayer = 1;
	if (players[currentPlayer] != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Game mode: start turn"));
		players[currentPlayer]->StartTurn(CurrentGrid);
	}
}


void AMinimaxMode::PlayerTurnEnd(int32 index)
{
	//Check end game
	//currentPlayer
	UTextBlock* TextBlock = Cast<UTextBlock>(CurrentGrid[index]->GetChildAt(0));
	TextBlock->SetText(FText::FromString(players[currentPlayer]->Icon));
	currentPlayer++;
	if (currentPlayer >= sizeof(players) / sizeof(players[0]))
		currentPlayer = 0;
	if (players[currentPlayer] != nullptr) {
		players[currentPlayer]->StartTurn(CurrentGrid);
	}
}

ABasePlayer* AMinimaxMode::GetPlayer(int32 index, FString icon) {
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), index);
	if (Pawn) {
		FString PawnName = Pawn->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Nome del primo giocatore: %s"), *PawnName);
		ABasePlayer* PlayerPawn = Cast<ABasePlayer>(Pawn);
		if (PlayerPawn)
		{
			PlayerPawn->Icon = icon;
			return PlayerPawn;

		}
	}

	return nullptr;
}