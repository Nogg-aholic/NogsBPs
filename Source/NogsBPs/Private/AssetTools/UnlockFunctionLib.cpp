


#include "AssetTools/UnlockFunctionLib.h"

void UUnlockFunctionLib::InitRecipeUnlocks(UFGUnlockRecipe * Obj, TArray<TSubclassOf<class UFGRecipe>> recipes)
{
#if WITH_EDITOR 
	Obj->Init(recipes);
#else
	return;
#endif
}
void UUnlockFunctionLib::InitUnlockInventorySlot(UFGUnlockInventorySlot * Obj, int32 count)
{
#if WITH_EDITOR 
	Obj->Init(count);
#else
	return;
#endif
}
void UUnlockFunctionLib::InitUnlockArmEquipmentSlot(UFGUnlockArmEquipmentSlot * Obj, int32 count)
{
#if WITH_EDITOR 
	Obj->Init(count);
#else
	return;
#endif
};