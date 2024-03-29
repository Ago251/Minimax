// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePlayer.generated.h"

class AMinimaxMode;
class UTextBlock;
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStartTurnEvent, TArray<UButton*>, Grid);

UCLASS()
class MINIMAX_API ABasePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePlayer();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	bool isYourTurn;
	AMinimaxMode* MinimaxMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
	FString Icon;


	TArray<FString> CurrentGrid;
	/*UPROPERTY(BlueprintAssignable, Category = "My Events")
	FStartTurnEvent OnStartTurn;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	virtual void StartTurn(TArray<UButton*> Grid);

	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	virtual void EndTurn(int32 index);

	TArray<FString> CreateStringArray(TArray<UButton*>& Grid);

    UTextBlock* GetText(UButton* Button);
};
