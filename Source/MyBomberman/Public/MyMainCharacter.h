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
    bool IsPowerActive(PowerUpType type);

    /** Time to place bombs in seconds. */
    UPROPERTY(EditAnywhere, Category = "Bomb")
    float TimeBetweenBoomPlacement = 1.f;

    /** Bomb Z offset */
    UPROPERTY(EditAnywhere, Category = "Bomb")
    float BombZOffset;

    /** Bomb to Spawn */
    UPROPERTY(EditAnywhere, Category = "Bomb")
    TSubclassOf<class AMyBomb> BombToSpawn;

    /** Boosted Bomb to Spawn */
    UPROPERTY(EditAnywhere, Category = "Bomb")
    TSubclassOf<class AMyBomb> BoostedBombToSpawn;

    /** Bomb placement cooldown */
    UPROPERTY(VisibleAnywhere, Category = "Bomb")
    bool BombPlacementCooldownActive = false;

    /** Time to place bombs in seconds. */
    UPROPERTY(EditAnywhere, Category = "Health")
    float PlayerHealth = 3.f;

    /** Damage Received Sound */
    UPROPERTY(EditAnywhere, Category = "Health")
    USoundWave* DamageSound;

    /** Time Power Ups can be used. */
    UPROPERTY(EditAnywhere, Category = "Power Up")
    float PowerUpTime = 5.f;

    /** Extra Speed Applied when picking up the Power Up. */
    UPROPERTY(EditAnywhere, Category = "Power Up")
    float SpeedExtraBoost = 1000.f;

protected:
    void MoveForward(float value);
    void MoveRight(float value);
    void PlaceBomb();

    virtual void SetupPlayerInputComponent(class UInputComponent* playerInputComponent) override;
    virtual float TakeDamage(float damageAmount, const FDamageEvent& damageEvent, class AController* eventInstigator, class AActor* damageCauser) override;

private:
    void Move(float value, EAxis::Type axis);
    void RevertSpeedPowerUp();
    void RevertDamagePowerUp();
    void RestoreBombPlacementCooldown();

private:
    FTimerHandle BombPlacementCooldownTimer;
    FTimerHandle SpeedPowerUpCooldownTimer;
    FTimerHandle DamagePowerUpCooldownTimer;

private:
    bool CanSpawnBigBomb = false;
};
