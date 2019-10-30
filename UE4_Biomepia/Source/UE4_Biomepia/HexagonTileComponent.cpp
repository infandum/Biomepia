// Fill out your copyright notice in the Description page of Project Settings.


#include "HexagonTileComponent.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UHexagonTileComponent::UHexagonTileComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	////SceneComponent->Mobility = EComponentMobility::Static;
	//RootComponent = SceneComponent;

	if (StaticMesh == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No default mesh was set, setting default 1M_Hexagon"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshObj(TEXT("/Game/Geometry/Meshes/1M_Hexagon"));
		StaticMesh = StaticMeshObj.Object;
	}

	//if (StaticMesh)
	//{

	//	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	//	MeshComponent->RegisterComponent();
	//	MeshComponent->SetStaticMesh(StaticMesh);
	//		//MeshComponent->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
	//		//MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	//}
}


// Called when the game starts
void UHexagonTileComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHexagonTileComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

