// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBombermanGameMode.h"
#include "UObject/ConstructorHelpers.h"

AMyBombermanGameMode::AMyBombermanGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/MyBomberman/Blueprints/BombermanCharacter"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}
