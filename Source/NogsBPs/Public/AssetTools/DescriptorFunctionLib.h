

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGItemCategory.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DescriptorFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class NOGSBPS_API UDescriptorFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetUseName(TSubclassOf<UFGItemDescriptor> item, bool UseName);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetName(TSubclassOf<UFGItemDescriptor> item, FText Name);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetDescription(TSubclassOf<UFGItemDescriptor> item, FText Name);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetMesh(TSubclassOf<UFGItemDescriptor> item, UStaticMesh* Mesh);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetMaterial(TSubclassOf< UFGItemDescriptor > item, UMaterialInterface * Mat);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetBigIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D* Icon);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetSmallIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D* Icon);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetFluidColor(TSubclassOf<UFGItemDescriptor> item, FColor Value);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetForm(TSubclassOf<UFGItemDescriptor> item, EResourceForm Value);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetCategory(TSubclassOf<UFGItemDescriptor> item, TSubclassOf<UFGItemCategory> Value);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetCanbeDisgarded(TSubclassOf<UFGItemDescriptor> item, bool Value);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetRememberPickUp(TSubclassOf<UFGItemDescriptor> item, bool Value);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetEnergyValue(TSubclassOf<UFGItemDescriptor> item, float Value);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetRadioactiveDecay(TSubclassOf<UFGItemDescriptor> item, float Value);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
	static void SetStackSize(TSubclassOf<UFGItemDescriptor> item, EStackSize Value);
	UFUNCTION(BlueprintPure, Category = "Editor| Item")
	static EStackSize GetStackSize(TSubclassOf<UFGItemDescriptor> item);
};
