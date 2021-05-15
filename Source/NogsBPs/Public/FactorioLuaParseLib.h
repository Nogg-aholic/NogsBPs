

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "Serialization/JsonSerializer.h" 
#include "BPJsonObjectValue.h"
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
	static TArray<FString> ParseRecipeList(FString List)
	{
		TArray<FString> Out;
		FString in = "},\"";
		
		Out = UKismetStringLibrary::ParseIntoArray(List, in);
		FString tmp = FString::Join(Out, *FString("}\n______________________________\n\""));
		in = "\n______________________________";
		Out = UKismetStringLibrary::ParseIntoArray(tmp, in);
		TArray<FString> res;

		for (auto i : Out)
		{
			FString left;
			FString right;
			if (i.Split("{", &left, &right))
			{
				left = "{";
				left.Append(right);
				if (!UKismetStringLibrary::EndsWith(left, "}"))
				{
					left.Append("}");
				}
				res.Add(left);
			}
			else
			{
				left = "{";
				left.Append(i);
				if (!UKismetStringLibrary::EndsWith(left, "}"))
				{
					left.Append("}");
				}
				res.Add(left);
			}

		}
		return res;
	}
	UFUNCTION(BlueprintCallable)
	static  TArray<UBPJsonObject * > GetObject(TArray<FString> In, UObject * Outer) {
		
		TArray<UBPJsonObject *> arr;
		if (!Outer)
			return arr;
		for (auto i : In)
		{
			TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(i);
			FJsonSerializer Serializer;
			TSharedPtr<FJsonObject> result;
			Serializer.Deserialize(reader, result);

			UBPJsonObject * Obj = NewObject<UBPJsonObject>(Outer);
			if (!Obj)
				continue;
			else
			{
				Obj->InnerObj = result;
				arr.Add(Obj);
			}
		}
		return arr;
	}

	UFUNCTION(BlueprintCallable)
	static void ParseRecipe(UBPJsonObject * Obj, FString & Name, FString & Category, TArray< UBPJsonObjectValue *> & Ingredients, TArray< UBPJsonObjectValue *> & Products, float & Energy)
	{
		
		if (!Obj)
			return;
		if (!Obj->InnerObj)
			return;

		if(Obj->Values.Contains("name"))
			Name = (*Obj->Values.Find("name"))->AsString();
		if (Obj->Values.Contains("category"))
			Category = (*Obj->Values.Find("category"))->AsString();
		if (Obj->Values.Contains("ingredients"))
			Ingredients = (*Obj->Values.Find("ingredients"))->AsArray();
		if (Obj->Values.Contains("products"))
			Products = (*Obj->Values.Find("products"))->AsArray();
		if (Obj->Values.Contains("energy"))
			Energy = (*Obj->Values.Find("energy"))->AsNumber();
	
	};

	UFUNCTION(BlueprintCallable)
	static void ParseItemCost(UBPJsonObject * Obj, FString & Type, FString & Name, int32 & Amount, float & Probability )
	{
		if (!Obj)
			return;
		if (!Obj->InnerObj)
			return;

		Name = Obj->GetJsonStringField("name");
		Type = Obj->GetJsonStringField("type");
		Amount = Obj->GetJsonNumberField("amount");
		Probability = Obj->GetJsonNumberField("probabilty");
	};
};
