// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBreakableBrick.h"
#include "MyPowerUpTriggerBox.h"

AMyBreakableBrick::AMyBreakableBrick()
{
    MyBreakableBrickMesh = CreateDefaultSubobject<UStaticMeshComponent>("BreakableBrickMesh");
    SetRootComponent(MyBreakableBrickMesh);
}

float AMyBreakableBrick::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    if ((FMath::RandRange(1, 100 / PercentageOfSpawnPowerUp) == 1))
    {
        SpawnPowerUp();
    }
    Destroy();
    return DamageAmount;
}

void AMyBreakableBrick::SpawnPowerUp()
{
    UWorld* currentWorld = GetWorld();
    if (currentWorld == nullptr)
    {
        return;
    }

    FTransform locationToSpawn = GetActorTransform();
    FVector location = locationToSpawn.GetLocation();
    locationToSpawn.SetLocation(FVector(location.X, location.Y, location.Z));
    locationToSpawn.SetRotation(FQuat(0, 0, 0, 0));

    FActorSpawnParameters spawnParameters;

    PowerUpType type = (PowerUpType) FMath::RandRange(0, 1);
    switch (type)
    {
        case PowerUpType::SPEED:
        {
            currentWorld->SpawnActor<AMyPowerUpTriggerBox>(SpeedPowerUpPrefab, locationToSpawn, spawnParameters);
        }
        break;

        case PowerUpType::DAMAGE:
        {
            currentWorld->SpawnActor<AMyPowerUpTriggerBox>(DamagePowerUpPrefab, locationToSpawn, spawnParameters);
        }
        break;

        default:
        {
            //Invalid Power Up Type
            check(false);
        }
        break;
    }
}

