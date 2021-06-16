

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Serialization/JsonSerializer.h" 
#include "BPJsonObject.h"
#include "BPJsonObject.h"
#include "Serialization/JsonReader.h" 
#include "FactorioLuaParseLib.generated.h"

/**
 * 
 */
UCLASS()
class NOGSBPS_API UFactorioLuaParseLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static TArray<FString> ParseRecipeList(FString List);
	UFUNCTION(BlueprintCallable)
	static TArray<FBPJsonObject> GetObject(TArray<FString> In, UObject* Outer);

	UFUNCTION(BlueprintCallable)
	static void ParseRecipe(FBPJsonObject& Obj, FString& Name, FString& Category, TArray<FBPJsonObject>& Ingredients,
	                        TArray<FBPJsonObject>& Products, float& Energy);

	UFUNCTION(BlueprintCallable)
	static void ParseItemCost(FBPJsonObject& Obj, FString& Type, FString& Name, int32& Amount, float& Probability);
};
