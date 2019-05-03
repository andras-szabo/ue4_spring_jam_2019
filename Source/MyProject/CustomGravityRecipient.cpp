// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomGravityRecipient.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"

UCustomGravityRecipient::UCustomGravityRecipient()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCustomGravityRecipient::HandleGravityFlipped(bool isUpsideDown)
{
	_isGravityFlipped = isUpsideDown;

	if (_staticMeshComponent == nullptr)
	{
		FindRelevantComponents();

		if (_staticMeshComponent == nullptr)
		{
			return;
		}
	}

	auto gravityEnabled = _staticMeshComponent->IsGravityEnabled();

	if (_isGravityFlipped && gravityEnabled)
	{
		_staticMeshComponent->SetEnableGravity(false);
	}

	if (!_isGravityFlipped && !gravityEnabled)
	{
		_staticMeshComponent->SetEnableGravity(true);
	}
}

void UCustomGravityRecipient::BeginPlay()
{
	Super::BeginPlay();
}

void UCustomGravityRecipient::FindRelevantComponents()
{
	auto owner = GetOwner();

	if (owner != nullptr)
	{
		_staticMeshComponent = owner->FindComponentByClass<UStaticMeshComponent>();
		if (_staticMeshComponent != nullptr)
		{
			_mass = _staticMeshComponent->GetMass();
		}
	}
}


void UCustomGravityRecipient::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_isGravityFlipped && _staticMeshComponent != nullptr)
	{
		_staticMeshComponent->AddForce(FVector(0.0f, 0.0f, 9.81f * _mass * MockGravity));
	}
}

