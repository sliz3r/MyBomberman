// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPowerUpTriggerBox.h"
#include "MyMainCharacter.generated.h"

UCLASS()
class MYBOMBERMAN_API AMyMainCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AMyMainCharacter();

    void ApplyPowerUp(PowerUpType type);

    /** Time to place bombs in seconds. */
    UPROPERTY(EditAnywhere, Category = Bomb)
    float TimeBetweenBoomPlacement = 1.0f;

    /** Bomb Z offset */
    UPROPERTY(EditAnywhere, Category = Bomb)
    float BombZOffset;

    /** Bomb to Spawn */
    UPROPERTY(EditAnywhere, Category = Bomb)
    TSubclassOf<class AMyBomb> BombToSpawn;

    /** Bomb placement cooldown */
    UPROPERTY(VisibleAnywhere, Category = Bomb)
    bool BombPlacementCooldownActive = false;

protected:
    void MoveForward(float value);
    void MoveRight(float value);
    void PlaceBomb();

    virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
    void Move(float value, EAxis::Type axis);
    
    inline void RestoreBombPlacementCooldown() { BombPlacementCooldownActive = false; }

private:
    FTimerHandle BombPlacementCooldownTimer;
};
