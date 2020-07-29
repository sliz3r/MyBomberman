// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPowerUpTriggerBox.h"

#include "DrawDebugHelpers.h"
#include "MyMainCharacter.h"

AMyPowerUpTriggerBox::AMyPowerUpTriggerBox()
{
    OnActorBeginOverlap.AddDynamic(this, &AMyPowerUpTriggerBox::OnOverlapBegin);
}

void AMyPowerUpTriggerBox::OnOverlapBegin(class AActor* overlappedActor, class AActor* otherActor)
{
    if (otherActor && otherActor != this)
    {
#ifdef UE_BUILD_DEBUG
        if (GEngine != nullptr)
        {
            GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, TEXT("Overlap Begin"));
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Overlapped Actor = %s"), *otherActor->GetName()));
            
            if (PowerUpType == PowerUpType::SPEED)
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Applied PowerUp = %s"), TEXT("Speed Boost")));
            }
            else
            {
                GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta, FString::Printf(TEXT("Applied PowerUp = %s"), TEXT("Damage Boost")));
            }
        }
#endif

        if (AMyMainCharacter* mainCharacter = Cast<AMyMainCharacter>(otherActor))
        {
            mainCharacter->ApplyPowerUp(PowerUpType);
            Destroy();
        }
    }
}