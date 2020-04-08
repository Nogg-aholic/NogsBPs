// ILikeBanas

#pragma once
#include "Core.h"
#include "Engine.h"
#include "EngineUtils.h"
#include "runtime\Json\Public\Policies\PrettyJsonPrintPolicy.h"
#include "runtime\Json\Public\Policies\CondensedJsonPrintPolicy.h"
#include "Object.h"
#include "UObject/Class.h"
#include "UnrealType.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Json.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NBlueprintFunctionLibrary.generated.h"

/**
 * 
 */


UCLASS()
class NOGSBPS_API UNBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
		UFUNCTION(BlueprintCallable, Category = "Editor|Class")
		static UClass * FindClassByName(FString ClassNameInput);
public:

	template <class FunctorType>
	class PlatformFileFunctor : public IPlatformFile::FDirectoryVisitor	//GenericPlatformFile.h
	{
	public:

		virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory) override
		{
			return Functor(FilenameOrDirectory, bIsDirectory);
		}

		PlatformFileFunctor(FunctorType&& FunctorInstance)
			: Functor(MoveTemp(FunctorInstance))
		{
		}

	private:
		FunctorType Functor;
	};

	template <class Functor>
	static PlatformFileFunctor<Functor> MakeDirectoryVisitor(Functor&& FunctorInstance)
	{
		return PlatformFileFunctor<Functor>(MoveTemp(FunctorInstance));
	}
	static TSharedPtr<FJsonValue> convertUPropToJsonValue(UProperty* prop, void* ptrToProp, bool UsePretty = false);
	static FString SanitizeJsonString(FString write, bool some, bool RemoveOthers = false);
	static TSharedPtr<FJsonObject> convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct, bool UsePrettyName = false);
	static TSharedPtr<FJsonObject> convertUStructToJsonObjectWithName(UStruct * Struct, void * ptrToStruct, FString Name);
	static void convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct);
	static void convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp);


	UFUNCTION(BlueprintCallable, Category = "Data Table", CustomThunk, meta = (DataTable = "DataTable", CustomStructureParam = "Structure"))
		static void InsertIntoDataTable(FString RowName, UDataTable* DataTable, UProperty* Structure);

	DECLARE_FUNCTION(execInsertIntoDataTable)
	{
		//Grab the UDataTable Object from the Stack
		FString RowName;
		Stack.StepCompiledIn<UStrProperty>(&RowName);
		P_GET_OBJECT(UDataTable, DataTable);

		// Step into the stack
		Stack.Step(Stack.Object, NULL);

		// Grab the last property found when we walked the stack
		// This does not contains the property value, only its type information

		UStructProperty* StructureProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);


		// Grab the base address where the struct actually stores its data
		// This is where the property value is truly stored
		void* StructurePtr = Stack.MostRecentPropertyAddress;

		// We need this to wrap up the stack
		P_FINISH;

		//Now we have our data from the stack, lets internally update the data table
		InternalInsertIntoDataTable(DataTable, StructureProperty, StructurePtr, RowName);
	}
	static void InternalInsertIntoDataTable(UDataTable* DataTable, UStructProperty* Structure, void* StructurePtr, FString RowName);


	UFUNCTION(BlueprintCallable, Category = "Json", CustomThunk, meta = (CustomStructureParam = "Structure"))
		static void GetStructAsJsonForTable(FString RowName, bool UsePretty, UPARAM(ref)FString &String, UProperty *Structure);

	DECLARE_FUNCTION(execGetStructAsJsonForTable)
	{
		FString RowName;
		bool UsePretty;
		Stack.StepCompiledIn<UStrProperty>(&RowName);
		Stack.StepCompiledIn<UBoolProperty>(&UsePretty);
		PARAM_PASSED_BY_REF(String, UStrProperty, FString);
		Stack.Step(Stack.Object, NULL);

		UStructProperty* StructureProperty = ExactCast<UStructProperty>(Stack.MostRecentProperty);

		void* StructurePtr = Stack.MostRecentPropertyAddress;

		P_FINISH;
		InternalGetStructAsJson(StructureProperty, StructurePtr, String, RowName,UsePretty);
	}
	static void InternalGetStructAsJson(UStructProperty *Structure, void * StructurePtr, FString &String, FString Name, bool UsePretty = false);

	/** Obtain all files in a provided directory, with optional extension filter. All files are returned if Ext is left blank. Returns false if operation could not occur. */
	UFUNCTION(BlueprintPure, Category = "VictoryBPLibrary|File IO")
		static bool FileIO_GetFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext);




	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Victory Get All Files
//      Optional File Extension Filter!!!  by Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	UFUNCTION(BlueprintPure, Category = "VictoryBPLibrary|File IO")
	static FORCEINLINE bool GetFiles(const FString& FullPathOfBaseDir, TArray<FString>& FilenamesOut, bool Recursive = false, const FString& FilterByExtension = "")
	{
		//Format File Extension, remove the "." if present
		const FString FileExt = FilterByExtension.Replace(TEXT("."), TEXT("")).ToLower();

		FString Str;
		auto FilenamesVisitor = MakeDirectoryVisitor(
			[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			//Files
			if (!bIsDirectory)
			{
				//Filter by Extension
				if (FileExt != "")
				{
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					//Filter by Extension
					if (FPaths::GetExtension(Str).ToLower() == FileExt)
					{
						if (Recursive)
						{
							FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
						}
						else
						{
							FilenamesOut.Push(Str);
						}
					}
				}

				//Include All Filenames!
				else
				{
					//Just the Directory
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					if (Recursive)
					{
						FilenamesOut.Push(FilenameOrDirectory); //need whole path for recursive
					}
					else
					{
						FilenamesOut.Push(Str);
					}
				}
			}
			return true;
		}
		);
		if (Recursive)
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
		}
		else
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
		}
	}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//  Victory Get Directories
	//      Optional Search SubString!!!  by Rama
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Get Directories
	UFUNCTION(BlueprintPure, Category = "VictoryBPLibrary|File IO")
		static FORCEINLINE bool GetDirectories(const FString& FullPathOfBaseDir,  TArray<FString>& DirsOut, const FString&  NotContainsStr = "", bool Recursive = false, const FString& ContainsStr = "")
	{
		FString Str;
		FString Str2;

		auto FilenamesVisitor = MakeDirectoryVisitor(
			[&](const TCHAR* FilenameOrDirectory, bool bIsDirectory)
		{
			if (bIsDirectory)
			{
				//Using a Contains Filter?
				if (ContainsStr != "")
				{
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);
					//Only if Directory Contains Str		
					if (Str.Contains(ContainsStr))
					{
						if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
						else DirsOut.Push(Str);
					}
					
				}
				else if (NotContainsStr != "") {
					if (!Str.Contains(NotContainsStr))
					{
						if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
						else DirsOut.Push(Str);
					}
				}
				//Get ALL Directories!
				else
				{
					//Just the Directory
					Str = FPaths::GetCleanFilename(FilenameOrDirectory);

					if (Recursive) DirsOut.Push(FilenameOrDirectory); //need whole path for recursive
					else DirsOut.Push(Str);
				}
			}
			return true;
		}
		);
		if (Recursive)
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectoryRecursively(*FullPathOfBaseDir, FilenamesVisitor);
		}
		else
		{
			return FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*FullPathOfBaseDir, FilenamesVisitor);
		}
	}



};

static FString makeBetterPropName(FString name);
