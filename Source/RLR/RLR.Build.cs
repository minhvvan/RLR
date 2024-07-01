// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RLR : ModuleRules
{
	public RLR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

<<<<<<< Updated upstream
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput","Sockets", "Networking", "UMG",  "Slate"
            ,"Protobuf","SlateCore", "GameplayTags"});
=======
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput","Sockets", "Networking", "UMG",  "Slate",
            "SlateCore","Networking" });
>>>>>>> Stashed changes

        PublicIncludePaths.AddRange(new string[] { "RLR" });
        PrivateDependencyModuleNames.AddRange(new string[] { });
        PrivateDependencyModuleNames.Add("MariaDBConnection");
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
