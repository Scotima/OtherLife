// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class OtherLifeFarm : ModuleRules
{
	public OtherLifeFarm(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.Add(ModuleDirectory);

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput", "UMG" });
       
        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
