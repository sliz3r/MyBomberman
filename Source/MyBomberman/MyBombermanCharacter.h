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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
        float TimeBetweenBoomPlacement = 1.0f;;

protected:
    void MoveForward(float value);
    void MoveRight(float value);
    void PlaceBomb();
    virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;

private:
    void Move(float value, EAxis::Type axis);
};

