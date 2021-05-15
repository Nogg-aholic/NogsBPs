// ILikeBanas

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "ContentLibAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class NOGSBPS_API UContentLibAssetFactory : public UFactory
{
	GENERATED_UCLASS_BODY()

		// UFactory Interface

		virtual UObject* FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn) override;

};
