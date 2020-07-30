// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBreakableBrick.generated.h"

UCLASS()
class MYBOMBERMAN_API AMyBreakableBrick : public AActor
{
    GENERATED_BODY()

    /** Brick Mesh */
    UPROPERTY(EditAnywhere, Category = "Components")
    UStaticMeshComponent* MyBreakableBrickMesh;

    /** Damage Power Up */
    UPROPERTY(EditAnywhere, Category = "Power Up")
    int PercentageOfSpawnPowerUp;

    /** Speed Power Up */
    UPROPERTY(EditAnywhere, Category = "Power Up")
    TSubclassOf<class AMyPowerUpTriggerBox> SpeedPowerUpPrefab;

    /** Damage Power Up */
    UPROPERTY(EditAnywhere, Category = "Power Up")
    TSubclassOf<class AMyPowerUpTriggerBox> DamagePowerUpPrefab;

    /** Sound when breaking */
    UPROPERTY(EditAnywhere, Category = "Power Up")
    USoundWave* BreakingSound;

public:
    AMyBreakableBrick();

    virtual float TakeDamage(float damageAmount, const FDamageEvent& damageEvent, class AController* eventInstigator, class AActor* damageCauser) override;

private:
    void SpawnPowerUp();
};
