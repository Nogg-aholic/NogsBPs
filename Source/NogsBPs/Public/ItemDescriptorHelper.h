// ILikeBanas

#pragma once

#include "CoreMinimal.h"
#include "FGItemDescriptor.h"
#include "FGResearchTree.h"
#include "FGSchematic.h"
#include "FGRecipe.h"
#include "FGUnlockRecipe.h"
#include "FGUnlockScannableResource.h"
#include "FGUnlockInventorySlot.h"
#include "FGUnlockArmEquipmentSlot.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGSchematicPurchasedDependency.h"

#include "UObject/UObjectGlobals.h" 
#include "FGSchematicPurchasedDependency.h"

#include "ItemDescriptorHelper.generated.h"


/**
 * 
 */
UCLASS()
class NOGSBPS_API UItemDescriptorHelper : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


		//** Defaul Set Functions for BP
		UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetUseName(TSubclassOf< UFGItemDescriptor > item, bool UseName) { item.GetDefaultObject()->mUseDisplayNameAndDescription = UseName; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetName(TSubclassOf< UFGItemDescriptor > item, FText Name) { item.GetDefaultObject()->mDisplayName = Name; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetDescription(TSubclassOf< UFGItemDescriptor > item, FText Name) { item.GetDefaultObject()->mDescription = Name; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetMesh(TSubclassOf< UFGItemDescriptor > item, UStaticMesh * Mesh) { item.GetDefaultObject()->mConveyorMesh = Mesh; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetMaterial(TSubclassOf< UFGItemDescriptor > item, UMaterialInterface * Mat) { item.GetDefaultObject()->mConveyorMesh->SetMaterial(0, Mat); }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetBigIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D *Icon) { item.GetDefaultObject()->mPersistentBigIcon = Icon; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetSmallIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D *Icon) { item.GetDefaultObject()->mSmallIcon = Icon; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetFluidDensity(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mFluidDensity = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetFluidViscosity(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mFluidViscosity = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetFluidFriction(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mFluidFriction = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetFluidColor(TSubclassOf<UFGItemDescriptor> item, FColor  Value) { item.GetDefaultObject()->mFluidColor = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetForm(TSubclassOf<UFGItemDescriptor> item, EResourceForm  Value) { item.GetDefaultObject()->mForm = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetCategory(TSubclassOf<UFGItemDescriptor> item, TSubclassOf<UFGItemCategory>  Value) { item.GetDefaultObject()->mItemCategory = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetCanbeDisgarded(TSubclassOf<UFGItemDescriptor> item, bool  Value) { item.GetDefaultObject()->mCanBeDiscarded = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetRememberPickUp(TSubclassOf<UFGItemDescriptor> item, bool  Value) { item.GetDefaultObject()->mRememberPickUp = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetEnergyValue(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mEnergyValue = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetRadioactiveDecay(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mRadioactiveDecay = Value; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Item")
		static void SetStackSize(TSubclassOf<UFGItemDescriptor> item, EStackSize  Value) { item.GetDefaultObject()->mStackSize = Value; }
	UFUNCTION(BlueprintPure, Category = "Editor|Item")
		static EStackSize GetStackSize(TSubclassOf<UFGItemDescriptor> item) { return item.GetDefaultObject()->mStackSize; }

	// Schematic stuff

	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetType(TSubclassOf< UFGSchematic > inClass, ESchematicType Type) { inClass.GetDefaultObject()->mType = Type; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetDisplayName(TSubclassOf< UFGSchematic > inClass, FText Name) { inClass.GetDefaultObject()->mDisplayName = Name; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetSchemCategory(TSubclassOf< UFGSchematic > inClass, TSubclassOf<class UFGSchematicCategory> Cat) { inClass.GetDefaultObject()->mSchematicCategory = Cat; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetSubCategories(TSubclassOf< UFGSchematic > inClass, TArray < TSubclassOf<class UFGSchematicCategory>> Cat) { inClass.GetDefaultObject()->mSubCategories = Cat; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetCost(TSubclassOf< UFGSchematic > inClass, TArray<FItemAmount> Cost) { inClass.GetDefaultObject()->mCost = Cost; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetTimeToComplete(TSubclassOf< UFGSchematic > inClass, float sec) { inClass.GetDefaultObject()->mTimeToComplete = sec; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetUnlocks(TSubclassOf< UFGSchematic > inClass, TArray< class UFGUnlock* > Unlocks) { inClass.GetDefaultObject()->mUnlocks = Unlocks; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetSchematicIcon(TSubclassOf< UFGSchematic > inClass, FSlateBrush Icon) { inClass.GetDefaultObject()->mSchematicIcon = Icon; }

	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetDependsOnSchematic(TSubclassOf< UFGSchematic > inClass, TArray<UFGAvailabilityDependency*> Deps) {
		inClass.GetDefaultObject()->mSchematicDependencies = Deps;
	}
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetAdditionalDependsOnSchematic(TSubclassOf< UFGSchematic > inClass, TArray < TSubclassOf< UFGSchematic >> Dep) { inClass.GetDefaultObject()->mAdditionalSchematicDependencies = Dep; }
	UFUNCTION(BlueprintCallable, Category = "Editor|Schematic")
		static void SetTechTier(TSubclassOf< UFGSchematic > inClass, int32 Tier) { inClass.GetDefaultObject()->mTechTier = Tier; }





	// Recipe Stuff
	UFUNCTION(BlueprintCallable, Category = "Editor|Recipe")
		static void SetRecipeName(TSubclassOf<UFGRecipe> recipe, FText Name) { recipe.GetDefaultObject()->mDisplayName = Name; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Recipe")
		static void SetIngredient(TSubclassOf<UFGRecipe> recipe, TArray<FItemAmount> ingredient) { recipe.GetDefaultObject()->mIngredients = ingredient; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Recipe")
		static void SetProduct(TSubclassOf< UFGRecipe > recipe, TArray< FItemAmount > product) { recipe.GetDefaultObject()->mProduct = product; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Recipe")
		static void SetManufactoringDuration(TSubclassOf<UFGRecipe> recipe, float sec) { recipe.GetDefaultObject()->mManufactoringDuration = sec; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Recipe")
		static void SetManualManufacturingMultiplier(TSubclassOf<UFGRecipe> recipe, float val) { recipe.GetDefaultObject()->mManualManufacturingMultiplier = val; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Recipe")
		static void SetProducedIn(TSubclassOf<UFGRecipe> recipe, TArray< TSoftClassPtr< UObject > > mProducedIn) { recipe.GetDefaultObject()->mProducedIn = mProducedIn; };
	UFUNCTION(BlueprintCallable, Category = "Editor|Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClass(TArray<UObject*> In);


	// FG Unlock

	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitRecipeUnlocks(UFGUnlockRecipe * Obj, TArray< TSubclassOf< class UFGRecipe > > recipes) { Obj->Init(recipes); }
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitScannableUnlocks(UFGUnlockScannableResource * Obj, TArray< TSubclassOf< class UFGResourceDescriptor > > recipes) { Obj->Init(recipes); }
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitUnlockInventorySlot(UFGUnlockInventorySlot * Obj, int32 count) { Obj->Init(count); }
	UFUNCTION(BlueprintCallable, Category = "Editor|Unlock")
		static void InitUnlockArmEquipmentSlot(UFGUnlockArmEquipmentSlot * Obj, int32 count) { Obj->Init(count); }


	// FG ResearchTree
	UFUNCTION(BlueprintCallable, Category = "Editor|ResearchTree")
		static void SetRecipeDisplayName(TSubclassOf < UFGResearchTree>  Obj, FText mDisplayName) { Obj.GetDefaultObject()->mDisplayName = mDisplayName; }
	UFUNCTION(BlueprintCallable, Category = "Editor|ResearchTree")
		static void SetPreUnlockDisplayName(TSubclassOf < UFGResearchTree>  Obj, FText mPreUnlockDisplayName) { Obj.GetDefaultObject()->mPreUnlockDisplayName = mPreUnlockDisplayName; }
	UFUNCTION(BlueprintCallable, Category = "Editor|ResearchTree")
		static void SetPreUnlockDescription(TSubclassOf < UFGResearchTree>  Obj, FText mPreUnlockDescription) { Obj.GetDefaultObject()->mPreUnlockDescription = mPreUnlockDescription; }
	UFUNCTION(BlueprintCallable, Category = "Editor|ResearchTree")
		static void SetPostUnlockDescription(TSubclassOf < UFGResearchTree> Obj, FText mPostUnlockDescription) { Obj.GetDefaultObject()->mPostUnlockDescription = mPostUnlockDescription; }
	UFUNCTION(BlueprintCallable, Category = "Editor|ResearchTree")
		static void SetResearchTreeIcon(TSubclassOf < UFGResearchTree>  Obj, FSlateBrush mResearchTreeIcon) { Obj.GetDefaultObject()->mResearchTreeIcon = mResearchTreeIcon; }


	//void Init(int32 numInventorySlotsToUnlock) { mNumInventorySlotsToUnlock = numInventorySlotsToUnlock; }

	//void Init(TArray< TSubclassOf< class UFGResourceDescriptor > > resources) { mResourcesToAddToScanner = resources; }
		//FText mPreUnlockDisplayName;

	/** The name to be displayed to the player after the tree is unlocked */
		//FText mDisplayName;

	/** The description to be displayed to the player before the tree is unlocked */
		//FText mPreUnlockDescription;

	/** The description to be displayed to the player after the tree is unlocked */
		//FText mPostUnlockDescription;

	/** Icon used when displaying this research tree */
		//FSlateBrush mResearchTreeIcon;

	//	TArray< TSoftClassPtr< UObject > > 

	UFUNCTION(BlueprintPure, Category = "Editor|Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClass_(TArray<UClass*> In);

	UFUNCTION(BlueprintPure, Category = "Editor|Recipe")
		static TArray<UClass*> GetClassFromSoftPtr(TArray<TSoftClassPtr<UObject>> In);


	static TArray< TSubclassOf< UObject > >  GetClassFromSoftPtr2(TArray< TSoftClassPtr< UObject > >  In);


	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * selfref, TArray< TSubclassOf< class UFGSchematic > > schematics, bool requireAllSchematicsToBePurchased);

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void GetSchematicDependencies(TSubclassOf< UFGSchematic > inClass, UPARAM(ref) TArray<  UFGAvailabilityDependency* >& out_schematicDependencies);
};