// Fill out your copyright notice in the Description page of Project Settings.

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
    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
    void Move(float value, EAxis::Type axis);
};

