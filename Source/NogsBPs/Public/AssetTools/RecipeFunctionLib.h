

#pragma once

#include "CoreMinimal.h"
#include "FGRecipe.h"

#include "Kismet/BlueprintFunctionLibrary.h"

#include "RecipeFunctionLib.generated.h"


USTRUCT(Blueprintable)
struct NOGSBPS_API FRecipeStruct
{
	GENERATED_BODY()

	FRecipeStruct();
	FRecipeStruct(TSubclassOf<class UFGRecipe> inClass);

	bool operator==(FRecipeStruct inClass) {

		if (inClass.Name != Name)
		{
			return false;
		}
		if (inClass.Class != Class)
		{
			return false;
		}
		if (inClass.ManufactoringDuration != ManufactoringDuration)
		{
			return false;
		}
		if (inClass.ManualManufacturingMultiplier != ManualManufacturingMultiplier)
		{
			return false;
		}
		if (inClass.mProducedIn != mProducedIn)
		{
			return false;
		}
		if (CompareProducts(inClass.Ingredients))
		{
			return false;
		}
		if (CompareProducts(inClass.Products))
		{
			return false;
		}
		
		return true;
	}

	bool operator==(TSubclassOf<class UFGRecipe> inClass) {
		return *this == FRecipeStruct(inClass);
	}

	bool CompareProducts(TArray< FItemAmount > ProductsIn)
	{
		for (int32 i = 0; i < Products.Num(); i++)
		{
			if (!ProductsIn.IsValidIndex(i))
				return false;

			if (ProductsIn[i].Amount != Products[i].Amount || ProductsIn[i].ItemClass != Products[i].ItemClass)
				return false;
		}
		return true;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGRecipe> Class;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< FItemAmount > Ingredients;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< FItemAmount > Products;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ManufactoringDuration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float ManualManufacturingMultiplier;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TArray< TSoftClassPtr< UObject > > mProducedIn;

};
/**
 * 
 */
UCLASS()
class NOGSBPS_API URecipeFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetRecipeName(TSubclassOf<UFGRecipe> recipe, FText Name) { recipe.GetDefaultObject()->mDisplayName = Name; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetIngredient(TSubclassOf<UFGRecipe> recipe, TArray<FItemAmount> ingredient) { recipe.GetDefaultObject()->mIngredients = ingredient; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetProduct(TSubclassOf< UFGRecipe > recipe, TArray< FItemAmount > product) { recipe.GetDefaultObject()->mProduct = product; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetManufactoringDuration(TSubclassOf<UFGRecipe> recipe, float sec) { recipe.GetDefaultObject()->mManufactoringDuration = sec; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetManualManufacturingMultiplier(TSubclassOf<UFGRecipe> recipe, float val) { recipe.GetDefaultObject()->mManualManufacturingMultiplier = val; recipe->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetProducedIn(TSubclassOf<UFGRecipe> recipe, TArray< TSoftClassPtr< UObject > > mProducedIn) { recipe.GetDefaultObject()->mProducedIn = mProducedIn; recipe->MarkPackageDirty(); };
	
	
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClassFromObjects(TArray<UObject*> In);

	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static TArray<TSoftClassPtr<UObject>> GetSoftClass(TArray<UClass*> In);

	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static TArray<UClass*> GetClassFromSoftPtr(TArray<TSoftClassPtr<UObject>> In);


	UFUNCTION(BlueprintPure, Category = "Editor| Recipe")
		static FRecipeStruct GetStructFromRecipe(TSubclassOf<UFGRecipe> inClass) { return FRecipeStruct(inClass); }

	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
		static void SetRecipeFromStruct(TSubclassOf<UFGRecipe> inClass, FRecipeStruct Struct);

	/** Returns true if FRecipeStruct A is equal to FRecipeStruct B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (RecipeStruct)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FRecipeStructFRecipeStruct(FRecipeStruct A, FRecipeStruct B);
	/** Returns true if FRecipeStruct A is equal to the generated FRecipeStruct from a UFGSchematic B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UFGSchematic)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Schematics")
		static bool EqualEqual_FRecipeStructUFGRecipe(FRecipeStruct A, TSubclassOf<class UFGRecipe> B);
	
};
