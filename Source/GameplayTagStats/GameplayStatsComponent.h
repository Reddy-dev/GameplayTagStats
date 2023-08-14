// Copyright Solstice Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagStack.h"
#include "GameplayTagStackInterface.h"
#include "Components/ActorComponent.h"
#include "GameplayStatsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStatsChangedDelegate);

UCLASS(ClassGroup=(Stats), meta=(BlueprintSpawnableComponent))
class GAMEPLAYTAGSTATS_API UGameplayStatsComponent : public UActorComponent, public IGameplayTagStackInterface
{
	GENERATED_BODY()

public:
	UGameplayStatsComponent(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void AddToTagStack_Implementation(FGameplayTag StatTag, int32 Value) override;
	virtual void RemoveFromTagStack_Implementation(FGameplayTag StatTag, int32 Value) override;
	virtual bool HasTagStack_Implementation(FGameplayTag StatTag) const override;
	virtual int32 GetTagStack_Implementation(FGameplayTag StatTag) const override;
	virtual FGameplayTagStackContainer GetTagStackContainer_Implementation() const override;

	UPROPERTY(BlueprintAssignable, Category = "Stats")
	FOnStatsChangedDelegate OnStatChanged;

	UFUNCTION()
	void OnRep_GameplayTagStackContainer();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Stats", ReplicatedUsing=OnRep_GameplayTagStackContainer)
	FGameplayTagStackContainer GameplayTagStackContainer;
};
