// Fill out your copyright notice in the Description page of Project Settings.


#include "GenerateLevelActor.h"
#include "FuzzyActor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

// Sets default values
AGenerateLevelActor::AGenerateLevelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up root component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	// Get building block static meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Xasset(TEXT("StaticMesh'/Game/Meshes/block_X2.block_X2'"));
	XBlockMesh = Xasset.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Tasset(TEXT("StaticMesh'/Game/Meshes/block_T2.block_T2'"));
	TBlockMesh = Tasset.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Lasset(TEXT("StaticMesh'/Game/Meshes/block_L2.block_L2'"));
	LBlockMesh = Lasset.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Iasset(TEXT("StaticMesh'/Game/Meshes/block_I2_Cube.block_I2_Cube'"));
	IBlockMesh = Iasset.Object;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Rasset(TEXT("StaticMesh'/Game/Meshes/block_R2.block_R2'"));
	RBlockMesh = Rasset.Object;

	/*
	static ConstructorHelpers::FClassFinder<AActor> XBlockFinder(TEXT("Blueprint'/Game/Meshes/CaveBlocks/BlockBlueprints/BP_BlockX.BP_BlockX'"));
	BlockBP_X = XBlockFinder.Class;
	static ConstructorHelpers::FClassFinder<AActor> TBlockFinder(TEXT("Blueprint'/Game/Meshes/CaveBlocks/BlockBlueprints/BP_BlockT.BP_BlockT'"));
	BlockBP_T = TBlockFinder.Class;
	static ConstructorHelpers::FClassFinder<AActor> LBlockFinder(TEXT("Blueprint'/Game/Meshes/CaveBlocks/BlockBlueprints/BP_BlockL.BP_BlockL'"));
	BlockBP_L = LBlockFinder.Class;
	static ConstructorHelpers::FClassFinder<AActor> IBlockFinder(TEXT("Blueprint'/Game/Meshes/CaveBlocks/BlockBlueprints/BP_BlockI.BP_BlockI'"));
	BlockBP_I = IBlockFinder.Class;
	static ConstructorHelpers::FClassFinder<AActor> RBlockFinder(TEXT("Blueprint'/Game/Meshes/CaveBlocks/BlockBlueprints/BP_BlockR.BP_BlockR'"));
	BlockBP_R = RBlockFinder.Class;
	*/

	/*
	// Set up room static mesh components
	RoomMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh1"));
	RoomMesh1->SetupAttachment(RootComponent);
	RoomMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh2"));
	RoomMesh2->SetupAttachment(RootComponent);
	RoomMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh3"));
	RoomMesh3->SetupAttachment(RootComponent);
	RoomMesh4 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh4"));
	RoomMesh4->SetupAttachment(RootComponent);
	RoomMesh5 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh5"));
	RoomMesh5->SetupAttachment(RootComponent);
	RoomMesh6 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh6"));
	RoomMesh6->SetupAttachment(RootComponent);
	RoomMesh7 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh7"));
	RoomMesh7->SetupAttachment(RootComponent);
	RoomMesh8 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh8"));
	RoomMesh8->SetupAttachment(RootComponent);
	RoomMesh9 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh9"));
	RoomMesh9->SetupAttachment(RootComponent);
	RoomMesh10 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh10"));
	RoomMesh10->SetupAttachment(RootComponent);
	RoomMesh11 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh11"));
	RoomMesh11->SetupAttachment(RootComponent);
	RoomMesh12 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh12"));
	RoomMesh12->SetupAttachment(RootComponent);
	RoomMesh13 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh13"));
	RoomMesh13->SetupAttachment(RootComponent);
	RoomMesh14 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh14"));
	RoomMesh14->SetupAttachment(RootComponent);
	RoomMesh15 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RoomMesh15"));
	RoomMesh15->SetupAttachment(RootComponent);
	
	RoomMeshArray.Empty();
	RoomMeshArray.Emplace(RoomMesh1);
	RoomMeshArray.Emplace(RoomMesh2);
	RoomMeshArray.Emplace(RoomMesh3);
	RoomMeshArray.Emplace(RoomMesh4);
	RoomMeshArray.Emplace(RoomMesh5);
	RoomMeshArray.Emplace(RoomMesh6);
	RoomMeshArray.Emplace(RoomMesh7);
	RoomMeshArray.Emplace(RoomMesh8);
	RoomMeshArray.Emplace(RoomMesh9);
	RoomMeshArray.Emplace(RoomMesh10);
	RoomMeshArray.Emplace(RoomMesh11);
	RoomMeshArray.Emplace(RoomMesh12);
	RoomMeshArray.Emplace(RoomMesh13);
	RoomMeshArray.Emplace(RoomMesh14);
	RoomMeshArray.Emplace(RoomMesh15);
	*/
}

