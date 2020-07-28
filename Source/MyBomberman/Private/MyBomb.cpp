// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBomb.h"

#include "Components/StaticMeshComponent.h"

#include "Engine.h"

AMyBomb::AMyBomb()
{
    MyBombMesh = CreateDefaultSubobject<UStaticMeshComponent>("BombMesh");
    SetRootComponent(MyBombMesh);
}

void AMyBomb::Explode()
{
    if (UWorld* currentWorld = GetWorld())
    {
        FHitResult* hitResult = new FHitResult();

        FVector startTrace = GetActorLocation();
        TArray<FVector> endTraces;
        endTraces.Add(FVector(GetActorForwardVector() * ExplosionDistance) + startTrace);
        endTraces.Add(FVector(GetActorForwardVector() * -ExplosionDistance) + startTrace);
        endTraces.Add(FVector(GetActorRightVector() * -ExplosionDistance) + startTrace);
        endTraces.Add(FVector(GetActorRightVector() * ExplosionDistance) + startTrace);

        FCollisionQueryParams* collisionParameters = new FCollisionQueryParams();
        collisionParameters->AddIgnoredActor(this);

        for (const FVector& endTrace : endTraces)
        {
            if (currentWorld->LineTraceSingleByChannel(*hitResult, startTrace, endTrace, ECC_Pawn, *collisionParameters))
            {
                DrawDebugLine(currentWorld, startTrace, endTrace, FColor::Red, false, 1.0f);
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString::Printf(TEXT("Hit Detected: %s"), *hitResult->Actor->GetName()));
            }
        }
    }

    Destroy();
}

void AMyBomb::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle ExplodeTimer;
    GetWorldTimerManager().SetTimer(ExplodeTimer, this, &AMyBomb::Explode, ExplosionDelay);
}
