// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPowerUpTriggerBox.h"

#include "DrawDebugHelpers.h"
#include "MyMainCharacter.h"

AMyPowerUpTriggerBox::AMyPowerUpTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &AMyPowerUpTriggerBox::OnOverlapBegin);
}

void AMyPowerUpTriggerBox::BeginPlay()
{
    Super::BeginPlay();
    DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, 999, 0, 5);
}

void AMyPowerUpTriggerBox::OnOverlapBegin(class AActor* overlappedActor, class AActor* otherActor)
{
    if (otherActor && otherActor != this)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Begin"));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapped Actor = %s"), *otherActor->GetName()));

            if (AMyMainCharacter* mainCharacter = Cast<AMyMainCharacter>(otherActor))
            {
                mainCharacter->ApplyPowerUp(PowerUpType);
            }
        }
    }
}