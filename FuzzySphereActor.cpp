// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzySphereActor.h"
#include "Kismet/GameplayStatics.h"
#include "ProceduralTestCharacter.h"
#include "GenerateLevelActor.h"

// Sets default values
AFuzzySphereActor::AFuzzySphereActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticAsset(TEXT("StaticMesh'/Game/Meshes/Fuzzies/sea_urchin_FBX.sea_urchin_FBX'"));
	SphereMesh = StaticAsset.Object;
	StaticMeshComponent->SetStaticMesh(SphereMesh);
	StaticMeshComponent->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	static ConstructorHelpers::FObjectFinder<UMaterial> Mat1Asset(TEXT("Material'/Game/HUD/M_FuzzyRed.M_FuzzyRed'"));
	SphereMatRed = Mat1Asset.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> Mat1AssetGlow(TEXT("Material'/Game/HUD/M_FuzzyGlowRed.M_FuzzyGlowRed'"));
	SphereMatRedGlow = Mat1AssetGlow.Object; 
	static ConstructorHelpers::FObjectFinder<UMaterial> Mat2Asset(TEXT("Material'/Game/HUD/M_FuzzyYellow.M_FuzzyYellow'"));
	SphereMatYellow = Mat2Asset.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> Mat2AssetGlow(TEXT("Material'/Game/HUD/M_FuzzyGlowYellow.M_FuzzyGlowYellow'"));
	SphereMatYellowGlow = Mat2AssetGlow.Object; 
	static ConstructorHelpers::FObjectFinder<UMaterial> Mat3Asset(TEXT("Material'/Game/HUD/M_FuzzyBlue.M_FuzzyBlue'"));
	SphereMatBlue = Mat3Asset.Object;
	static ConstructorHelpers::FObjectFinder<UMaterial> Mat3AssetGlow(TEXT("Material'/Game/HUD/M_FuzzyGlowBlue.M_FuzzyGlowBlue'"));
	SphereMatBlueGlow = Mat3AssetGlow.Object;

	//StaticMeshComponent->SetMaterial(0, SphereMatRed);
	//StaticMeshComponent->SetMaterial(1, SphereMatRedGlow);

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComp->SetupAttachment(RootComponent);
	SphereComp->InitSphereRadius(30.0f);

	TextComp = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender"));
	TextComp->SetupAttachment(RootComponent);
	TextComp->SetText("Press E to collect");
	TextComp->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	TextComp->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
	TextComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	// Set HUD widget
	static ConstructorHelpers::FClassFinder<UWidgetBlueprint> HUDObj(TEXT("/Game/HUD/Widget_TestHUD"));
	HUDWidgetClass = HUDObj.Class;
}

void AFuzzySphereActor::GrabFuzzy()
{
	AActor* MyLevelActor; 
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("GRAB FUZZY"));

	MyLevelActor = UGameplayStatics::GetActorOfClass(GetWorld(), AGenerateLevelActor::StaticClass());

	if (FuzzyColor == 0)
	{
		Cast<AGenerateLevelActor>(MyLevelActor)->NumCurrentRed++;
	}
	else if (FuzzyColor == 1)
	{
		Cast<AGenerateLevelActor>(MyLevelActor)->NumCurrentBlue++;
	}
	else
	{
		Cast<AGenerateLevelActor>(MyLevelActor)->NumCurrentYellow++;
	}

	//HUDWidget = 
	//UE_LOG(LogTemp, Warning, TEXT("HUD class = %s"), UGameplayStatics::GetPlayerController()->GetHUD()->Get)


	this->Destroy();
}

// Called when the game starts or when spawned
void AFuzzySphereActor::BeginPlay()
{
	AActor* MyLevelActor;
	bool fuzzyPlaced;

	Super::BeginPlay();
	
	MyLevelActor = UGameplayStatics::GetActorOfClass(GetWorld(), AGenerateLevelActor::StaticClass());
	fuzzyPlaced = false;

	while (!fuzzyPlaced)
	{
		int32 randomInt = FMath::RandRange(0, 2);
		if (randomInt == 0)
		{
			// Spawn red fuzzy if target number has not been found
			if (Cast<AGenerateLevelActor>(MyLevelActor)->NumCurrentRed < Cast<AGenerateLevelActor>(MyLevelActor)->NumTargetRed)
			{
				StaticMeshComponent->SetMaterial(0, SphereMatRed);
				StaticMeshComponent->SetMaterial(1, SphereMatRedGlow);
				FuzzyColor = 0;
				fuzzyPlaced = true;
			}
		}
		else if (randomInt == 1)
		{
			// Spawn blue fuzzy if target number has not been found
			if (Cast<AGenerateLevelActor>(MyLevelActor)->NumCurrentBlue < Cast<AGenerateLevelActor>(MyLevelActor)->NumTargetBlue)
			{
				StaticMeshComponent->SetMaterial(0, SphereMatBlue);
				StaticMeshComponent->SetMaterial(1, SphereMatBlueGlow);
				FuzzyColor = 1;
				fuzzyPlaced = true;
			}
		}
		else
		{
			// Spawn yellow fuzzy if target number has not been found
			if (Cast<AGenerateLevelActor>(MyLevelActor)->NumCurrentYellow < Cast<AGenerateLevelActor>(MyLevelActor)->NumTargetYellow)
			{
				StaticMeshComponent->SetMaterial(0, SphereMatYellow);
				StaticMeshComponent->SetMaterial(1, SphereMatYellowGlow);
				FuzzyColor = 2;
				fuzzyPlaced = true;
			}
		}
	}
	this->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0)); 
	
	if (InputComponent)
	{
		InputComponent->BindAction("GrabFuzzy", IE_Pressed, this, &AFuzzySphereActor::GrabFuzzy);

	}
	
	
	//MyMode = Cast<AProceduralTestGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

}

// Called every frame
void AFuzzySphereActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//MyChar = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	MyController = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (MyController)
	{
		//MyTransform = MyChar->GetActorRotation();
		TextComp->SetWorldRotation(MyController->GetControlRotation());
		TextComp->AddLocalRotation(FRotator(0.0f, 180.0f, 0.0f));
	}
}



