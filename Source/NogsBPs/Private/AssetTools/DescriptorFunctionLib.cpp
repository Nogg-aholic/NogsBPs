


#include "AssetTools/DescriptorFunctionLib.h"
#include "Kismet/KismetMathLibrary.h"

FItemDescriptorStruct::FItemDescriptorStruct()
{
	Class = nullptr;
	Name = "";
	Form = EResourceForm::RF_INVALID;
	StackSize = EStackSize::SS_ONE;
	RememberPickUp = false;
	CanBeDiscarded = true;
	EnergyValue = 0.f;
	RadioactiveDecay = 0.f;
	FluidColor = FColor();
	ConveyorMesh = nullptr;
	Category = nullptr;
	IconSmall = nullptr;
	IconBig = nullptr;
}

FItemDescriptorStruct::FItemDescriptorStruct(TSubclassOf<class UFGItemDescriptor> inClass)
{
	if (!inClass)
	{
		Class = nullptr;
		Name = "";
		Form = EResourceForm::RF_INVALID;
		StackSize = EStackSize::SS_ONE;
		RememberPickUp = false;
		CanBeDiscarded = true;
		EnergyValue = 0.f;
		RadioactiveDecay = 0.f;
		FluidColor = FColor();
		ConveyorMesh = nullptr;
		Category = nullptr;
		IconSmall = nullptr;
		IconBig = nullptr;
		return;
	}
		

	Class = inClass;
	Name = inClass.GetDefaultObject()->mDisplayName.ToString();
	Form = inClass.GetDefaultObject()->mForm;
	StackSize = inClass.GetDefaultObject()->mStackSize;
	RememberPickUp = inClass.GetDefaultObject()->mRememberPickUp;
	CanBeDiscarded = inClass.GetDefaultObject()->mCanBeDiscarded;
	EnergyValue = inClass.GetDefaultObject()->mEnergyValue;
	RadioactiveDecay = inClass.GetDefaultObject()->mRadioactiveDecay;
	FluidColor = inClass.GetDefaultObject()->mFluidColor;
	Category = inClass.GetDefaultObject()->mItemCategory;
	IconSmall = inClass.GetDefaultObject()->mSmallIcon;
	ConveyorMesh = inClass.GetDefaultObject()->mConveyorMesh;
}

void UDescriptorFunctionLib::SetMaterial(TSubclassOf<UFGItemDescriptor> item, UMaterialInterface * Mat)
{
#if WITH_EDITOR
	item.GetDefaultObject()->mConveyorMesh->SetMaterial(0, Mat); item->MarkPackageDirty();
#else
	return;
#endif
}
void UDescriptorFunctionLib::SetDescriptorFromStruct(TSubclassOf<UFGItemDescriptor> inClass, FItemDescriptorStruct Struct)
{
	if (!inClass)
		return;
	if (FItemDescriptorStruct() == Struct)
		return;
	if (Struct == inClass)
		return;

	inClass.GetDefaultObject()->mDisplayName = FText::FromString(Struct.Name);
	inClass.GetDefaultObject()->mForm = Struct.Form;
	inClass.GetDefaultObject()->mStackSize = Struct.StackSize;
	inClass.GetDefaultObject()->mRememberPickUp = Struct.RememberPickUp;
	inClass.GetDefaultObject()->mCanBeDiscarded = Struct.CanBeDiscarded;
	inClass.GetDefaultObject()->mEnergyValue = Struct.EnergyValue;
	inClass.GetDefaultObject()->mRadioactiveDecay = Struct.RadioactiveDecay;
	inClass.GetDefaultObject()->mFluidColor = Struct.FluidColor;
	inClass.GetDefaultObject()->mItemCategory = Struct.Category;
	inClass.GetDefaultObject()->mSmallIcon = Struct.IconSmall;
	inClass.GetDefaultObject()->mPersistentBigIcon = Struct.IconBig;
	inClass.GetDefaultObject()->mConveyorMesh = Struct.ConveyorMesh;

	inClass->MarkPackageDirty();
	
}

KISMET_MATH_FORCEINLINE
bool UDescriptorFunctionLib::EqualEqual_FDescriptorStructFDescriptorStruct(FItemDescriptorStruct A, FItemDescriptorStruct B)
{
	return A == B;
}

KISMET_MATH_FORCEINLINE
bool UDescriptorFunctionLib::EqualEqual_FDescriptorStructUFGItemDescriptor(FItemDescriptorStruct A, TSubclassOf<class UFGItemDescriptor> B)
{
	return A == B;
}
