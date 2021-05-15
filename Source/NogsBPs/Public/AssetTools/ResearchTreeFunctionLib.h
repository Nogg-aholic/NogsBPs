

#pragma once

#include "CoreMinimal.h"
#include "FGResearchTree.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

#include "ResearchTreeFunctionLib.generated.h"

/**
 * 
 */
UCLASS()
class NOGSBPS_API UResearchTreeFunctionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetRecipeDisplayName(TSubclassOf < UFGResearchTree>  Obj, FText mDisplayName) { Obj.GetDefaultObject()->mDisplayName = mDisplayName; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetPreUnlockDisplayName(TSubclassOf < UFGResearchTree>  Obj, FText mPreUnlockDisplayName) { Obj.GetDefaultObject()->mPreUnlockDisplayName = mPreUnlockDisplayName; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetPreUnlockDescription(TSubclassOf < UFGResearchTree>  Obj, FText mPreUnlockDescription) { Obj.GetDefaultObject()->mPreUnlockDescription = mPreUnlockDescription; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetPostUnlockDescription(TSubclassOf < UFGResearchTree> Obj, FText mPostUnlockDescription) { Obj.GetDefaultObject()->mPostUnlockDescription = mPostUnlockDescription; Obj->MarkPackageDirty(); };
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
		static void SetResearchTreeIcon(TSubclassOf < UFGResearchTree>  Obj, FSlateBrush mResearchTreeIcon) { Obj.GetDefaultObject()->mResearchTreeIcon = mResearchTreeIcon; Obj->MarkPackageDirty(); };

	UFUNCTION(BlueprintPure, Category = "ResearchTree")
		static FVector2D ResearchTreeCoordinateToCanvasPosition(int32 X, int32 Y, int32 GridSize)
	{ 
		return FVector2D(X * GridSize, (Y * GridSize) + (X % 2 > 0 ? GridSize / 2 : GridSize)) - (GridSize/8);
	}
	UFUNCTION(BlueprintPure, Category = "ResearchTree")
		static FVector2D ResearchTreeRoadCoordinateToCanvasPosition(int32 X, int32 Y, int32 OtherX, int32 GridSize,bool IsStart)
	{
		float newXOffset = (GridSize / 4); bool mod = X % 2 > 0;
		FVector2D Out = FVector2D((X * GridSize) + newXOffset, (Y * GridSize) + (mod ? (newXOffset * 2) : (newXOffset * 4)) + (mod ? (IsStart ? 3.f : 2.f) * newXOffset : ((IsStart ? 3.f : (X == OtherX ? 2.f : 3.f)) * newXOffset)));
		Out.X -= GridSize / 8;
		Out.Y -= IsStart ? GridSize / 16 : (-1 * (GridSize / 16));
		return Out;
	}


	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
		static UFGResearchTreeNode * GetNodeForSchematic(TSubclassOf<class UFGResearchTree> Tree, TSubclassOf<class UFGSchematic> Schematic)
	{
		for (auto Node : Tree.GetDefaultObject()->mNodes)
		{
			UProperty *  uprop = Node->GetClass()->FindPropertyByName(TEXT("mNodeDataStruct"));
			UStructProperty *  structProp = Cast<UStructProperty>(uprop); 
			if (structProp)
			{
				for (auto prop = TFieldIterator<UProperty>(structProp->Struct); prop; ++prop) {
					UClassProperty * SchematicProp = Cast<UClassProperty>(*prop);
					if (SchematicProp)
					{
						void* LoadedObject = prop->ContainerPtrToValuePtr<void>(structProp);
						UClass * CastResult = Cast<UClass>(SchematicProp->GetPropertyValue(LoadedObject));
						if (CastResult)
						{
							if (CastResult == Schematic)
							{
								return Node;
							}
							else
							{
								break;

							}
						}
					}
				}
			}
		}
		return nullptr;
	}

	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
		static void CalculateRoadPosition(FVector2D Start, FVector2D End,float Thickness, FVector2D &CanvasStart, FVector2D& Size, float& RenderAngle, float& InvertedRenderAngle)
	{
		FVector From = FVector(Start.X, Start.Y, 0.f);
		FVector To = FVector(End.X, End.Y, 0.f);
		
		FRotator direction = UKismetMathLibrary::FindLookAtRotation(From, To);
		
		RenderAngle = direction.Yaw;
		float distance = FVector2D::Distance(Start, End);
		Size = FVector2D(FMath::Clamp(distance,Thickness/2, 1000.f ), Thickness);
		CanvasStart = FVector2D(((Start.X + End.X) / 2) - (distance / 2), ((Start.Y + End.Y) / 2));
		InvertedRenderAngle = direction.GetInverse().Yaw;
		return;
	}


};