// Called when the game starts or when spawned
void AGenerateLevelActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGenerateLevelActor::AddMeshes()
{
	int numExits;
	int counter = 0;
	int directions[] = { 0, 0, 0, 0 };  // N, E, S, W

	UE_LOG(LogTemp, Warning, TEXT("AddMeshes() called."));
	for (int y = 0; y <= 7; y++)
		for (int x = 0; x <= 7; x++)
			if (counter < 15)
				//if (RoomGrid[x][y] == 9)
				if (RoomGrid[x][y] == 1 || RoomGrid[x][y] == 9)
				{
					UE_LOG(LogTemp, Warning, TEXT("Location X: %d, Y: %d"), x, y);
					
					// count exits & mark directions
					numExits = 0;
					for (int i = 0; i <= 3; i++)
						directions[i] = 0;
					if (x - 1 >= 0)
						if (RoomGrid[x - 1][y] == 1 || RoomGrid[x - 1][y] == 9)
						{
							numExits++;
							directions[3] = 1;
						}
					if (x + 1 <= 7)
						if (RoomGrid[x + 1][y] == 1 || RoomGrid[x + 1][y] == 9)
						{
							numExits++;
							directions[1] = 1;
						}
					if (y - 1 >= 0)
						if (RoomGrid[x][y - 1] == 1 || RoomGrid[x][y - 1] == 9)
						{
							numExits++;
							directions[2] = 1;
						}
					if (y + 1 <= 7)
						if (RoomGrid[x][y + 1] == 1 || RoomGrid[x][y + 1] == 9)
						{
							numExits++;
							directions[0] = 1;
						}

					// Add south exit for entrance block
					if (RoomGrid[x][y] == 9)
					{
						numExits++;
						directions[2] = 1;
					}
					
					UE_LOG(LogTemp, Warning, TEXT("N: %d, E: %d, S: %d, W: %d"), directions[0], directions[1], directions[2], directions[3]);
					
					// Set mesh & rotation
					if (numExits == 4)  // X block
					{
						RoomMeshArray[counter]->SetStaticMesh(XBlockMesh);
					}
					else if (numExits == 3)  // T block
					{
						RoomMeshArray[counter]->SetStaticMesh(TBlockMesh);
						// Set rotation
						if (directions[3] != 1)  // W
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
						else if (directions[1] != 1)  // E
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
						else if (directions[2] != 1)  // S
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
						else if (directions[0] != 1)  // N
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
					}
					else if (numExits == 2)  // L block or I block
					{
						if ((directions[0] == 1 && directions[2] == 1) || (directions[1] == 1 && directions[3] == 1)) // I block
						{
							RoomMeshArray[counter]->SetStaticMesh(IBlockMesh);
							// Set rotation
							if (directions[0] == 1)
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
							else
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
						}
						else // L block
						{
							RoomMeshArray[counter]->SetStaticMesh(LBlockMesh);
							// Set rotation
							if (directions[0] == 1 && directions[3] == 1)
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
							else if (directions[0] == 1 && directions[1] == 1)
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
							else if (directions[1] == 1 && directions[2] == 1)
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
							else if (directions[2] == 1 && directions[3] == 1)
								RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
						}
					}
					else // R block
					{
						RoomMeshArray[counter]->SetStaticMesh(RBlockMesh);
						// Set rotation
						if (directions[0] == 1)
							RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
						else if (directions[1] == 1)
							RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
						else if (directions[2] == 1)
							RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
						else if (directions[3] == 1)
							RoomMeshArray[counter]->SetRelativeRotation(FRotator(0.0f, 180.0f, 0.0f));
					}
					
					// Set location
					RoomMeshArray[counter]->SetWorldLocation(FVector(y * 2000.0f, x * 2000.0f, 0.0f));
					
					UE_LOG(LogTemp, Warning, TEXT("Rotation: %f"), RoomMeshArray[counter]->GetRelativeRotation().Yaw);
					// Increase room counter
					counter++;
				}

}

