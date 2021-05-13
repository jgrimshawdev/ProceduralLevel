// Fill out your copyright notice in the Description page of Project Settings.


#include "FuzzyActor.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "FuzzySphereActor.h"
#include "ProceduralTestGameMode.h"
#include "Blueprint/UserWidget.h"

// Sets default values
AFuzzyActor::AFuzzyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up root component
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	DestructibleComponent = CreateDefaultSubobject<UDestructibleComponent>(TEXT("Destructible Component"));
	DestructibleComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UDestructibleMesh> MeshAsset(TEXT("DestructibleMesh'/Game/Meshes/Rocks/Rock_1_DM.Rock_1_DM'"));
	DestMesh = MeshAsset.Object;
	DestructibleComponent->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	DestructibleComponent->SetVisibility(false);
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh Component"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticAsset(TEXT("StaticMesh'/Game/Meshes/Rocks/Rock_1.Rock_1'"));
	StatMesh = StaticAsset.Object;
	StaticMeshComponent->SetStaticMesh(StatMesh);
	StaticMeshComponent->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));
	


	TriggerComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	TriggerComponent->SetupAttachment(RootComponent);
	TriggerComponent->SetNotifyRigidBodyCollision(true);
	TriggerComponent->InitBoxExtent(FVector(30.0f, 30.0f, 30.0f));

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(RootComponent);
	SphereComponent->InitSphereRadius(500.0f);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFuzzyActor::OnSphereOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AFuzzyActor::OnSphereOverlapEnd);
	
	IsDestroyed = false;
	IsTriggerEnabled = false;

	MaxHealth = 10.0f;

	DefaultDamage = 10.0f;
	DefaultImpulse = 1.0f;

	// Set indicator widget
	static ConstructorHelpers::FClassFinder<UUserWidget> IndicatorObj(TEXT("/Game/HUD/Widget_Indicator"));
	IndicatorWidgetClass = IndicatorObj.Class;

	static ConstructorHelpers::FObjectFinder<UParticleSystem> PSAsset(TEXT("ParticleSystem'/Game/TS_Fireworks/Particles/PS_RockTest.PS_RockTest'"));
	ParticleSys = PSAsset.Object;

}

void AFuzzyActor::Damage(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsDestroyed && OtherComp->GetName() == "Tool")
	{
		CurrentHealth -= 1.0f;
		if (CurrentHealth <= 0.0f)
		{
			DestroyRock(DefaultDamage, Hit.Location, NormalImpulse, DefaultImpulse);
		}
	}
}

void AFuzzyActor::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AProceduralTestGameMode* MyMode = Cast<AProceduralTestGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyMode->IsSwinging)
		{
			MyHit = SweepResult;

			GetWorldTimerManager().SetTimer(DamageTimer, this, &AFuzzyActor::DamageRock, 1.0f, false, 0.0f);
		}
	}
	
	if (!IsDestroyed && IsTriggerEnabled && OtherComp->GetName() == "Tool")
	{
		DestroyRock(DefaultDamage, DestructibleComponent->GetComponentLocation(), DestructibleComponent->GetForwardVector(), DefaultImpulse);
	}
}

void AFuzzyActor::DestroyRock(float Damage, FVector HitLocation, FVector ImpulseDirection, float Impulse)
{
	if (!IsDestroyed)
	{
		IsDestroyed = true;

		DestructibleComponent->ApplyDamage(Damage, HitLocation, ImpulseDirection, Impulse);
	}
}

void AFuzzyActor::DamageRock()
{
	DestructibleComponent->SetDestructibleMesh(DestMesh);
	StaticMeshComponent->SetVisibility(false);

	DestroyRock(0.1f, MyHit.Location, DestructibleComponent->GetForwardVector(), 0.1f);

	// Spawn fuzzy sphere
	FVector zOffset = FVector(0.0f, 0.0f, 100.0f);
	FActorSpawnParameters SpawnInfo;
	AFuzzySphereActor* FuzzySphere;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSys, this->GetActorLocation(), this->GetActorRotation(), FVector(1.0f, 1.0f, 1.0f), true, EPSCPoolMethod::None, true);
	
	FuzzySphere = GetWorld()->SpawnActor<AFuzzySphereActor>(this->GetActorLocation() + zOffset, FRotator(0.0f, 0.0f, 0.0f), SpawnInfo);
	int32 randomInt = FMath::RandRange(0, 2);
	
	this->Destroy();

}

// Called when the game starts or when spawned
void AFuzzyActor::BeginPlay()
{
	Super::BeginPlay();
	
	DestructibleComponent->OnComponentHit.AddDynamic(this, &AFuzzyActor::Damage);

	TriggerComponent->OnComponentBeginOverlap.AddDynamic(this, &AFuzzyActor::Trigger);

	CurrentHealth = MaxHealth;
}

// Called every frame
void AFuzzyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuzzyActor::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Sphere Overlap Begin on %s"), *this->GetName());

	// Display indicator widget
	if (IndicatorWidgetClass != nullptr)
	{
		if (!IndicatorWidget)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load IndicatorWidget"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load IndicatorWidgetClass"));
	}
}

void AFuzzyActor::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Sphere Overlap End"));
}