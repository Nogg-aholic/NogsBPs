// ILikeBanas


#include "NBlueprintFunctionLibrary.h"
#include "FGItemDescriptor.h"
#include <string>
#include "FGResearchTree.h"

UClass* UNBlueprintFunctionLibrary::FindClassByName(FString ClassNameInput)
{

	const TCHAR* ClassName = *ClassNameInput;
	UObject* ClassPackage = ANY_PACKAGE;



	if (UClass* Result = FindObject<UClass>(ANY_PACKAGE, ClassName, false))
		return Result;

	if (UObjectRedirector* RenamedClassRedirector = FindObject<UObjectRedirector>(ANY_PACKAGE, ClassName, true))
		return CastChecked<UClass>(RenamedClassRedirector->DestinationObject);

	return nullptr;
}

TSharedPtr<FJsonObject> UNBlueprintFunctionLibrary::convertUStructToJsonObjectWithName(UStruct* Struct, void* ptrToStruct, FString Name) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	obj->SetStringField("Name", Name);
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		obj->SetField(prop->GetName(), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}

FString makeBetterPropName(FString name) {
	int32 index;
	FString temp = name;
	name.FindLastChar('_', index);
	name = name.Left(index);
	name.FindLastChar('_', index);
	name = name.Left(index);
	if (name == "")
		return temp;
	return name;
}

TSharedPtr<FJsonObject> UNBlueprintFunctionLibrary::convertUStructToJsonObject(UStruct* Struct, void* ptrToStruct, bool UsePrettyName) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		if (UsePrettyName == true)
			obj->SetField(makeBetterPropName(prop->GetName()), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct),UsePrettyName));
		else
			obj->SetField(prop->GetName(), convertUPropToJsonValue(*prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct)));
	}
	return obj;
}


void UNBlueprintFunctionLibrary::convertJsonObjectToUStruct(TSharedPtr<FJsonObject> json, UStruct* Struct, void* ptrToStruct) {
	auto obj = TSharedPtr<FJsonObject>(new FJsonObject());
	for (auto prop = TFieldIterator<UProperty>(Struct); prop; ++prop) {
		FString FieldName;
		FieldName = prop->GetName();
		auto field = json->TryGetField(FieldName);
		if (!field.IsValid()) continue;
		convertJsonValueToUProperty(field, *prop, prop->ContainerPtrToValuePtr<void>(ptrToStruct));
	}
}

void UNBlueprintFunctionLibrary::convertJsonValueToUProperty(TSharedPtr<FJsonValue> json, UProperty* prop, void* ptrToProp) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		strProp->SetPropertyValue(ptrToProp, json->AsString());
	}
	if (auto txtProp = Cast<UTextProperty>(prop)) {
		FText txt;
		txtProp->SetPropertyValue(ptrToProp, txt.FromString(json->AsString()));
	}
	if (auto nameProp = Cast<UNameProperty>(prop)) {
		nameProp->SetPropertyValue(ptrToProp, *json->AsString());
	}
	else if (auto fProp = Cast<UFloatProperty>(prop)) {
		fProp->SetPropertyValue(ptrToProp, json->AsNumber());
	}
	else if (auto iProp = Cast<UIntProperty>(prop)) {
		iProp->SetPropertyValue(ptrToProp, json->AsNumber());
	}
	else if (auto bProp = Cast<UBoolProperty>(prop)) {
		bProp->SetPropertyValue(ptrToProp, json->AsBool());
	}
	else if (auto eProp = Cast<UEnumProperty>(prop)) {
		UByteProperty* ByteProp = Cast<UByteProperty>(eProp->GetUnderlyingProperty());
		int64 ENumb = json->AsNumber();
		void* EnumPtr = eProp->ContainerPtrToValuePtr<void>(ptrToProp);
		ByteProp->SetIntPropertyValue(EnumPtr, ENumb);
	}
	else if (auto aProp = Cast<UArrayProperty>(prop)) {
		FScriptArrayHelper helper(aProp, ptrToProp);
		helper.EmptyValues();
		TArray<TSharedPtr<FJsonValue>> jsonArr = json->AsArray();
		for (int i = 0; i < jsonArr.Num(); i++) {
			int64 valueIndex = helper.AddValue();
			convertJsonValueToUProperty(jsonArr[i], aProp->Inner, helper.GetRawPtr(valueIndex));
		}
	}
	else if (auto cProp = Cast<UClassProperty>(prop)) {
		FSoftObjectPath CppName = json->AsString();
		UObject* LoadedObject = FSoftObjectPath(json->AsString()).TryLoad();
		UClass * CastResult = Cast<UClass>(LoadedObject);
		cProp->SetPropertyValue(ptrToProp, CastResult);
	}
	else if (auto uProp = Cast<UObjectProperty>(prop)) {
		UObject* uObj = FSoftObjectPath(json->AsString()).TryLoad();
		uProp->SetPropertyValue(ptrToProp, uObj);
	}
	else if (auto sProp = Cast<UStructProperty>(prop)) {
		convertJsonObjectToUStruct(json->AsObject(), sProp->Struct, ptrToProp);
	}
}

