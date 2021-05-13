// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ProceduralTestGameMode.h"
#include "Components/TextRenderComponent.h"
#include "WidgetBlueprint.h"
#include "FuzzySphereActor.generated.h"

UCLASS()
class PROCEDURALTEST_API AFuzzySphereActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuzzySphereActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UStaticMesh* SphereMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UMaterial* SphereMatRed;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UMaterial* SphereMatRedGlow; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UMaterial* SphereMatYellow;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UMaterial* SphereMatYellowGlow; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UMaterial* SphereMatBlue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UMaterial* SphereMatBlueGlow; 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstanceDynamic* SphereMID;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = FuzzySphere)
		UTextRenderComponent* TextComp;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UWidgetBlueprint> HUDWidgetClass;
	UPROPERTY(EditAnywhere)
		class UWidgetBlueprint* HUDWidget;

	UFUNCTION()
		void GrabFuzzy();

private:
	ACharacter* MyChar;
	APlayerController* MyController;
	FRotator* MyTransform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Color of fuzzy - 0=red, 1=blue, 2=yellow
	int FuzzyColor;


};
