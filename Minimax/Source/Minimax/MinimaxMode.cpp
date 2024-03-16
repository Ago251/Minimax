// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimaxMode.h"

void AMinimaxMode::BeginPlay() 
{
	Super::BeginPlay();
	//Initialization
	//players[currentPlayer]->StartTurn();
}

void AMinimaxMode::PlayerTurnEnd() 
{
	//Check end game
	//currentPlayer
	currentPlayer++;
	if (currentPlayer >= sizeof(players) / sizeof(players[0]))
		currentPlayer = 0;
	players[currentPlayer]->StartTurn();
}