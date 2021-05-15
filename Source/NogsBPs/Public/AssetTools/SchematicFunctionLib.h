

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


USTRUCT(Blueprintable)
struct NOGSBPS_API FnSchematicStruct
{
	GENERATED_BODY()

	FnSchematicStruct();
	FnSchematicStruct(TSubclassOf<class UFGSchematic> inClass);

	bool operator==(FnSchematicStruct inClass) {
		if (inClass.Class != Class)
		{
			return false;
		}
		if (inClass.mDisplayName != mDisplayName)
		{
			return false;
		}
		if (inClass.mType != mType)
		{
			return false;
		}
		if (inClass.mTechTier != mTechTier)
		{
			return false;
		}
		if (inClass.mSchematicCategory != mSchematicCategory)
		{
			return false;
		}
		if (inClass.mSubCategories != mSubCategories)
		{
			return false;
		}	
		if (inClass.mTimeToComplete != mTimeToComplete)
		{
			return false;
		}
		if (inClass.mSchematicIcon != mSchematicIcon)
		{
			return false;
		}
		if (CompareCost(inClass.mCost))
		{
			return false;
		}
		if (inClass.mUnlocks != mUnlocks)
		{
			for (int32 i = 0; i < inClass.mUnlocks.Num(); i++)
			{
				if (!inClass.mUnlocks.IsValidIndex(i) || !mUnlocks.IsValidIndex(i))
					return false;

				//UFGUnlockArmEquipmentSlot
				{
					UFGUnlockArmEquipmentSlot * A = Cast< UFGUnlockArmEquipmentSlot>(mUnlocks[i]);
					UFGUnlockArmEquipmentSlot * B = Cast< UFGUnlockArmEquipmentSlot>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						int32 A_ = A->GetNumArmEquipmentSlotsToUnlock();
						int32 B_ = B->GetNumArmEquipmentSlotsToUnlock();
						if (A_ != B_)
							return false;
					}
					
				}
				//UFGUnlockInventorySlot
				{
					UFGUnlockInventorySlot * A = Cast< UFGUnlockInventorySlot>(mUnlocks[i]);
					UFGUnlockInventorySlot * B = Cast< UFGUnlockInventorySlot>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						int32 A_ = A->GetNumInventorySlotsToUnlock();
						int32 B_ = B->GetNumInventorySlotsToUnlock();
						if (A_ != B_)
							return false;
					}

				}
				//UFGUnlockBuildEfficiency
				{
					UFGUnlockBuildEfficiency * A = Cast< UFGUnlockBuildEfficiency>(mUnlocks[i]);
					UFGUnlockBuildEfficiency * B = Cast< UFGUnlockBuildEfficiency>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
				}
				//UFGUnlockBuildOverclock
				{
					UFGUnlockBuildOverclock * A = Cast< UFGUnlockBuildOverclock>(mUnlocks[i]);
					UFGUnlockBuildOverclock * B = Cast< UFGUnlockBuildOverclock>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
				}
				//UFGUnlockMap
				{
					UFGUnlockMap * A = Cast< UFGUnlockMap>(mUnlocks[i]);
					UFGUnlockMap * B = Cast< UFGUnlockMap>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
				}

				//UFGUnlockGiveItem
				{
					UFGUnlockGiveItem * A = Cast< UFGUnlockGiveItem>(mUnlocks[i]);
					UFGUnlockGiveItem * B = Cast< UFGUnlockGiveItem>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;

					if (A && B)
					{
						TArray< FItemAmount > A_ = A->GetItemsToGive();
						TArray< FItemAmount > B_ = B->GetItemsToGive();
						if (A_.Num() != B_.Num())
							return false;
						for (int32 j = 0; j < A_.Num(); j++)
						{
							if (!B_.IsValidIndex(j))
								return false;

							if (B_[j].Amount != mCost[j].Amount || B_[j].ItemClass != mCost[j].ItemClass)
								return false;
						}
					}
				}
				//UFGUnlockRecipe
				{
					UFGUnlockRecipe * A = Cast< UFGUnlockRecipe>(mUnlocks[i]);
					UFGUnlockRecipe * B = Cast< UFGUnlockRecipe>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray< TSubclassOf< class UFGRecipe > > A_ = A->GetRecipesToUnlock();
						TArray< TSubclassOf< class UFGRecipe > > B_ = B->GetRecipesToUnlock();
						if (A_ != B_)
							return false;
					}
				}
				//UFGUnlockScannableResource
				{
					UFGUnlockScannableResource * A = Cast< UFGUnlockScannableResource>(mUnlocks[i]);
					UFGUnlockScannableResource * B = Cast< UFGUnlockScannableResource>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray< FScannableResourcePair > A_ = A->GetResourcesToAddToScanner();
						TArray< FScannableResourcePair > B_ = B->GetResourcesToAddToScanner();
						if (A != B)
							return false;
					}

				}
				//UFGUnlockSchematic
				{
					UFGUnlockSchematic * A = Cast< UFGUnlockSchematic>(mUnlocks[i]);
					UFGUnlockSchematic * B = Cast< UFGUnlockSchematic>(inClass.mUnlocks[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray < TSubclassOf< class UFGSchematic > > A_ = A->GetSchematicsToUnlock();
						TArray < TSubclassOf< class UFGSchematic > > B_ = B->GetSchematicsToUnlock();
						if (A != B)
							return false;
					}

				}

			}
		}
		if (inClass.mSchematicDependencies != mSchematicDependencies)
		{
			for (int32 i = 0; i < inClass.mSchematicDependencies.Num(); i++)
			{
				//UFGItemPickedUpDependency
				{
					UFGItemPickedUpDependency * A = Cast< UFGItemPickedUpDependency>(inClass.mSchematicDependencies[i]);
					UFGItemPickedUpDependency * B = Cast< UFGItemPickedUpDependency>(inClass.mSchematicDependencies[i]);
					if (A && !B || !A && B)
						return false;
					else if (A && B)
					{
						TArray< TSubclassOf< class UFGItemDescriptor > > A_; A->GetItems(A_);
						TArray< TSubclassOf< class UFGItemDescriptor > > B_; B->GetItems(B_);
						if (A_ != B_)
							return false;
					}			
				}
				//UFGSchematicPurchasedDependency
				{
					UFGSchematicPurchasedDependency * A = Cast< UFGSchematicPurchasedDependency>(inClass.mSchematicDependencies[i]);
					UFGSchematicPurchasedDependency * B = Cast< UFGSchematicPurchasedDependency>(inClass.mSchematicDependencies[i]);

					if (A && !B || !A && B)
						return false;

					if (A && B)
					{
						TArray< TSubclassOf< class UFGSchematic > > A_; A->GetSchematics(A_);
						TArray< TSubclassOf< class UFGSchematic > > B_; B->GetSchematics(B_);
						if (A_ != B_)
							return false;
					}
			
				}
				//UFGRecipeUnlockedDependency
				{
					UFGRecipeUnlockedDependency * A = Cast< UFGRecipeUnlockedDependency>(inClass.mSchematicDependencies[i]);
					UFGRecipeUnlockedDependency * B = Cast< UFGRecipeUnlockedDependency>(inClass.mSchematicDependencies[i]);
					if (A && !B || !A && B)
						return false;
					if (A && B)
					{
						TArray< TSubclassOf< class UFGRecipe > > A_; A->GetRecipes(A_);
						TArray< TSubclassOf< class UFGRecipe > > B_; B->GetRecipes(B_);
						if (A_ != B_)
							return false;
					}
					

				}
				//UFGGamePhaseReachedDependency
				{
					UFGGamePhaseReachedDependency * A = Cast< UFGGamePhaseReachedDependency>(inClass.mSchematicDependencies[i]);
					UFGGamePhaseReachedDependency * B = Cast< UFGGamePhaseReachedDependency>(inClass.mSchematicDependencies[i]);
					if (A && !B || !A && B)
						return false;
					if (A && B)
					{
						EGamePhase A_ = A->GetGamePhase();
						EGamePhase B_ = B->GetGamePhase();
						if (A_ != B_)
							return false;
					}
				
				}
				
			}
			return false;
		}

		return true;
	}

	bool operator==(TSubclassOf<class UFGSchematic> inClass) {
		return *this == FnSchematicStruct(inClass);
	}

	bool CompareCost(TArray< FItemAmount > ProductsIn)
	{
		if (mCost.Num() != ProductsIn.Num())
			return false;
		for (int32 i = 0; i < mCost.Num(); i++)
		{
			if (!ProductsIn.IsValidIndex(i))
				return false;

			if (ProductsIn[i].Amount != mCost[i].Amount || ProductsIn[i].ItemClass != mCost[i].ItemClass)
				return false;
		}
		return true;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGSchematic> Class;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString mDisplayName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		ESchematicType mType;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		int32 mTechTier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGSchematicCategory>  mSchematicCategory;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray < TSubclassOf<class UFGSchematicCategory>> mSubCategories;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< FItemAmount > mCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float mTimeToComplete;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< class UFGUnlock* > mUnlocks;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FSlateBrush mSchematicIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< class UFGAvailabilityDependency* > mSchematicDependencies;

};


