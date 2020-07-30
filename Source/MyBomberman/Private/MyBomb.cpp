// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBomb.h"

#include "Components/StaticMeshComponent.h"

#include "Engine.h"

AMyBomb::AMyBomb()
{
    MyBombMesh = CreateDefaultSubobject<UStaticMeshComponent>("BombMesh");
    SetRootComponent(MyBombMesh);
}

void AMyBomb::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle ExplodeTimer;
    GetWorldTimerManager().SetTimer(ExplodeTimer, this, &AMyBomb::Explode, ExplosionDelay);
}

float AMyBomb::TakeDamage(float DamageAmount, const FDamageEvent& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    Explode();
    return DamageAmount;
}

void AMyBomb::Explode()
{
    if (IsExploding == false)
    {
        IsExploding = true;
        PerformRayCasts();
        SpawnEffect();
        PlaySound();
        Destroy();
    }
}

void AMyBomb::PerformRayCasts()
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
            if (currentWorld->LineTraceSingleByChannel(*hitResult, startTrace, endTrace, ECC_WorldStatic, *collisionParameters))
            {
#ifdef UE_BUILD_DEBUG
                if (GEngine != nullptr)
                {
                    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Turquoise, FString::Printf(TEXT("Hit Detected: %s"), *hitResult->Actor->GetName()));
                }
#endif
                FDamageEvent dummyDamageEvent;
                hitResult->Actor->TakeDamage(BombDamage, dummyDamageEvent, GetInstigatorController(), this);
                collisionParameters->AddIgnoredActor(hitResult->Actor.Get());

#ifdef UE_BUILD_DEBUG
                DrawDebugLine(currentWorld, startTrace, hitResult->Location, FColor::Red, false, 1.0f);
#endif
            }
#ifdef UE_BUILD_DEBUG
            else
            {
                DrawDebugLine(currentWorld, startTrace, endTrace, FColor::Red, false, 1.0f);
            }
#endif
        }
    }
}

void AMyBomb::SpawnEffect()
{
    if (UWorld* currentWorld = GetWorld())
    {
        UGameplayStatics::SpawnEmitterAtLocation(currentWorld, ExplosionFX, GetActorLocation());
    }
}

void AMyBomb::PlaySound()
{
    UGameplayStatics::PlaySound2D(this, ExplosionSound);
}
