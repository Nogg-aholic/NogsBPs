


#include "AssetTools/RecipeFunctionLib.h"
#include "Kismet/KismetMathLibrary.h"

FRecipeStruct::FRecipeStruct()
{
	Class = nullptr;
	Name = "";
	Ingredients = {};
	Products = {};
	ManufactoringDuration = 0.f;
	ManualManufacturingMultiplier = 0.f;
	mProducedIn = {};
}

FRecipeStruct::FRecipeStruct(TSubclassOf<class UFGRecipe> inClass)
{
	if (!inClass)
		return;
	Class = inClass;
	Name = inClass.GetDefaultObject()->mDisplayName.ToString();
	Ingredients = inClass.GetDefaultObject()->mIngredients;
	Products = inClass.GetDefaultObject()->mProduct;
	ManufactoringDuration = inClass.GetDefaultObject()->mManufactoringDuration;
	ManualManufacturingMultiplier = inClass.GetDefaultObject()->mManualManufacturingMultiplier;
	mProducedIn = inClass.GetDefaultObject()->mProducedIn;
}

TArray<TSoftClassPtr<UObject>> URecipeFunctionLib::GetSoftClassFromObjects(TArray<UObject*>  In)
{
	TArray< TSoftClassPtr< UObject > > out;
	if (In.Num() > 0)
	{
		for (int j = 0; j < In.Num(); j++)
		{
			if (In[j]->IsValidLowLevel())
			{
				TSoftClassPtr< UObject >obj(In[j]->GetClass());
				out.Add(obj);
			}
		}
		return out;
	}
	else
		return TArray< TSoftClassPtr< UObject > >();
}

TArray<TSoftClassPtr<UObject>> URecipeFunctionLib::GetSoftClass(TArray<UClass*>  In)
{
	TArray< TSoftClassPtr< UObject > > out;
	if (In.Num() > 0)
	{
		for (int j = 0; j < In.Num(); j++)
		{
			if (In[j]->IsValidLowLevel())
			{
				TSoftClassPtr< UObject >obj(In[j]);
				out.Add(obj);
			}
		}
		return out;
	}
	else
		return TArray< TSoftClassPtr< UObject > >();

}

TArray<UClass*> URecipeFunctionLib::GetClassFromSoftPtr(TArray<TSoftClassPtr<UObject>>   In)
{
	TArray<UClass*>  out;
	if (In.Num() > 0)
	{
		for (int j = 0; j < In.Num(); j++)
		{
			if (In[j]->IsValidLowLevel())
			{
				UClass* obj = In[j].Get();
				out.Add(obj);
			}
		}
		return out;
	}
	else
		return TArray<UClass*>();
}

void URecipeFunctionLib::SetRecipeFromStruct(TSubclassOf<UFGRecipe> inClass, FRecipeStruct Struct)
{
	if (!inClass)
		return;
	if (Struct == FRecipeStruct())
		return;
	if (Struct == inClass)
		return;
	
	inClass.GetDefaultObject()->mDisplayName = FText::FromString(Struct.Name);
	inClass.GetDefaultObject()->mIngredients = Struct.Ingredients;
	inClass.GetDefaultObject()->mProduct = Struct.Products;
	inClass.GetDefaultObject()->mManufactoringDuration = Struct.ManufactoringDuration;	
	inClass.GetDefaultObject()->mManualManufacturingMultiplier = Struct.ManualManufacturingMultiplier;	
	inClass.GetDefaultObject()->mProducedIn = Struct.mProducedIn;	
	inClass->MarkPackageDirty();
	
}

KISMET_MATH_FORCEINLINE
bool URecipeFunctionLib::EqualEqual_FRecipeStructFRecipeStruct(FRecipeStruct A, FRecipeStruct B)
{
	return A == B;
}

KISMET_MATH_FORCEINLINE
bool URecipeFunctionLib::EqualEqual_FRecipeStructUFGRecipe(FRecipeStruct A, TSubclassOf<class UFGRecipe> B)
{
	return A == B;
}