/**
 * 
 */
UCLASS()
class NOGSBPS_API USchematicFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetDisplayName(TSubclassOf< UFGSchematic > inClass, FText Name) { inClass.GetDefaultObject()->mDisplayName = Name; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetType(TSubclassOf< UFGSchematic > inClass, ESchematicType Type) { inClass.GetDefaultObject()->mType = Type; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetTechTier(TSubclassOf< UFGSchematic > inClass, int32 Tier) { inClass.GetDefaultObject()->mTechTier = Tier; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetSchemCategory(TSubclassOf< UFGSchematic > inClass, TSubclassOf<class UFGSchematicCategory> Cat) { inClass.GetDefaultObject()->mSchematicCategory = Cat; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetSubCategories(TSubclassOf< UFGSchematic > inClass, TArray < TSubclassOf<class UFGSchematicCategory>> Cat) { inClass.GetDefaultObject()->mSubCategories = Cat; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetCost(TSubclassOf< UFGSchematic > inClass, TArray<FItemAmount> Cost) { inClass.GetDefaultObject()->mCost = Cost; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetTimeToComplete(TSubclassOf< UFGSchematic > inClass, float sec) { inClass.GetDefaultObject()->mTimeToComplete = sec; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetUnlocks(TSubclassOf< UFGSchematic > inClass, TArray< class UFGUnlock* > Unlocks) { inClass.GetDefaultObject()->mUnlocks = Unlocks; inClass->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetSchematicIcon(TSubclassOf< UFGSchematic > inClass, FSlateBrush Icon) { inClass.GetDefaultObject()->mSchematicIcon = Icon; inClass->MarkPackageDirty(); }

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematic")
		static void SetDependsOnSchematic(TSubclassOf< UFGSchematic > inClass, TArray< class UFGAvailabilityDependency* > Deps) { inClass.GetDefaultObject()->mSchematicDependencies = Deps; inClass->MarkPackageDirty(); }
	
	


	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * selfref, TArray< TSubclassOf< class UFGSchematic > > schematics, bool requireAllSchematicsToBePurchased);

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void GetSchematicDependencies(TSubclassOf< UFGSchematic > inClass, UPARAM(ref) TArray<  UFGAvailabilityDependency* >& out_schematicDependencies);


	UFUNCTION(BlueprintPure, Category = "Editor| Schematics")
		static FnSchematicStruct GetStructFromSchematic(TSubclassOf<UFGSchematic> inClass) { return FnSchematicStruct(inClass); }

	UFUNCTION(BlueprintCallable, Category = "Editor| Schematics")
		static void SetSchematicFromStruct(FnSchematicStruct Struct);

	/** Returns true if FSchematicStruct A is equal to FSchematicStruct B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (SchematicStruct)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FSchematicStructFSchematicStruct(FnSchematicStruct A, FnSchematicStruct B);
	/** Returns true if FSchematicStruct A is equal to the generated FSchematicStruct from a UFGSchematic B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UFGSchematic)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FSchematicStructUFGSchematic(FnSchematicStruct A, TSubclassOf<class UFGSchematic> B);
};
