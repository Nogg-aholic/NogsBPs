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

UContentLibAssetFactory::UContentLibAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Formats.Add(FString(TEXT("CLjson;")) + NSLOCTEXT("UContentLibAssetFactory", "ParseJson", "Json File").ToString());
	SupportedClass = UClass::StaticClass();
	bCreateNew = false;
	bEditorImport = true;
}

UObject* UContentLibAssetFactory::FactoryCreateBinary(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, const TCHAR* Type, const uint8*& Buffer, const uint8* BufferEnd, FFeedbackContext* Warn)
{
	FString raw;
	UBlueprint * BP = nullptr;

	if (FFileHelper::LoadFileToString(raw, *CurrentFilename))
	{
		UClass* LoadedObject = nullptr;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(*raw);
		FJsonSerializer Serializer;
		TSharedPtr<FJsonObject> Result;
		Serializer.Deserialize(Reader, Result);
		if (!Result.IsValid())
			return nullptr;

		if (Result->HasField("JS_LibClass") && Result->HasField("JS_LibValue"))
		{
			FString String = Result->GetStringField("JS_LibClass");
			TSharedPtr<FJsonObject> Obj = Result->GetObjectField("JS_LibValue");
			Result = Obj;
			if (FPackageName::IsValidObjectPath(String))
			{
				LoadedObject = LoadObject<UClass>(nullptr, *String);

				FString NewPackageName = FPackageName::GetLongPackagePath(InParent->GetOutermost()->GetName()) + TEXT("/") + Name.ToString();
				UPackage* Package = UPackageTools::FindOrCreatePackageForAssetType(FName(*NewPackageName), LoadedObject);
				check(Package);
				NewPackageName = Package->GetFullName();
				if (LoadedObject->IsChildOf(UMaterial::StaticClass()))
				{
					auto MaterialFactory = NewObject<UMaterialFactoryNew>();
					UMaterial* UnrealMaterial = static_cast<UMaterial*>(MaterialFactory->FactoryCreateNew(UMaterial::StaticClass(), Package, Name,
						RF_Standalone | RF_Public, NULL, GWarn));
					Package->FullyLoad();
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, UnrealMaterial);
					Package->SetDirtyFlag(true);
					return UnrealMaterial;
				}
				else if (LoadedObject->IsChildOf(UMaterialInstanceConstant::StaticClass()))
				{
					auto MaterialFactory = NewObject<UMaterialInstanceConstantFactoryNew>();
					UMaterialInstanceConstant* UnrealMaterial = static_cast<UMaterialInstanceConstant*>(MaterialFactory->FactoryCreateNew(
						UMaterialInstanceConstant::StaticClass(), Package, Name, RF_Standalone | RF_Public, nullptr, GWarn));
					Package->FullyLoad();
					UJsonStructBPLib::SetClassDefaultsFromJsonString(raw, nullptr, UnrealMaterial);
					Package->SetDirtyFlag(true);
					return UnrealMaterial;
				}
				else if (LoadedObject->IsChildOf(UStaticMesh::StaticClass()))
				{
					UStaticMesh* cubeMesh = LoadObject<UStaticMesh>(nullptr, TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));


					UStaticMesh* mesh = NewObject<UStaticMesh>(Package, Name, RF_Public | RF_Standalone);

					FStaticMeshSourceModel* SourceModel;
					SourceModel = &cubeMesh->GetSourceModels()[0];
					FRawMesh rawMesh;
					SourceModel->LoadRawMesh(rawMesh);

					// Create a new model
					new(mesh->GetSourceModels()) FStaticMeshSourceModel();
					mesh->GetSourceModels()[0].StaticMeshOwner = mesh;
					mesh->GetSourceModels()[0].SaveRawMesh(rawMesh);

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
				else
				{
					// this is all wrong but for now its too annoying if the Editor creates a popup for each failed type, rahter create somewhat functional dummy BPs , their path ref still might work
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

