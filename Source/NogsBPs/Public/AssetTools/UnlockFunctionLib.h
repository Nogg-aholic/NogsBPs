

#pragma once

#include "CoreMinimal.h"
#include "FGSchematic.h"
#include "Unlocks/FGUnlockRecipe.h"
#include "Unlocks/FGUnlockScannableResource.h"
#include "Unlocks/FGUnlockInventorySlot.h"
#include "Unlocks/FGUnlockArmEquipmentSlot.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnlockFunctionLib.generated.h"

template<typename Tag, typename Tag::type M>
struct Rob {
	friend typename Tag::type get(Tag) {
		return M;
	}
};


struct AFScannableResourcePair_steal {
	typedef TArray<FScannableResourcePair> UFGUnlockScannableResource::* type;
	friend type get(AFScannableResourcePair_steal);
};

struct mIncludeInBuilds_steal {
	typedef EIncludeInBuilds UFGSchematic::* type;
	friend type get(mIncludeInBuilds_steal);
};

template struct Rob<AFScannableResourcePair_steal, &UFGUnlockScannableResource::mResourcePairsToAddToScanner>;



template struct Rob<mIncludeInBuilds_steal, &UFGSchematic::mIncludeInBuilds>;


/**
 * 
 */
UCLASS()
class NOGSBPS_API UUnlockFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitRecipeUnlocks(UFGUnlockRecipe * Obj, TArray< TSubclassOf< class UFGRecipe > > recipes);
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitScannableUnlocks(UFGUnlockScannableResource * Obj, TArray< FScannableResourcePair > recipes) { Obj->*get(AFScannableResourcePair_steal()) = recipes; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitUnlockInventorySlot(UFGUnlockInventorySlot * Obj, int32 count);
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitUnlockArmEquipmentSlot(UFGUnlockArmEquipmentSlot * Obj, int32 count);

	
};
