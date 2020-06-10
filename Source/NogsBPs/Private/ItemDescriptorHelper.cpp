// ILikeBanas


#include "ItemDescriptorHelper.h"

TArray<TSoftClassPtr<UObject>> UItemDescriptorHelper::GetSoftClass(TArray<UObject*>  In)
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

TArray<TSoftClassPtr<UObject>> UItemDescriptorHelper::GetSoftClass_(TArray<UClass*>  In)
{
	TArray< TSoftClassPtr< UObject > > out;
	if(In.Num() > 0 )
	{
		for (int j = 0; j < In.Num(); j++)
		{
			if(In[j]->IsValidLowLevel())
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

TArray<UClass*> UItemDescriptorHelper::GetClassFromSoftPtr(TArray<TSoftClassPtr<UObject>>   In)
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

TArray<TSubclassOf<UObject>> UItemDescriptorHelper::GetClassFromSoftPtr2(TArray<TSoftClassPtr<UObject>> In)
{
	TArray<TSubclassOf<UObject>>   out;

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
		return TArray<TSubclassOf<UObject>>();
}

void UItemDescriptorHelper::InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * selfref, TArray<TSubclassOf<class UFGSchematic>> schematics, bool requireAllSchematicsToBePurchased)
{
	selfref->Init(schematics, requireAllSchematicsToBePurchased);
}

void UItemDescriptorHelper::GetSchematicDependencies(TSubclassOf<UFGSchematic> inClass, UPARAM(ref)TArray<UFGAvailabilityDependency*>& out_schematicDependencies)
{
	if (inClass)
		out_schematicDependencies = inClass.GetDefaultObject()->mSchematicDependencies;
	return;
}



