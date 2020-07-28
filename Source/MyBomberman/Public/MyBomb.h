// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBomb.generated.h"

UCLASS()
class MYBOMBERMAN_API AMyBomb : public AActor
{
    GENERATED_BODY()

    /** Bomb Mesh */
    UPROPERTY(EditAnywhere, Category = "Bomb Configuration")
    UStaticMeshComponent* MyBombMesh;

    /** Time to explode */
    UPROPERTY(EditAnywhere, Category = "Bomb Configuration")
    float ExplosionDelay;

    /** RayCast Distance */
    UPROPERTY(EditAnywhere, Category = "Bomb Configuration")
    float ExplosionDistance = 1000.f;

    /** Bomb Damage */
    UPROPERTY(EditAnywhere, Category = "Bomb Configuration")
    float BombDamage = 1.f;

    /** To track if we are already exploding */
    UPROPERTY(VisibleAnywhere, Category = "Bomb Info")
    bool IsExploding = false;

public:
    AMyBomb();

public:
    void Explode();

protected:
    virtual void BeginPlay() override;
    virtual float TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;
};
