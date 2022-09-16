


#include "AssetTools/DescriptorFunctionLib.h"
#include "Kismet/KismetMathLibrary.h"


void UDescriptorFunctionLib::SetUseName(TSubclassOf<UFGItemDescriptor> item, bool UseName)
{
	item.GetDefaultObject()->mUseDisplayNameAndDescription = UseName;
	item->MarkPackageDirty();
}


void UDescriptorFunctionLib::SetName(TSubclassOf<UFGItemDescriptor> item, FText Name)
{
	item.GetDefaultObject()->mDisplayName = Name;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetDescription(TSubclassOf<UFGItemDescriptor> item, FText Name)
{
	item.GetDefaultObject()->mDescription = Name;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetMesh(TSubclassOf<UFGItemDescriptor> item, UStaticMesh* Mesh)
{
	item.GetDefaultObject()->mConveyorMesh = Mesh;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetMaterial(TSubclassOf<UFGItemDescriptor> item, UMaterialInterface * Mat)
{
#if WITH_EDITOR
	item.GetDefaultObject()->mConveyorMesh->SetMaterial(0, Mat); item->MarkPackageDirty();
#else
	return;
#endif
}

void UDescriptorFunctionLib::SetBigIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D* Icon)
{
	item.GetDefaultObject()->mPersistentBigIcon = Icon;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetSmallIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D* Icon)
{
	item.GetDefaultObject()->mSmallIcon = Icon;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetFluidColor(TSubclassOf<UFGItemDescriptor> item, FColor Value)
{
	item.GetDefaultObject()->mFluidColor = Value;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetForm(TSubclassOf<UFGItemDescriptor> item, EResourceForm Value)
{
	item.GetDefaultObject()->mForm = Value;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetCategory(TSubclassOf<UFGItemDescriptor> item, TSubclassOf<UFGItemCategory> Value)
{
	item.GetDefaultObject()->mCategory = Value;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetCanbeDisgarded(TSubclassOf<UFGItemDescriptor> item, bool Value)
{
	item.GetDefaultObject()->mCanBeDiscarded = Value;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetRememberPickUp(TSubclassOf<UFGItemDescriptor> item, bool Value)
{
	item.GetDefaultObject()->mRememberPickUp = Value;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetEnergyValue(TSubclassOf<UFGItemDescriptor> item, float Value)
{
	item.GetDefaultObject()->mEnergyValue = Value;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetRadioactiveDecay(TSubclassOf<UFGItemDescriptor> item, float Value)
{
	item.GetDefaultObject()->mRadioactiveDecay = Value;
	item->MarkPackageDirty();
}

void UDescriptorFunctionLib::SetStackSize(TSubclassOf<UFGItemDescriptor> item, EStackSize Value)
{
	item.GetDefaultObject()->mStackSize = Value;
	item->MarkPackageDirty();
}

EStackSize UDescriptorFunctionLib::GetStackSize(TSubclassOf<UFGItemDescriptor> item)
{
	return item.GetDefaultObject()->mStackSize;
}