void AGenerateLevelActor::AddBlocks()
{
	int numExits;
	int counter = 0;
	int directions[] = { 0, 0, 0, 0 };  // N, E, S, W
	FRotator tempRotator;

	// Initialize BlockTypeGrid
	for (int y = 0; y <= 7; y++)
		for (int x = 0; x <= 7; x++)
			BlockTypeGrid[x][y] = 'Z';
	
	UE_LOG(LogTemp, Warning, TEXT("AddBlocks() called."));
	for (int y = 0; y <= 7; y++)
		for (int x = 0; x <= 7; x++)
			if (counter < 15)
				if (RoomGrid[x][y] == 1 || RoomGrid[x][y] == 9)
				{
					UE_LOG(LogTemp, Warning, TEXT("Location X: %d, Y: %d"), x, y);

					// count exits & mark directions
					numExits = 0;
					for (int i = 0; i <= 3; i++)
						directions[i] = 0;
					if (x - 1 >= 0)
						if (RoomGrid[x - 1][y] == 1 || RoomGrid[x - 1][y] == 9)
						{
							numExits++;
							directions[3] = 1;
						}
					if (x + 1 <= 7)
						if (RoomGrid[x + 1][y] == 1 || RoomGrid[x + 1][y] == 9)
						{
							numExits++;
							directions[1] = 1;
						}
					if (y - 1 >= 0)
						if (RoomGrid[x][y - 1] == 1 || RoomGrid[x][y - 1] == 9)
						{
							numExits++;
							directions[2] = 1;
						}
					if (y + 1 <= 7)
						if (RoomGrid[x][y + 1] == 1 || RoomGrid[x][y + 1] == 9)
						{
							numExits++;
							directions[0] = 1;
						}

					// Add south exit for entrance block
					if (RoomGrid[x][y] == 9)
					{
						numExits++;
						directions[2] = 1;

						UE_LOG(LogTemp, Warning, TEXT("Spawning Entrance..."));
						GetWorld()->SpawnActor<AActor>(BlockBP_Entrance, FVector(y * 3200.0f, x * 3200.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
						StartLocation.x = x;
						StartLocation.y = y;
					}

					UE_LOG(LogTemp, Warning, TEXT("N: %d, E: %d, S: %d, W: %d"), directions[0], directions[1], directions[2], directions[3]);

					// Set mesh & rotation
					if (numExits == 4)  // X block
					{
						UE_LOG(LogTemp, Warning, TEXT("Spawn X Block"));
						GetWorld()->SpawnActor<AActor>(BlockBP_X, FVector(y * 3200.0f, x * 3200.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
						BlockTypeGrid[x][y] = 'X';
					}
					else if (numExits == 3)  // T block
					{
						// Set rotation
						if (directions[3] != 1)  // W
							tempRotator = FRotator(0.0f, 270.0f, 0.0f);
						else if (directions[1] != 1)  // E
							tempRotator = FRotator(0.0f, 90.0f, 0.0f);
						else if (directions[2] != 1)  // S
							tempRotator = FRotator(0.0f, 180.0f, 0.0f);
						else if (directions[0] != 1)  // N
							tempRotator = FRotator(0.0f, 0.0f, 0.0f);
						GetWorld()->SpawnActor<AActor>(BlockBP_T, FVector(y * 3200.0f, x * 3200.0f, 0.0f), tempRotator);
						BlockTypeGrid[x][y] = 'T';
					}
					else if (numExits == 2)  // L block or I block
					{
						if ((directions[0] == 1 && directions[2] == 1) || (directions[1] == 1 && directions[3] == 1)) // I block
						{
							// Set rotation
							if (directions[0] == 1)
								tempRotator = FRotator(0.0f, 0.0f, 0.0f);
							else
								tempRotator = FRotator(0.0f, 90.0f, 0.0f);
							GetWorld()->SpawnActor<AActor>(BlockBP_I, FVector(y * 3200.0f, x * 3200.0f, 0.0f), tempRotator);
							BlockTypeGrid[x][y] = 'I';
						}
						else // L block
						{
							// Set rotation
							if (directions[0] == 1 && directions[3] == 1)
								tempRotator = FRotator(0.0f, 0.0f, 0.0f);
							else if (directions[0] == 1 && directions[1] == 1)
								tempRotator = FRotator(0.0f, 90.0f, 0.0f);
							else if (directions[1] == 1 && directions[2] == 1)
								tempRotator = FRotator(0.0f, 180.0f, 0.0f);
							else if (directions[2] == 1 && directions[3] == 1)
								tempRotator = FRotator(0.0f, 270.0f, 0.0f);
							GetWorld()->SpawnActor<AActor>(BlockBP_L, FVector(y * 3200.0f, x * 3200.0f, 0.0f), tempRotator);
							BlockTypeGrid[x][y] = 'L';
						}
					}
					else // R block
					{
						// Set rotation
						if (directions[0] == 1)
							tempRotator = FRotator(0.0f, 270.0f, 0.0f);
						else if (directions[1] == 1)
							tempRotator = FRotator(0.0f, 0.0f, 0.0f);
						else if (directions[2] == 1)
							tempRotator = FRotator(0.0f, 90.0f, 0.0f);
						else if (directions[3] == 1)
							tempRotator = FRotator(0.0f, 180.0f, 0.0f);
						GetWorld()->SpawnActor<AActor>(BlockBP_R, FVector(y * 3200.0f, x * 3200.0f, 0.0f), tempRotator);
						BlockTypeGrid[x][y] = 'R';
					}

					UE_LOG(LogTemp, Warning, TEXT("Rotation: %f"), RoomMeshArray[counter]->GetRelativeRotation().Yaw);
					// Increase room counter
					counter++;
				}

}


void AGenerateLevelActor::AddFuzzies()
{
	FVector FuzzyLocation;
	FRotator FuzzyRotation;
	FActorSpawnParameters SpawnInfo;
	bool validRoom;
	int32 randomX;
	int32 randomY;
	int32 xOffset;
	int32 yOffset;
	int32 zOffset;
	int32 xRot;
	int32 yRot;
	int32 zRot;

	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (int i = 1; i <= 20; i++)
	{
		validRoom = false;
		while (!validRoom)
		{
			randomX = FMath::RandRange(0, 7);
			randomY = FMath::RandRange(0, 7);
			if (RoomGrid[randomX][randomY] == 1)
			{
				validRoom = true;
				xOffset = FMath::RandRange(-500, 500);
				yOffset = FMath::RandRange(-500, 500);
				zOffset = FMath::RandRange(10, 30);
				FuzzyLocation = FVector(randomY * 3200.0f + yOffset, randomX * 3200.0f + xOffset, zOffset);
				UE_LOG(LogTemp, Warning, TEXT("Fuzzy %d: XY: %d, %d Loc: %f, %f"), i, randomX, randomY, randomX * 3200.0f + xOffset, randomY * 3200.0f + yOffset);
				xRot = FMath::RandRange(0, 359);
				yRot = FMath::RandRange(0, 359);
				zRot = FMath::RandRange(0, 359);
				FuzzyRotation = FRotator(xRot, yRot, zRot);

				GetWorld()->SpawnActor<AFuzzyActor>(FuzzyLocation, FuzzyRotation, SpawnInfo);
			}

		}
	}
}

// Called every frame
void AGenerateLevelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGenerateLevelActor::AddDecoration()
{
	FActorSpawnParameters spawnParams;
	int xOffset;
	int yOffset;
	int zOffset;
	int scaleSize;
	FTransform spawnTransform;
	AActor* tempActor;
	int randomInt;
	
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	UE_LOG(LogTemp, Warning, TEXT("AddDecoration() called."));
	for (int y = 0; y <= 7; y++)
		for (int x = 0; x <= 7; x++)
		{
			// Add rock pile
			if (BlockTypeGrid[x][y] != 'Z')
			{
				if (FMath::RandRange(0, 1) == 1)
				{
					xOffset = FMath::RandRange(-1200, 1200);
					yOffset = FMath::RandRange(-1200, 1200);
					tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_RockPile, FVector(y * 3200 + yOffset, x * 3200 + xOffset, -20.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
					scaleSize = FMath::RandRange(50, 100);
					tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, 1.0f));
				}
			}
			
			// Add rocks
			if (BlockTypeGrid[x][y] != 'Z')
			{
				randomInt = FMath::RandRange(0, 4) + 3;
				for (int i = 0; i <= randomInt; i++)
				{
					xOffset = FMath::RandRange(-1200, 1200);
					yOffset = FMath::RandRange(-1200, 1200);
					if (BlockTypeGrid[x][y] == 'L')
					{
						zOffset = FMath::RandRange(-40, -20);
					}
					else
					{
						zOffset = FMath::RandRange(0, 10);
					}

					if (FMath::RandRange(0, 1) == 1)
					{
						tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Rock2, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f + zOffset), FRotator((float)FMath::RandRange(0, 359), (float)FMath::RandRange(0, 359), (float)FMath::RandRange(0, 359)), spawnParams);
						scaleSize = FMath::RandRange(50, 250);
						tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
					}
					else
					{
						tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Rock3, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f + zOffset), FRotator((float)FMath::RandRange(0, 359), (float)FMath::RandRange(0, 359), (float)FMath::RandRange(0, 359)), spawnParams);
						scaleSize = FMath::RandRange(10, 60);
						tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
					}
				}
			}

			if (BlockTypeGrid[x][y] == 'R' || BlockTypeGrid[x][y] == 'T' || BlockTypeGrid[x][y] == 'X')
			{
				// Add 1st floor (small)
				xOffset = FMath::RandRange(-1300, 1300);
				yOffset = FMath::RandRange(-1300, 1300);
				GetWorld()->SpawnActor<AActor>(CaveBP_Floor2, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
				// Add 2nd floor (33% chance for big)
				xOffset = FMath::RandRange(-1300, 1300);
				yOffset = FMath::RandRange(-1300, 1300);
				if (FMath::RandRange(0, 2) == 1)
				{
					GetWorld()->SpawnActor<AActor>(CaveBP_Floor2, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
				}
				else
				{
					scaleSize = FMath::RandRange(25, 75);
					spawnTransform = FTransform(FQuat(FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f)), FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
					tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Floor1, spawnTransform, spawnParams);
					tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
				}

				// Add columns
				randomInt = FMath::RandRange(0, 3);
				for (int i = 1; i <= randomInt; i++)
				{
					if (FMath::RandRange(0, 1) == 0)
					{
						xOffset = FMath::RandRange(-1400, 1400);
						yOffset = FMath::RandRange(-1400, 1400); 
						tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Column1, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
						scaleSize = FMath::RandRange(75, 125);
						tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, 1.0f));
					}
					else
					{
						xOffset = FMath::RandRange(-1400, 1400);
						yOffset = FMath::RandRange(-1400, 1400); 
						tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Column2, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
						scaleSize = FMath::RandRange(75, 125);
						tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, 1.0f));
					}
				}

				// Add mites
				randomInt = FMath::RandRange(0, 3);
				if (randomInt == 1)
				{
					xOffset = FMath::RandRange(-1400, 1400);
					yOffset = FMath::RandRange(-1400, 1400);
					tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Mite1, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
					scaleSize = FMath::RandRange(50, 125);
					tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
				}
				else if (randomInt == 2)
				{
					xOffset = FMath::RandRange(-1400, 1400);
					yOffset = FMath::RandRange(-1400, 1400);
					tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Mite2, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
					scaleSize = FMath::RandRange(50, 125);
					tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
				}
				else if (randomInt == 3)
				{
					for (int i = 0; i <= 1; i++)
					{
						if (FMath::RandRange(0, 1) == 0)
						{
							xOffset = FMath::RandRange(-1400, 1400);
							yOffset = FMath::RandRange(-1400, 1400);
							tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Mite1, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
							scaleSize = FMath::RandRange(50, 125);
							tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
						}
						else
						{
							xOffset = FMath::RandRange(-1400, 1400);
							yOffset = FMath::RandRange(-1400, 1400);
							tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Mite2, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
							scaleSize = FMath::RandRange(50, 125);
							tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
						}
					}
				}
				
				// Add arches
				if (FMath::RandRange(0, 3) == 2)
				{
					xOffset = FMath::RandRange(500, 1400);
					yOffset = FMath::RandRange(500, 1400);
					if (FMath::RandRange(0, 1) == 1)
					{
						xOffset *= -1;
					}
					if (FMath::RandRange(0, 1) == 1)
					{
						yOffset *= -1;
					}
					tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Arch, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
					scaleSize = FMath::RandRange(75, 125);
					tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
				}
			}
			//else if (BlockTypeGrid[x][y] == 'L' || BlockTypeGrid[x][y] == 'I')
			else if (BlockTypeGrid[x][y] == 'I')
			{
				// Add floor (25% chance for big)
				xOffset = FMath::RandRange(-1300, 1300);
				yOffset = FMath::RandRange(-1300, 1300);
				if (FMath::RandRange(0, 3) == 1)
				{
					scaleSize = FMath::RandRange(15, 60);
					spawnTransform = FTransform(FQuat(FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f)), FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
					tempActor = GetWorld()->SpawnActor<AActor>(CaveBP_Floor1, spawnTransform, spawnParams);
					tempActor->SetActorScale3D(FVector(scaleSize / 100.0f, scaleSize / 100.0f, scaleSize / 100.0f));
				}
				else
				{
					GetWorld()->SpawnActor<AActor>(CaveBP_Floor2, FVector(y * 3200 + yOffset, x * 3200 + xOffset, 0.0f), FRotator(0.0f, (float)FMath::RandRange(0, 359), 0.0f), spawnParams);
				}
			}
			
		}

}

