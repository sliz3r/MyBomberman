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

public:
    AMyBreakableBrick();

    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

private:
    void SpawnPowerUp();
};
