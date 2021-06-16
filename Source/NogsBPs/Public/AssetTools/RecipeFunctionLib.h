#pragma once

#include "CoreMinimal.h"
#include "FGRecipe.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RecipeFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class NOGSBPS_API URecipeFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public: 

	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
	static void SetRecipeName(TSubclassOf<UFGRecipe> recipe, FText Name);
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
	static void SetIngredient(TSubclassOf<UFGRecipe> recipe, TArray<FItemAmount> ingredient);
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
	static void SetProduct(TSubclassOf<UFGRecipe> recipe, TArray<FItemAmount> product);
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
	static void SetManufactoringDuration(TSubclassOf<UFGRecipe> recipe, float sec);
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
	static void SetManualManufacturingMultiplier(TSubclassOf<UFGRecipe> recipe, float val);
	UFUNCTION(BlueprintCallable, Category = "Editor| Recipe")
	static void SetProducedIn(TSubclassOf<UFGRecipe> recipe, TArray<TSoftClassPtr<UObject>> mProducedIn);
};