TSharedPtr<FJsonValue> UNBlueprintFunctionLibrary::convertUPropToJsonValue(UProperty* prop, void* ptrToProp, bool UsePretty) {
	if (auto strProp = Cast<UStrProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(strProp->GetPropertyValue(ptrToProp)));
	}
	if (auto txtProp = Cast<UTextProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(txtProp->GetPropertyValue(ptrToProp).ToString()));
	}
	if (auto nameProp = Cast<UNameProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(nameProp->GetPropertyValue(ptrToProp).ToString()));
	}
	else if (auto fProp = Cast<UFloatProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(fProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto iProp = Cast<UIntProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(iProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto bProp = Cast<UBoolProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueBoolean(bProp->GetPropertyValue(ptrToProp)));
	}
	else if (auto eProp = Cast<UEnumProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(eProp->GetUnderlyingProperty()->GetSignedIntPropertyValue(ptrToProp)));
	}
	else if (auto nProp = Cast<UNumericProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueNumber(nProp->GetUnsignedIntPropertyValue(ptrToProp)));
	}
	else if (auto aProp = Cast<UArrayProperty>(prop)) {
		auto& arr = aProp->GetPropertyValue(ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			jsonArr.Add(convertUPropToJsonValue(aProp->Inner, (void*)((size_t)arr.GetData() + i * aProp->Inner->ElementSize), UsePretty));
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	}
	else if (auto cProp = Cast<UClassProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(cProp->GetPropertyValue(ptrToProp)->GetPathName()));
	}
	else if (auto oProp = Cast<UObjectProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueString(oProp->GetPropertyValue(ptrToProp)->GetPathName()));
	}
	else if (auto mProp = Cast<UMapProperty>(prop)) {
		auto& arr = mProp->GetPropertyValue(ptrToProp);
		TArray<TSharedPtr<FJsonValue>> jsonArr;
		for (int i = 0; i < arr.Num(); i++) {
			TSharedPtr<FJsonValue> value = (convertUPropToJsonValue(mProp->KeyProp, (void*)((size_t)arr.GetData(i,mProp->MapLayout)), UsePretty));
			TSharedPtr<FJsonObject> JsonObject = TSharedPtr<FJsonObject>(new FJsonObject());
			FString write;
			TSharedRef<TJsonWriter<wchar_t, TCondensedJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TCondensedJsonPrintPolicy<wchar_t>>::Create(&write); //Our Writer Factory
			FString Indentifier = "";
			FJsonSerializer::Serialize(value, Indentifier, JsonWriter);
			SanitizeJsonString(write, false);
			JsonObject->SetField(write, convertUPropToJsonValue(mProp->ValueProp, (void*)((size_t)arr.GetData(i, mProp->MapLayout) + mProp->KeyProp->ElementSize), UsePretty));
			TSharedPtr<FJsonValueObject> Obj = TSharedPtr<FJsonValueObject>(new FJsonValueObject(JsonObject));
			jsonArr.Add(Obj);
		}
		return TSharedPtr<FJsonValue>(new FJsonValueArray(jsonArr));
	}
	else if (auto sProp = Cast<UStructProperty>(prop)) {
		return TSharedPtr<FJsonValue>(new FJsonValueObject(convertUStructToJsonObject(sProp->Struct, ptrToProp, UsePretty)));
	}
	else return TSharedPtr<FJsonValue>(new FJsonValueNull());
}

void UNBlueprintFunctionLibrary::InternalGetStructAsJson(UStructProperty *Structure, void* StructurePtr, FString &String, FString Name, bool UsePretty)
{
	TSharedPtr<FJsonObject> JsonObject;
	if(Name != "")
		JsonObject = convertUStructToJsonObjectWithName(Structure->Struct, StructurePtr, Name);
	else
		JsonObject = convertUStructToJsonObject(Structure->Struct, StructurePtr,UsePretty);

	FString write;
	TSharedRef<TJsonWriter<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>::Create(&write); //Our Writer Factory
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);
	String = write;
}

