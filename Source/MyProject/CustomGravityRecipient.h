// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomGravityRecipient.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UCustomGravityRecipient : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCustomGravityRecipient();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="Gravity")
	void HandleGravityFlipped(bool isUpsideDown);

protected:
	virtual void BeginPlay() override;
	void FindRelevantComponents();

public:
	UPROPERTY(EditAnywhere, Category = "Gravity")
	float MockGravity = 1000.f;

private:
	class UStaticMeshComponent* _staticMeshComponent = nullptr;
	bool _isGravityFlipped;
	float _mass;
};
