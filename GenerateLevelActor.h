// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralTestCharacter.h"
#include "GenerateLevelActor.generated.h"

UCLASS()
class PROCEDURALTEST_API AGenerateLevelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenerateLevelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	//UStaticMeshComponent RoomMeshArray[10];
	TArray<UStaticMeshComponent*> RoomMeshArray;
	
	// Create room grid
	void CreateGrid();
	// Marks created rooms on grid
	void MarkGrid(int x, int y);
	// Struct to hold xy grid coordinates
	struct XY
	{
		int x;
		int y;
	};
	XY StartLocation;

	void AddMeshes();
	void AddFuzzies();
	void AddBlocks();
	void AddDecoration();

	AProceduralTestCharacter* MyChar;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Number of rooms to generate
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int NumRooms;

	// Room building block meshes
	UStaticMesh* XBlockMesh;
	UStaticMesh* TBlockMesh;
	UStaticMesh* LBlockMesh;
	UStaticMesh* IBlockMesh;
	UStaticMesh* RBlockMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> BlockBP_X;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> BlockBP_T;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> BlockBP_L;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> BlockBP_I;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> BlockBP_R;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> BlockBP_Entrance;

	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Floor1;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Floor2;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Column1;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Column2;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Mite1;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Mite2;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Arch;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_RockPile;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Rock1;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Rock2;
	UPROPERTY(EditDefaultsOnly, Category = "Parameters")
		TSubclassOf<AActor> CaveBP_Rock3;

	// Root component
	USceneComponent* SceneRoot;

	// Room mesh components
	UStaticMeshComponent* RoomMesh1;
	UStaticMeshComponent* RoomMesh2;
	UStaticMeshComponent* RoomMesh3;
	UStaticMeshComponent* RoomMesh4;
	UStaticMeshComponent* RoomMesh5;
	UStaticMeshComponent* RoomMesh6;
	UStaticMeshComponent* RoomMesh7;
	UStaticMeshComponent* RoomMesh8;
	UStaticMeshComponent* RoomMesh9;
	UStaticMeshComponent* RoomMesh10;
	UStaticMeshComponent* RoomMesh11;
	UStaticMeshComponent* RoomMesh12;
	UStaticMeshComponent* RoomMesh13;
	UStaticMeshComponent* RoomMesh14;
	UStaticMeshComponent* RoomMesh15;

	UFUNCTION(BlueprintCallable)
		void GenerateLevel();

	// RoomGrid - 0=no room, 1=room, 2=needs room
	int RoomGrid[8][8];
	// BlockTypeGrid - I, L, R, X, or T
	char BlockTypeGrid[8][8];

	// Number of fuzzies variables
	UPROPERTY(BlueprintReadWrite)
		int NumTargetRed;
	UPROPERTY(BlueprintReadWrite)
		int NumCurrentRed;
	UPROPERTY(BlueprintReadWrite)
		int NumTargetBlue;
	UPROPERTY(BlueprintReadWrite)
		int NumCurrentBlue;
	UPROPERTY(BlueprintReadWrite)
		int NumTargetYellow;
	UPROPERTY(BlueprintReadWrite)
		int NumCurrentYellow;

};
