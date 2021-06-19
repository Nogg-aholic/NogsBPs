

#pragma once

#include "CoreMinimal.h"
#include "FGSchematic.h"
#include "AvailabilityDependencies/FGItemPickedUpDependency.h"
#include "AvailabilityDependencies/FGSchematicPurchasedDependency.h"
#include "AvailabilityDependencies/FGRecipeUnlockedDependency.h"
#include "AvailabilityDependencies/FGGamePhaseReachedDependency.h"
#include "Unlocks/FGUnlock.h"
#include "Unlocks/FGUnlockArmEquipmentSlot.h"
#include "Unlocks/FGUnlockBuildEfficiency.h"
#include "Unlocks/FGUnlockBuildOverclock.h"
#include "Unlocks/FGUnlockGiveItem.h"
#include "Unlocks/FGUnlockInventorySlot.h"
#include "Unlocks/FGUnlockMap.h"
#include "Unlocks/FGUnlockRecipe.h"
#include "Unlocks/FGUnlockScannableResource.h"
#include "Unlocks/FGUnlockSchematic.h"
#include "FGSchematicCategory.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SchematicFunctionLib.generated.h"



/**
 * 
 */
UCLASS()
class NOGSBPS_API USchematicFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetDisplayName(TSubclassOf<UFGSchematic> inClass, FText Name);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetDescription(TSubclassOf<UFGSchematic> inClass, FText Description);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetType(TSubclassOf<UFGSchematic> inClass, ESchematicType Type);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetTechTier(TSubclassOf<UFGSchematic> inClass, int32 Tier);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetSchematicCategory(TSubclassOf<UFGSchematic> inClass, TSubclassOf<class UFGSchematicCategory> Cat);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetSubCategories(TSubclassOf<UFGSchematic> inClass,
	                             TArray<TSubclassOf<class UFGSchematicCategory>> Cat);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetCost(TSubclassOf<UFGSchematic> inClass, TArray<FItemAmount> Cost);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetTimeToComplete(TSubclassOf<UFGSchematic> inClass, float sec);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetUnlocks(TSubclassOf<UFGSchematic> inClass, TArray<class UFGUnlock*> Unlocks);
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetSchematicIcon(TSubclassOf<UFGSchematic> inClass, FSlateBrush Icon);

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
	static void SetDependsOnSchematic(TSubclassOf<UFGSchematic> inClass, TArray<class UFGAvailabilityDependency*> Deps);


	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * Object, TArray< TSubclassOf< class UFGSchematic > > Schematics, bool bRequireAllSchematicsToBePurchased);

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void GetSchematicDependencies(TSubclassOf< UFGSchematic > inClass, UPARAM(ref) TArray<  UFGAvailabilityDependency* >& out_schematicDependencies);


};
