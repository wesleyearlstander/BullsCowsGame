// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    Isograms = GetValidWords(HiddenWords);
    InitGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (!bGameOver) {
        ProcessGuess(Input);
    }
    else {
        ClearScreen();
        InitGame();
    }
}

void UBullCowCartridge::InitGame()
{
    HiddenWord = Isograms[FMath::RandRange(0, Isograms.Num()-1)];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Hi welcome to Bull Cows Game!"));
    PrintLine(TEXT("Guess the %i letter word, you have %i lives"), HiddenWord.Len(), Lives);
    PrintLine(TEXT("Type in your guess.\nPress enter to continue..."));
    PrintLine(TEXT("The hidden word is %s"), *HiddenWord); //debug
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (HiddenWord == Guess) {
        EndGame(true);
    }
    else {
        if (HiddenWord.Len() != Guess.Len()) {
            PrintLine(TEXT("The hidden word is %i characters long"), HiddenWord.Len());
            return;
        }
        if (!IsIsogram(Guess)) {
            PrintLine(TEXT("The guessed word is not an Isogram"));
            return;
        }
        --Lives;
        if (Lives == 0) {
            EndGame(false);
            return;
        }
        else {
            FBullCowCount Score = GetBullCows(Guess);
            PrintLine(TEXT("You have %i bulls and You have %i cows"), Score.Bulls, Score.Cows);
            PrintLine(TEXT("Wrong answer, Lives: %i"), Lives);
        }
    }
}

bool UBullCowCartridge::IsIsogram(const FString& word) const
{
    size_t length = word.Len();
    for (size_t Index = 0; Index < length; ++Index)
    {
        for (size_t i = Index + 1; i < length; i++)
        {
            if (word[Index] == word[i])
                return false;
        }
    }
    return true;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    FBullCowCount Count;

    for (size_t i = 0; i < HiddenWord.Len(); i++)
    {
        if (Guess[i] == HiddenWord[i]) {
            Count.Bulls++;
            continue;
        }
        for (size_t j = 0; j < HiddenWord.Len(); j++)
        {
            if (Guess[i] == HiddenWord[j]) {
                Count.Cows++;
                break;
            }
        }
    }

    return Count;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& words) const
{
    TArray<FString> ValidWords;

    for (FString word : words) {
        if (IsIsogram(word) &&
            word.Len() <= 8 &&
            word.Len() >= 4) {
            ValidWords.Add(word);
        }
    }

    return ValidWords;
}

void UBullCowCartridge::EndGame(bool Won)
{
    bGameOver = true;
    if (Won) {
        PrintLine(TEXT("You Win"));
    }
    else {
        PrintLine(TEXT("You have run out of lives"));
        PrintLine(TEXT("You lose, the hidden word is: "), *HiddenWord);
    }
    PrintLine(TEXT("Press enter to play again."));
}

