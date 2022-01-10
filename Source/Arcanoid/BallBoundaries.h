// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallBoundaries.generated.h"

class APaddle_PlayerController;
class UBoxComponent;

UCLASS()
class ARCANOID_API ABallBoundaries : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABallBoundaries();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		UBoxComponent* Box_Collision;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);

	APaddle_PlayerController* ControllerRef;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
