// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimaxMode.h"
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
			players[0]->Icon = "X";
		}
	}

	if (sizeof(FoundActors) / sizeof(FoundActors[0]) > 1) {
		ABasePlayer* Pawn = Cast<ABasePlayer>(FoundActors[1]);
		if (Pawn) {
			FString PawnName = Pawn->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Nome del primo giocatore: %s"), *PawnName);
			players[1] = Pawn;
			players[1]->Icon = "O";
		}
	}

	//if (players[currentPlayer] != nullptr) {
	//	players[currentPlayer]->StartTurn();
	//}
}

void AMinimaxMode::StartGame(TArray<UButton*> Grid) {
	if (players[currentPlayer] != nullptr) {
		players[currentPlayer]->StartTurn(Grid);
	}
}


void AMinimaxMode::PlayerTurnEnd(TArray<UButton*> Grid)
{
	//Check end game
	//currentPlayer
	currentPlayer++;
	if (currentPlayer >= sizeof(players) / sizeof(players[0]))
		currentPlayer = 0;
	if (players[currentPlayer] != nullptr) {
		players[currentPlayer]->StartTurn(Grid);
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