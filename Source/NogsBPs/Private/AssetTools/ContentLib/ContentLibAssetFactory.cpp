#include "../Public/AssetTools/ContentLib/ContentLibAssetFactory.h"
#include "JsonStructBPLib.h"
#include "Kismet2/KismetEditorUtilities.h" 
#include "Kismet2/BlueprintEditorUtils.h" 
#include "Factories/MaterialFactoryNew.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimSequence.h" 
#include "Animation/BlendSpace.h" 
#include "Animation/AnimBlueprint.h" 

#include "RawMesh.h"
#include "Engine/StaticMesh.h" 

#include "Curves/CurveVector.h" 

#include "Curves/CurveLinearColor.h" 
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PackageTools.h"

#include "Misc/FileHelper.h"

/* UBG_MidiAssetFactory structors
 *****************************************************************************/

UContentLibAssetFactory::UContentLibAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("CLjson;")) + NSLOCTEXT("UContentLibAssetFactory", "ParseJson", "Json File").ToString());
	SupportedClass = UClass::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}

/* UFactory overrides
 *****************************************************************************/

UObject* UContentLibAssetFactory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn)
{
	FString raw;
	UBlueprint * BP = nullptr;

	if (FFileHelper::LoadFileToString(raw, *CurrentFilename))
	{
		UClass* LoadedObject = nullptr;
		TSharedRef<TJsonReader<>> reader = TJsonReaderFactory<>::Create(*raw);
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> result;
		Serializer.Deserialize(reader, result);
		if (!result.IsValid())
			return nullptr;

		if (result->HasField("LibClass") && result->HasField("LibValue"))
		{
			FString String = result->GetStringField("LibClass");
			TSharedPtr<FJsonObject> Obj = result->GetObjectField("LibValue");
			result = Obj;
			if (FPackageName::IsValidObjectPath(String))
			{
				LoadedObject = LoadObject<UClass>(NULL, *String);

				FString NewPackageName = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName()) + TEXT("/") + Name.ToString();
				UPackage* Package = UPackageTools::FindOrCreatePackageForAssetType(FName(*NewPackageName), LoadedObject);
				check(Package);
				NewPackageName = Package->GetFullName();
				if (LoadedObject->IsChildOf(UMaterial::StaticClass()))
				{
					auto MaterialFactory = NewObject<UMaterialFactoryNew>();
					UMaterial* UnrealMaterial = (UMaterial*)MaterialFactory->FactoryCreateNew(UMaterial::StaticClass(), Package, Name, RF_Standalone | RF_Public, NULL, GWarn);
					Package->FullyLoad();
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, UnrealMaterial);
					Package->SetDirtyFlag(true);
					return UnrealMaterial;
				}
				else if (LoadedObject->IsChildOf(UMaterialInstanceConstant::StaticClass()))
				{
					auto MaterialFactory = NewObject<UMaterialInstanceConstantFactoryNew>();
					UMaterialInstanceConstant* UnrealMaterial = (UMaterialInstanceConstant*)MaterialFactory->FactoryCreateNew(UMaterialInstanceConstant::StaticClass(), Package, Name, RF_Standalone | RF_Public, NULL, GWarn);
					Package->FullyLoad();
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, UnrealMaterial);
					Package->SetDirtyFlag(true);
					return UnrealMaterial;
				}
				else if (LoadedObject->IsChildOf(UStaticMesh::StaticClass()))
				{
					UStaticMesh* cubeMesh = LoadObject<UStaticMesh>(NULL, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));


					UStaticMesh* mesh = NewObject<UStaticMesh>(Package, Name, RF_Public | RF_Standalone);

					FStaticMeshSourceModel* sourceModel = &cubeMesh->SourceModels[0];
					FRawMesh rawMesh;
					sourceModel->LoadRawMesh(rawMesh);

					// Create a new model
					new(mesh->SourceModels) FStaticMeshSourceModel();
					mesh->SourceModels[0].StaticMeshOwner = mesh;
					mesh->SourceModels[0].SaveRawMesh(rawMesh);

					TArray<FText> BuildErrorsNuevo;
					mesh->Build(true, &BuildErrorsNuevo);


					mesh->ImportVersion = EImportStaticMeshVersion::LastVersion;
					mesh->CreateBodySetup();
					mesh->SetLightingGuid();
					mesh->PostEditChange();
					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return mesh;
				}
				else if (LoadedObject->IsChildOf(UTexture2D::StaticClass()))
				{
					UTexture2D* Tex = NewObject<UTexture2D>(Package, Name, RF_Public | RF_Standalone);

					uint8 * pixels = (uint8 *)malloc(4 * sizeof(uint8) * 4); // x4 because it's RGBA. 4 integers, one for Red, one for Green, one for Blue, one for Alpha
					pixels[4  + 4 + 0] = 255; // R
					pixels[4  + 4 + 1] = 0;   // G
					pixels[4  + 4 + 2] = 0;   // B
					pixels[4  + 4 + 3] = 255; // A
								
					


					Tex->PlatformData = new FTexturePlatformData();
					Tex->PlatformData->SizeX = 1;
					Tex->PlatformData->SizeY = 1;
					Tex->PlatformData->PixelFormat = PF_R8G8B8A8;

					// Passing the pixels information to the texture
					FTexture2DMipMap* Mip = new(Tex->PlatformData->Mips) FTexture2DMipMap();
					Mip->SizeX = 2;
					Mip->SizeY = 2;
					Mip->BulkData.Lock(LOCK_READ_WRITE);
					uint8* TextureData = (uint8 *)Mip->BulkData.Realloc(4 * sizeof(uint8) * 4);
					FMemory::Memcpy(TextureData, pixels, sizeof(uint8) * 2 * 2 * 4);
					Mip->BulkData.Unlock();

					// Updating Texture & mark it as unsaved
					Tex->AddToRoot();
					Tex->UpdateResource();
					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Tex;
				}
				/*
				else if (LoadedObject->IsChildOf(USkeletalMesh::StaticClass()))
				{
					USkeletalMesh* TexBl = LoadObject<USkeletalMesh>(NULL, TEXT("SkeletalMesh'/Engine/EditorMeshes/SkeletalMesh/DefaultSkeletalMesh.DefaultSkeletalMesh'"));
					USkeletalMesh* Tex = NewObject<USkeletalMesh>(Package, Name, RF_Public | RF_Standalone, TexBl);

					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Tex;
				}
				//
				else if (LoadedObject->IsChildOf(UAnimBlueprint::StaticClass()))
				{
					UAnimBlueprint* AnimE = LoadObject<UAnimBlueprint>(NULL, TEXT("AnimBlueprint'/Game/FactoryGame/Character/Player/Anim_1p.Anim_1p'"));
					UAnimBlueprint* Anim = NewObject<UAnimBlueprint>(Package, Name, RF_Public | RF_Standalone, AnimE);
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr,Anim);

					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Anim;
				}
				else if (LoadedObject->IsChildOf(UAnimSequence::StaticClass()))
				{
					UAnimSequence* AnimE = LoadObject<UAnimSequence>(NULL, TEXT("AnimSequence'/Engine/Tutorial/SubEditors/TutorialAssets/Character/Tutorial_Idle.Tutorial_Idle'"));
					UAnimSequence* Anim = NewObject<UAnimSequence>(Package, Name, RF_Public | RF_Standalone, AnimE);
					//UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, Anim);

					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Anim;
				}
				//
				else if (LoadedObject->IsChildOf(UBlendSpace::StaticClass()))
				{
					UBlendSpace* AnimE = LoadObject<UBlendSpace>(NULL, TEXT("BlendSpace1D'/Engine/Tutorial/SubEditors/TutorialAssets/Character/NewBlendSpace1D.NewBlendSpace1D'"));
					UBlendSpace* Anim = NewObject<UBlendSpace>(Package, Name, RF_Public | RF_Standalone, AnimE);
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, Anim);

					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Anim;
				}
				*/
				else if (LoadedObject->IsChildOf(UCurveFloat::StaticClass()))
				{
					UCurveFloat* Anim = NewObject<UCurveFloat>(Package, Name, RF_Public | RF_Standalone);
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, Anim);

					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Anim;
				}
				else if (LoadedObject->IsChildOf(UCurveLinearColor::StaticClass()))
				{
					UCurveLinearColor* Anim = NewObject<UCurveLinearColor>(Package, Name, RF_Public | RF_Standalone);
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, Anim);

					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Anim;
				}
				else if (LoadedObject->IsChildOf(UCurveVector::StaticClass()))
				{
					UCurveVector* Anim = NewObject<UCurveVector>(Package, Name, RF_Public | RF_Standalone);
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, Anim);

					Package->FullyLoad();
					Package->SetDirtyFlag(true);
					return Anim;
				}
				else if (FKismetEditorUtilities::CanCreateBlueprintOfClass(LoadedObject))
				{
					EBlueprintType BlueprintType = BPTYPE_Normal;
					BP = FKismetEditorUtilities::CreateBlueprint(LoadedObject, Package, Name, BlueprintType, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), NAME_None);
					FString PathName = BP->GetPathName();
					if (!PathName.EndsWith("_C")) {
						PathName.Append("_C");
					}
					UClass* InnerBPClass = LoadObject<UClass>(NULL, *PathName);
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, InnerBPClass);
					BP->MarkPackageDirty();
				}

			}
		}
	}

	return BP;
}

