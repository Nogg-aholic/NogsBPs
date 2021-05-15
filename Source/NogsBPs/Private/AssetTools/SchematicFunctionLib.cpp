

#include "AssetTools/SchematicFunctionLib.h"
#include "Kismet/KismetMathLibrary.h"



void USchematicFunctionLib::InitSchematicPurchaseDep(UFGSchematicPurchasedDependency * selfref, TArray<TSubclassOf<class UFGSchematic>> schematics, bool requireAllSchematicsToBePurchased)
{
#if WITH_EDITOR	
	selfref->Init(schematics, requireAllSchematicsToBePurchased);
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

void USchematicFunctionLib::SetSchematicFromStruct(FnSchematicStruct Struct)
{
	if (!Struct.Class)
		return;
	if (Struct == FnSchematicStruct())
		return;
	if (Struct == Struct.Class)
		return;

	auto obj = Struct.Class.GetDefaultObject();

	obj->mDisplayName = FText::FromString(Struct.mDisplayName);
	obj->mType = Struct.mType;
	obj->mTechTier = Struct.mTechTier;
	obj->mSchematicCategory = Struct.mSchematicCategory;
	obj->mSubCategories = Struct.mSubCategories;
	obj->mTimeToComplete = Struct.mTimeToComplete;
	obj->mSchematicIcon = Struct.mSchematicIcon;
	obj->mCost = Struct.mCost;
	obj->mUnlocks = Struct.mUnlocks;
	obj->mSchematicDependencies = Struct.mSchematicDependencies;

	Struct.Class->MarkPackageDirty();
}

KISMET_MATH_FORCEINLINE
bool USchematicFunctionLib::EqualEqual_FSchematicStructFSchematicStruct(FnSchematicStruct A, FnSchematicStruct B)
{
	return A == B;
}

KISMET_MATH_FORCEINLINE
bool USchematicFunctionLib::EqualEqual_FSchematicStructUFGSchematic(FnSchematicStruct A, TSubclassOf<class UFGSchematic> B)
{
	return A == B;
}

FnSchematicStruct::FnSchematicStruct()
{
	Class = nullptr;
	mDisplayName = "";
	mType = ESchematicType::EST_Custom;
	mTechTier = 0;
	mSchematicCategory = nullptr;
	mSubCategories = {};
	mTimeToComplete = 180.f;
	mSchematicIcon = FSlateBrush();
	mCost = {};
	mUnlocks = {};
	mSchematicDependencies = {};
}

FnSchematicStruct::FnSchematicStruct(TSubclassOf<class UFGSchematic> inClass)
{
	if (!inClass)
	{
		Class = nullptr; 
		mDisplayName = "";
		mType = ESchematicType::EST_Custom;
		mTechTier = 0;
		mSchematicCategory = nullptr;
		mSubCategories = {};
		mTimeToComplete = 180.f;
		mSchematicIcon = FSlateBrush();
		mCost = {};
		mUnlocks = {};
		mSchematicDependencies = {};
	}

	Class = inClass;
	mDisplayName = inClass.GetDefaultObject()->mDisplayName.ToString();
	mType = inClass.GetDefaultObject()->mType;
	mTechTier = inClass.GetDefaultObject()->mTechTier;
	mSchematicCategory = inClass.GetDefaultObject()->mSchematicCategory;
	mSubCategories = inClass.GetDefaultObject()->mSubCategories;
	mTimeToComplete = inClass.GetDefaultObject()->mTimeToComplete;
	mSchematicIcon = inClass.GetDefaultObject()->mSchematicIcon;
	mCost = inClass.GetDefaultObject()->mCost;
	mUnlocks = inClass.GetDefaultObject()->mUnlocks;
	mSchematicDependencies = inClass.GetDefaultObject()->mSchematicDependencies;

}
