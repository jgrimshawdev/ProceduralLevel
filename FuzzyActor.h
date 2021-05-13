// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructibleComponent.h"
#include "DestructibleMesh.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "FuzzyActor.generated.h"

UCLASS()
class PROCEDURALTEST_API AFuzzyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuzzyActor();

	// Destructible mesh that hides Fuzzy
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		UDestructibleComponent* DestructibleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		UStaticMeshComponent* StaticMeshComponent;

	// Root component
	USceneComponent* SceneRoot;

	// Box collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		class UBoxComponent* TriggerComponent;
	// Sphere collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		UDestructibleMesh* DestMesh; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		UStaticMesh* StatMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		UMaterial* FuzzyMat;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzyVariables)
		UParticleSystem* ParticleSys;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FuzzyVariables)
		bool IsDestroyed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FuzzyVariables)
		float MaxHealth;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FuzzyVariables)
		float CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FuzzyVariables)
		float DefaultDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FuzzyVariables)
		float DefaultImpulse;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = FuzzyVariables)
		bool IsTriggerEnabled;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> IndicatorWidgetClass;
	UPROPERTY(EditAnywhere)
		class UUserWidget* IndicatorWidget;

	UFUNCTION()
		void Damage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void DestroyRock(float Damage, FVector HitLocation, FVector ImpulseDirection, float Impulse);
	UFUNCTION()
		void DamageRock();

	// declare overlap begin function
	UFUNCTION()
		void OnSphereOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function
	UFUNCTION()
		void OnSphereOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle DamageTimer;
	FHitResult MyHit;
};
