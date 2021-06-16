


#include "AssetTools/ResearchTreeFunctionLib.h"

void UResearchTreeFunctionLib::SetRecipeDisplayName(TSubclassOf<UFGResearchTree> Obj, FText mDisplayName)
{
	Obj.GetDefaultObject()->mDisplayName = mDisplayName;
	Obj->MarkPackageDirty();
}

void UResearchTreeFunctionLib::SetPreUnlockDisplayName(TSubclassOf<UFGResearchTree> Obj, FText mPreUnlockDisplayName)
{
	Obj.GetDefaultObject()->mPreUnlockDisplayName = mPreUnlockDisplayName;
	Obj->MarkPackageDirty();
}

void UResearchTreeFunctionLib::SetPreUnlockDescription(TSubclassOf<UFGResearchTree> Obj, FText mPreUnlockDescription)
{
	Obj.GetDefaultObject()->mPreUnlockDescription = mPreUnlockDescription;
	Obj->MarkPackageDirty();
}

void UResearchTreeFunctionLib::SetPostUnlockDescription(TSubclassOf<UFGResearchTree> Obj, FText mPostUnlockDescription)
{
	Obj.GetDefaultObject()->mPostUnlockDescription = mPostUnlockDescription;
	Obj->MarkPackageDirty();
}

void UResearchTreeFunctionLib::SetResearchTreeIcon(TSubclassOf<UFGResearchTree> Obj, FSlateBrush mResearchTreeIcon)
{
	Obj.GetDefaultObject()->mResearchTreeIcon = mResearchTreeIcon;
	Obj->MarkPackageDirty();
}

FVector2D UResearchTreeFunctionLib::ResearchTreeCoordinateToCanvasPosition(int32 X, int32 Y, int32 GridSize)
{
	return FVector2D(X * GridSize, (Y * GridSize) + (X % 2 > 0 ? GridSize / 2 : GridSize)) - (GridSize / 8);
}

FVector2D UResearchTreeFunctionLib::ResearchTreeRoadCoordinateToCanvasPosition(const int32 X, const int32 Y, const int32 OtherX,
                                                                               const int32 GridSize, const bool IsStart)
{
	const float newXOffset = (GridSize / 4);
	const bool mod = X % 2 > 0;
	FVector2D Out = FVector2D((X * GridSize) + newXOffset,
	                          (Y * GridSize) + (mod ? (newXOffset * 2) : (newXOffset * 4)) + (mod
		                          ? (IsStart ? 3.f : 2.f) * newXOffset
		                          : ((IsStart ? 3.f : (X == OtherX ? 2.f : 3.f)) * newXOffset)));
	Out.X -= GridSize / 8;
	Out.Y -= IsStart ? GridSize / 16 : (-1 * (GridSize / 16));
	return Out;
}

UFGResearchTreeNode* UResearchTreeFunctionLib::GetNodeForSchematic(const TSubclassOf<UFGResearchTree> Tree,
                                                                   const TSubclassOf<UFGSchematic> Schematic)
{
	for (auto Node : Tree.GetDefaultObject()->mNodes)
	{
		FProperty* Uprop = Node->GetClass()->FindPropertyByName(TEXT("mNodeDataStruct"));
		FStructProperty* structProp = Cast<FStructProperty>(Uprop);
		if (structProp)
		{
			for (auto prop = TFieldIterator<FProperty>(structProp->Struct); prop; ++prop)
			{
				FClassProperty* SchematicProp = Cast<FClassProperty>(*prop);
				if (SchematicProp)
				{
					void* LoadedObject = prop->ContainerPtrToValuePtr<void>(structProp);
					UClass* CastResult = Cast<UClass>(SchematicProp->GetPropertyValue(LoadedObject));
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

void UResearchTreeFunctionLib::CalculateRoadPosition(const FVector2D Start, const FVector2D End, const float Thickness,
                                                     FVector2D& CanvasStart, FVector2D& Size, float& RenderAngle,
                                                     float& InvertedRenderAngle)
{
	const FVector From = FVector(Start.X, Start.Y, 0.f);
	const FVector To = FVector(End.X, End.Y, 0.f);

	const FRotator Direction = UKismetMathLibrary::FindLookAtRotation(From, To);

	RenderAngle = Direction.Yaw;
	const float Distance = FVector2D::Distance(Start, End);
	Size = FVector2D(FMath::Clamp(Distance, Thickness / 2, 1000.f), Thickness);
	CanvasStart = FVector2D(((Start.X + End.X) / 2) - (Distance / 2), ((Start.Y + End.Y) / 2));
	InvertedRenderAngle = Direction.GetInverse().Yaw;
	return;
}