FString UNBlueprintFunctionLibrary::SanitizeJsonString(FString write, bool some, bool RemoveOthers)
{
	using namespace std;
	// {\r\n\t\"Table\":
	FString VariableName = write;
	FString replace;
	VariableName.Split("[", nullptr, &replace, ESearchCase::IgnoreCase, ESearchDir::FromStart);
	replace.Split("]", &VariableName, nullptr, ESearchCase::IgnoreCase, ESearchDir::FromEnd);

	if (some)
	{
		replace = "[";
		VariableName.Append("]");
	}
	else
	{
		replace = "";
	}
	replace.Append(*VariableName);
	using namespace std;
	string str = TCHAR_TO_UTF8(*replace);
	int size = str.length();
	for (int j = 0; j <= size; j++)
	{
		for (int i = 0; i <= j; i++)
		{
			if (str[i] == ' ')
			{
				str.erase(str.begin() + i);
			}
		}
	}


	return str.c_str();
}


void UNBlueprintFunctionLibrary::InternalInsertIntoDataTable(UDataTable * DataTable, UStructProperty * Structure, void * StructurePtr, FString RowName)
{
	//Get all the contents as a Json string. this Json string also has the Row Structure Information in it as well... pretty handy
	FString TableDump = DataTable->GetTableAsJSON(EDataTableExportFlags::UseJsonObjectsForStructs);
	//TArray<FString> errors = DataTable2->CreateTableFromJSONString(TableDump);
	//return;
	//^ Will output a Json string like the following: [{"Name": "RowName", "Var1" : "Var1Value"}] ---No master Identifier hence bellow comment

	//A function to add "{\"Table\":" to the beginning and "}" to the end of our TableDump. The reason for this is that I am yet to find a function that allows me to read or write a Json string without an Identifier.
	FString Out = "{\"Table\":";
	TableDump.Append("}");
	Out.Append(TableDump);
	TableDump = Out;

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject()); //Create a master FJsonObject
	TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(TableDump); //Read the TableDump into the master FJsonObject for data manipulation  

	FString write; //Our Serialized Json string - Will be ready to use once we've completed our data manipulation and serialized our master FJsonObject
	TSharedRef<TJsonWriter<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>> JsonWriter = TJsonWriterFactory<wchar_t, TPrettyJsonPrintPolicy<wchar_t>>::Create(&write); //Our Writer Factory

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) //Deserialize the master FJsonObject
	{
		TSharedPtr<FJsonObject> JsonObjectArray = MakeShareable(new FJsonObject()); //Create a master FJsonObject
		TArray<TSharedPtr<FJsonValue>> Items = JsonObject->GetArrayField("Table"); //Read the field array (More information on Json https://www.json.org/json-en.html if you are unfamiliar with Json)

		TSharedPtr<FJsonObject> NewItem = MakeShareable(new FJsonObject());

		// Name Row Table Stuff
		NewItem = convertUStructToJsonObjectWithName(Structure->Struct, StructurePtr, RowName); //A function that iterates over our wildcard structure. Code bellow.

		TSharedPtr<FJsonValueObject> NewJsonValue = MakeShareable(new FJsonValueObject(NewItem)); //Cast the FJsonObject NewItem to FJsonValueObject so it can be added to a Json field array

		if (!NewJsonValue.IsValid())
		{
			return;
		}

		//Add our NewJsonValue FJsonValueObject the Items array, then add to the field array called "Table"
		Items.Add(NewJsonValue);
		JsonObject->SetArrayField("Table", Items);


		{
			//We have finished data manipulation and now we serialize our FJsonObject
			FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

			//For some reason, CreateTableFromJSONString will not accept Json Pretty Policy, it will only accept a single line JsonString, so the
			//The SanitizeJsonString removes all the spaces(Will change to just removing new lines when I find a practical solution)

			FString str = SanitizeJsonString(write, true);

			//Update the DataTabe from the new Json string.
			TArray<FString> errors = DataTable->CreateTableFromJSONString(str);

			for (auto e : errors)
			{
				UE_LOG(LogTemp, Warning, TEXT("Nested Object not Valid!"));
			}
		}
	}
}

bool UNBlueprintFunctionLibrary::FileIO_GetFiles(TArray<FString>& Files, FString RootFolderFullPath, FString Ext)
{
	if (RootFolderFullPath.Len() < 1) return false;

	FPaths::NormalizeDirectoryName(RootFolderFullPath);

	IFileManager& FileManager = IFileManager::Get();

	if (Ext == "")
	{
		Ext = "*.*";
	}
	else
	{
		Ext = (Ext.Left(1) == ".") ? "*" + Ext : "*." + Ext;
	}

	FString FinalPath = RootFolderFullPath + "/" + Ext;
	FileManager.FindFiles(Files, *FinalPath, true, false);
	return true;
}