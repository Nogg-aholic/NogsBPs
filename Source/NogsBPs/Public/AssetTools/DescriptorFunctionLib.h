

#pragma once

#include "CoreMinimal.h"
#include "Resources/FGItemDescriptor.h"
#include "FGItemCategory.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DescriptorFunctionLib.generated.h"


USTRUCT(Blueprintable)
struct NOGSBPS_API FItemDescriptorStruct
{
	GENERATED_BODY()

	FItemDescriptorStruct();
	FItemDescriptorStruct(TSubclassOf<class UFGItemDescriptor> inClass);

	bool operator==(TSubclassOf<class UFGItemDescriptor> inClass) {

		if (inClass.GetDefaultObject()->mDisplayName.ToString() != Name)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mForm != Form)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mStackSize != StackSize)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mRememberPickUp != RememberPickUp)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mCanBeDiscarded != CanBeDiscarded)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mEnergyValue != EnergyValue)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mRadioactiveDecay != RadioactiveDecay)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mFluidColor != FluidColor)
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mItemCategory != Category)
		{
			return false;
		}

		if (inClass.GetDefaultObject()->mSmallIcon != IconSmall )
		{
			return false;
		}
		if (inClass.GetDefaultObject()->mPersistentBigIcon != IconBig)
		{
			return false;
		}

		return true;
	}
	bool operator==(FItemDescriptorStruct inClass) {

		if (inClass.Name != Name)
		{
			return false;
		}
		if (inClass.Form != Form)
		{
			return false;
		}
		if (inClass.StackSize != StackSize)
		{
			return false;
		}
		if (inClass.RememberPickUp != RememberPickUp)
		{
			return false;
		}
		if (inClass.CanBeDiscarded != CanBeDiscarded)
		{
			return false;
		}
		if (inClass.EnergyValue != EnergyValue)
		{
			return false;
		}
		if (inClass.RadioactiveDecay != RadioactiveDecay)
		{
			return false;
		}
		if (inClass.FluidColor != FluidColor)
		{
			return false;
		}
		if (inClass.Category != Category)
		{
			return false;
		}

		if (inClass.IconSmall != IconSmall)
		{
			return false;
		}
		if (inClass.IconBig != IconBig)
		{
			return false;
		}

		return true;
	}

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FString Name;
		
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EResourceForm Form;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		EStackSize StackSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool RememberPickUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		bool CanBeDiscarded;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float EnergyValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		float RadioactiveDecay;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		FColor FluidColor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGItemDescriptor> Class;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<class UFGItemCategory> Category;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UStaticMesh * ConveyorMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTexture2D * IconSmall;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		UTexture2D * IconBig;

};




/**
 * 
 */
UCLASS()
class NOGSBPS_API UDescriptorFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetUseName(TSubclassOf< UFGItemDescriptor > item, bool UseName) { item.GetDefaultObject()->mUseDisplayNameAndDescription = UseName; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetName(TSubclassOf< UFGItemDescriptor > item, FText Name) { item.GetDefaultObject()->mDisplayName = Name; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetDescription(TSubclassOf< UFGItemDescriptor > item, FText Name) { item.GetDefaultObject()->mDescription = Name; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetMesh(TSubclassOf< UFGItemDescriptor > item, UStaticMesh * Mesh) { item.GetDefaultObject()->mConveyorMesh = Mesh; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetMaterial(TSubclassOf< UFGItemDescriptor > item, UMaterialInterface * Mat);
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetBigIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D *Icon) { item.GetDefaultObject()->mPersistentBigIcon = Icon; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetSmallIcon(TSubclassOf<UFGItemDescriptor> item, UTexture2D *Icon) { item.GetDefaultObject()->mSmallIcon = Icon; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetFluidColor(TSubclassOf<UFGItemDescriptor> item, FColor  Value) { item.GetDefaultObject()->mFluidColor = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetForm(TSubclassOf<UFGItemDescriptor> item, EResourceForm  Value) { item.GetDefaultObject()->mForm = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetCategory(TSubclassOf<UFGItemDescriptor> item, TSubclassOf<UFGItemCategory>  Value) { item.GetDefaultObject()->mItemCategory = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetCanbeDisgarded(TSubclassOf<UFGItemDescriptor> item, bool  Value) { item.GetDefaultObject()->mCanBeDiscarded = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetRememberPickUp(TSubclassOf<UFGItemDescriptor> item, bool  Value) { item.GetDefaultObject()->mRememberPickUp = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetEnergyValue(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mEnergyValue = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetRadioactiveDecay(TSubclassOf<UFGItemDescriptor> item, float  Value) { item.GetDefaultObject()->mRadioactiveDecay = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetStackSize(TSubclassOf<UFGItemDescriptor> item, EStackSize  Value) { item.GetDefaultObject()->mStackSize = Value; item->MarkPackageDirty(); }
	UFUNCTION(BlueprintPure, Category = "Editor| Item")
		static EStackSize GetStackSize(TSubclassOf<UFGItemDescriptor> item) { return item.GetDefaultObject()->mStackSize; }

	UFUNCTION(BlueprintPure, Category = "Editor| Item")
		static FItemDescriptorStruct GetStructFromDescriptor(TSubclassOf<UFGItemDescriptor> inClass) { return FItemDescriptorStruct(inClass); }

	UFUNCTION(BlueprintCallable, Category = "Editor| Item")
		static void SetDescriptorFromStruct(TSubclassOf<UFGItemDescriptor> inClass, FItemDescriptorStruct Struct);

	/** Returns true if FItemDescriptorStruct A is equal to FItemDescriptorStruct B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (DescriptorStruct)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Item")
		static bool EqualEqual_FDescriptorStructFDescriptorStruct(FItemDescriptorStruct A, FItemDescriptorStruct B);
	/** Returns true if FItemDescriptorStruct A is equal to the generated FItemDescriptorStruct from a UFGItemDescriptor B (A == B)*/
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (UFGItemDescriptor)", CompactNodeTitle = "==", ScriptMethod = "Equals", ScriptOperator = "==", Keywords = "== equal"), Category = "Editor| Item")
		static bool EqualEqual_FDescriptorStructUFGItemDescriptor(FItemDescriptorStruct A, TSubclassOf<class UFGItemDescriptor> B);





	
};
