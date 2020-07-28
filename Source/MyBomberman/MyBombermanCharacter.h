// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBombermanCharacter.generated.h"

UCLASS(config = Game)
class AMyBombermanCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyBombermanCharacter();

    /** Time to place bombs in seconds. */
    UPROPERTY(EditAnywhere, Category = Bomb)
    float TimeBetweenBoomPlacement = 1.0f;

    /** Bomb Z offset */
    UPROPERTY(EditAnywhere, Category = Bomb)
    float BombZOffset;

    /** Bomb to Spawn */
    UPROPERTY(EditAnywhere, Category = Bomb)
    TSubclassOf<class AMyBomb> BombToSpawn;

protected:
    void MoveForward(float value);
    void MoveRight(float value);
    void PlaceBomb();

    virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

private:
    void Move(float value, EAxis::Type axis);
};

