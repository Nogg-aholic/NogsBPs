

#include "AssetTools/SchematicFunctionLib.h"
#include "Kismet/KismetMathLibrary.h"


void USchematicFunctionLib::SetDisplayName(TSubclassOf<UFGSchematic> inClass, FText Name)
{
	inClass.GetDefaultObject()->mDisplayName = Name;
	inClass->MarkPackageDirty();
}


void USchematicFunctionLib::SetDescription(TSubclassOf<UFGSchematic> inClass, FText Description)
{
	inClass.GetDefaultObject()->mDescription = Description;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetType(TSubclassOf<UFGSchematic> inClass, ESchematicType Type)
{
	inClass.GetDefaultObject()->mType = Type;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetTechTier(TSubclassOf<UFGSchematic> inClass, int32 Tier)
{
	inClass.GetDefaultObject()->mTechTier = Tier;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetSchematicCategory(TSubclassOf<UFGSchematic> inClass, TSubclassOf<UFGSchematicCategory> Cat)
{
	inClass.GetDefaultObject()->mSchematicCategory = Cat;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetSubCategories(TSubclassOf<UFGSchematic> inClass,
                                             TArray<TSubclassOf<UFGSchematicCategory>> Cat)
{
	inClass.GetDefaultObject()->mSubCategories = Cat;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetCost(TSubclassOf<UFGSchematic> inClass, TArray<FItemAmount> Cost)
{
	inClass.GetDefaultObject()->mCost = Cost;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetTimeToComplete(TSubclassOf<UFGSchematic> inClass, float sec)
{
	inClass.GetDefaultObject()->mTimeToComplete = sec;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetUnlocks(TSubclassOf<UFGSchematic> inClass, TArray<UFGUnlock*> Unlocks)
{
	inClass.GetDefaultObject()->mUnlocks = Unlocks;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetSchematicIcon(TSubclassOf<UFGSchematic> inClass, FSlateBrush Icon)
{
	inClass.GetDefaultObject()->mSchematicIcon = Icon;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::SetDependsOnSchematic(TSubclassOf<UFGSchematic> inClass,
                                                  TArray<UFGAvailabilityDependency*> Deps)
{
	inClass.GetDefaultObject()->mSchematicDependencies = Deps;
	inClass->MarkPackageDirty();
}

void USchematicFunctionLib::InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * Object, TArray<TSubclassOf<class UFGSchematic>> Schematics, bool bRequireAllSchematicsToBePurchased)
{
#if WITH_EDITOR	
	Object->Init(Schematics, bRequireAllSchematicsToBePurchased);
#else
	return;
#endif
}

void USchematicFunctionLib::GetSchematicDependencies(TSubclassOf<UFGSchematic> inClass, UPARAM(ref)TArray<UFGAvailabilityDependency*>& out_schematicDependencies)
{
	if (inClass)
		out_schematicDependencies = inClass.GetDefaultObject()->mSchematicDependencies;
	return;
}
