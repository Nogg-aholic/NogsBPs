


#include "AssetTools/RecipeFunctionLib.h"
#include "Kismet/KismetMathLibrary.h"


void URecipeFunctionLib::SetRecipeName(TSubclassOf<UFGRecipe> recipe, FText Name)
{
	recipe.GetDefaultObject()->mDisplayName = Name;
	recipe->MarkPackageDirty();
}

void URecipeFunctionLib::SetIngredient(TSubclassOf<UFGRecipe> recipe, TArray<FItemAmount> ingredient)
{
	recipe.GetDefaultObject()->mIngredients = ingredient;
	recipe->MarkPackageDirty();
}

void URecipeFunctionLib::SetProduct(TSubclassOf<UFGRecipe> recipe, TArray<FItemAmount> product)
{
	recipe.GetDefaultObject()->mProduct = product;
	recipe->MarkPackageDirty();
}

void URecipeFunctionLib::SetManufactoringDuration(TSubclassOf<UFGRecipe> recipe, float sec)
{
	recipe.GetDefaultObject()->mManufactoringDuration = sec;
	recipe->MarkPackageDirty();
}

void URecipeFunctionLib::SetManualManufacturingMultiplier(TSubclassOf<UFGRecipe> recipe, float val)
{
	recipe.GetDefaultObject()->mManualManufacturingMultiplier = val;
	recipe->MarkPackageDirty();
}

void URecipeFunctionLib::SetProducedIn(TSubclassOf<UFGRecipe> recipe, TArray<TSoftClassPtr<>> mProducedIn)
{
	recipe.GetDefaultObject()->mProducedIn = mProducedIn;
	recipe->MarkPackageDirty();
}
