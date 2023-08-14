// Copyright Solstice Games

#include "GameplayStatsComponent.h"
#include "Net/UnrealNetwork.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GameplayStatsComponent)

UGameplayStatsComponent::UGameplayStatsComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetIsReplicatedByDefault(true);

	PrimaryComponentTick.bCanEverTick = false;
}

void UGameplayStatsComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams SharedParams;
	SharedParams.bIsPushBased = true;

	DOREPLIFETIME_WITH_PARAMS_FAST(UGameplayStatsComponent, GameplayTagStackContainer, SharedParams);
}

void UGameplayStatsComponent::AddToTagStack_Implementation(FGameplayTag StatTag, int32 Value)
{
	GameplayTagStackContainer.AddStack(StatTag, Value);
	MARK_PROPERTY_DIRTY_FROM_NAME(UGameplayStatsComponent, GameplayTagStackContainer, this);
	if (OnStatChanged.IsBound())
	{
		OnStatChanged.Broadcast();
	}
}

void UGameplayStatsComponent::RemoveFromTagStack_Implementation(FGameplayTag StatTag, int32 Value)
{
	GameplayTagStackContainer.RemoveStack(StatTag, Value);
	MARK_PROPERTY_DIRTY_FROM_NAME(UGameplayStatsComponent, GameplayTagStackContainer, this);
	if (OnStatChanged.IsBound())
	{
		OnStatChanged.Broadcast();
	}
}

bool UGameplayStatsComponent::HasTagStack_Implementation(FGameplayTag StatTag) const
{
	return GameplayTagStackContainer.ContainsTag(StatTag);
}

int32 UGameplayStatsComponent::GetTagStack_Implementation(FGameplayTag StatTag) const
{
	return GameplayTagStackContainer.GetStackCount(StatTag);
}

FGameplayTagStackContainer UGameplayStatsComponent::GetTagStackContainer_Implementation() const
{
	return GameplayTagStackContainer;
}

void UGameplayStatsComponent::OnRep_GameplayTagStackContainer()
{
	if (OnStatChanged.IsBound())
	{
		OnStatChanged.Broadcast();
	}
}
