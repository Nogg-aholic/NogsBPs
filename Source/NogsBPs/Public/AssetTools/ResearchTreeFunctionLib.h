

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
	static void SetRecipeDisplayName(TSubclassOf<UFGResearchTree> Obj, FText mDisplayName);
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
	static void SetPreUnlockDisplayName(TSubclassOf<UFGResearchTree> Obj, FText mPreUnlockDisplayName);
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
	static void SetPreUnlockDescription(TSubclassOf<UFGResearchTree> Obj, FText mPreUnlockDescription);
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
	static void SetPostUnlockDescription(TSubclassOf<UFGResearchTree> Obj, FText mPostUnlockDescription);
	UFUNCTION(BlueprintCallable, Category = "Editor| ResearchTree")
	static void SetResearchTreeIcon(TSubclassOf<UFGResearchTree> Obj, FSlateBrush mResearchTreeIcon);
	
	UFUNCTION(BlueprintPure, Category = "ResearchTree")
	static FVector2D ResearchTreeCoordinateToCanvasPosition(int32 X, int32 Y, int32 GridSize);
	UFUNCTION(BlueprintPure, Category = "ResearchTree")
	static FVector2D ResearchTreeRoadCoordinateToCanvasPosition(int32 X, int32 Y, int32 OtherX, int32 GridSize,
	                                                            bool IsStart);


	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
	static UFGResearchTreeNode* GetNodeForSchematic(TSubclassOf<class UFGResearchTree> Tree,
	                                                TSubclassOf<class UFGSchematic> Schematic);

	UFUNCTION(BlueprintPure, Category = "Editor| ResearchTree")
	static void CalculateRoadPosition(FVector2D Start, FVector2D End, float Thickness, FVector2D& CanvasStart,
	                                  FVector2D& Size, float& RenderAngle, float& InvertedRenderAngle);
};
