// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
		virtual void OnInput(const FString& Input) override;
		void InitGame();
		void ProcessGuess(const FString& Guess);
		void EndGame(const bool Won);
		bool IsIsogram(const FString& Word) const;
		FBullCowCount GetBullCows(const FString& Guess) const;
		TArray<FString> GetValidWords(const TArray<FString>& words) const;

	// Your declarations go below!
	private:
		FString HiddenWord;
		uint32 Lives : 31;
		bool bGameOver : 1;
		TArray<FString> Isograms;

};