void AGenerateLevelActor::GenerateLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("GenerateLevel() called."));
	
	// Calculate number of fuzzies
	NumCurrentRed = 0;
	NumCurrentBlue = 0;
	NumCurrentYellow = 0;
	NumTargetRed = FMath::RandRange(3, 8);
	NumTargetBlue = FMath::RandRange(3, 8);
	NumTargetYellow = FMath::RandRange(3, 8);

	CreateGrid();
	//AddMeshes();
	AddBlocks();
	AddFuzzies();
	AddDecoration();
	


	// Move player to entrance
	UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->SetActorLocation(FVector(-4500.0f, StartLocation.x * 3200.0f - 18.0f, 490.0f), false, 0, ETeleportType::None);
}

void AGenerateLevelActor::MarkGrid(int x, int y)
{
	int adjSquares[] = { 0, 0, 0, 0 };
	int32 randomInt;
	
	if (x - 1 >= 0)
		if (RoomGrid[x - 1][y] == 0)
		{
			RoomGrid[x - 1][y] = 2;
			adjSquares[0] = RoomGrid[x - 1][y];
		}
	if (x + 1 <= 7)
		if (RoomGrid[x + 1][y] == 0)
		{
			RoomGrid[x + 1][y] = 2;
			adjSquares[1] = RoomGrid[x + 1][y];
		}
	if (y - 1 >= 0)
		if (RoomGrid[x][y - 1] == 0)
		{
			RoomGrid[x][y - 1] = 2;
			adjSquares[2] = RoomGrid[x][y - 1];
		}
	if (y + 1 <= 7)
		if (RoomGrid[x][y + 1] == 0)
		{
			RoomGrid[x][y + 1] = 2;
			adjSquares[3] = RoomGrid[x][y + 1];
		}

	// Eliminate one possible exit
	int count = 0;
	for (int i = 0; i <= 3; i++)
	{
		if (adjSquares[i] == 2)
		{
			count++;
		}
	}
	if (count >= 2)
	{
		bool valid = false;
		while (!valid)
		{
			randomInt = FMath::RandRange(0, 3);
			if (adjSquares[randomInt] == 2)
			{
				valid = true;
				if (randomInt == 0)
					RoomGrid[x - 1][y] = 3;
				else if (randomInt == 1)
					RoomGrid[x + 1][y] = 3;
				else if (randomInt == 2)
					RoomGrid[x][y - 1] = 3;
				else
					RoomGrid[x][y + 1] = 3;
			}
		}
	}
}

