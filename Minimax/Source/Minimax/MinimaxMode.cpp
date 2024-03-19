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
	if (!IsWinner(players[currentPlayer]->Icon)) {
		currentPlayer++;
		if (currentPlayer >= sizeof(players) / sizeof(players[0]))
			currentPlayer = 0;
		if (players[currentPlayer] != nullptr) {
			players[currentPlayer]->StartTurn(CurrentGrid);
		}
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


bool AMinimaxMode::IsWinner(FString player) {
	FLinearColor RedColor = FLinearColor(1.0f, 0.0f, 0.0f);

	//Horizontal
	for (int i = 0; i < 7; i += 3)
	{
		if (GetStringText(CurrentGrid[i]) == player && GetStringText(CurrentGrid[i + 1]) == player && GetStringText(CurrentGrid[i + 2]) == player) {
				GetText(CurrentGrid[i])->SetColorAndOpacity(RedColor);
				GetText(CurrentGrid[i + 1])->SetColorAndOpacity(RedColor);
				GetText(CurrentGrid[i + 2])->SetColorAndOpacity(RedColor);
				return true;
		}
	}


	//Vertical
	for (int i = 0; i < 3; ++i)
	{
		if (GetStringText(CurrentGrid[i]) == player && GetStringText(CurrentGrid[i + 3]) == player && GetStringText(CurrentGrid[i + 6]) == player) {
			GetText(CurrentGrid[i])->SetColorAndOpacity(RedColor);
			GetText(CurrentGrid[i + 3])->SetColorAndOpacity(RedColor);
			GetText(CurrentGrid[i + 6])->SetColorAndOpacity(RedColor);
			return true;
		}
	}

	//Diagnonals
	if (GetStringText(CurrentGrid[0]) == player && GetStringText(CurrentGrid[4]) == player && GetStringText(CurrentGrid[8]) == player) {
			GetText(CurrentGrid[0])->SetColorAndOpacity(RedColor);
			GetText(CurrentGrid[4])->SetColorAndOpacity(RedColor);
			GetText(CurrentGrid[8])->SetColorAndOpacity(RedColor);
			return true;
	}

	if (GetStringText(CurrentGrid[2]) == player && GetStringText(CurrentGrid[4]) == player && GetStringText(CurrentGrid[6]) == player) {
			GetText(CurrentGrid[2])->SetColorAndOpacity(RedColor);
			GetText(CurrentGrid[4])->SetColorAndOpacity(RedColor);
			GetText(CurrentGrid[6])->SetColorAndOpacity(RedColor);
			return true;
	}

	return false;
}

UTextBlock* AMinimaxMode::GetText(UButton* Button)
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

FString AMinimaxMode::GetStringText(UButton* Button)
{
	if (Button)
	{
		// Ottieni il componente figlio TextBlock direttamente
		UTextBlock* TextBlock = Cast<UTextBlock>(Button->GetChildAt(0));
		return TextBlock->GetText().ToString();
	}

	// Se il Button ? nullo o non ha un TextBlock come figlio, restituisci nullptr
	return "";
}