void AGenerateLevelActor::CreateGrid()
{
	int32 randomInt;
	TArray<XY> XYArray;
	XY tempXY;

	UE_LOG(LogTemp, Warning, TEXT("CreateGrid() called. Grid generation beginning..."))
	
	// Initialize grid
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			RoomGrid[i][j] = 0;
	
	// Create entrance
	randomInt = FMath::RandRange(0, 7);
	RoomGrid[randomInt][0] = 9;
	MarkGrid(randomInt, 0);
	UE_LOG(LogTemp, Warning, TEXT("Room # 1 created."));

	// Fill out rooms from entrance
	for (int count = 2; count <= NumRooms; count++)
	{
		XYArray.Empty();
		for (int i = 0; i <= 7; i++)
			for (int j = 0; j <= 7; j++)
			{
				if (RoomGrid[i][j] == 2)
				{
					tempXY.x = i;
					tempXY.y = j;
					XYArray.Emplace(tempXY);
				}
			}
		randomInt = FMath::RandRange(0, XYArray.Num()-1);
		RoomGrid[XYArray[randomInt].x][XYArray[randomInt].y] = 1;
		MarkGrid(XYArray[randomInt].x, XYArray[randomInt].y);

		UE_LOG(LogTemp, Warning, TEXT("Room # %d created."), count);
	}

	UE_LOG(LogTemp, Warning, TEXT("Grid generation ended."))
	for (int y = 7; y >= 0; y--)
		UE_LOG(LogTemp, Warning, TEXT("Row %d: %d %d %d %d %d %d %d %d"), y, RoomGrid[0][y], RoomGrid[1][y], RoomGrid[2][y], RoomGrid[3][y], RoomGrid[4][y], RoomGrid[5][y], RoomGrid[6][y], RoomGrid[7][y]);
}
