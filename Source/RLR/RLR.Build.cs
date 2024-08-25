// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RLR : ModuleRules
{
	public RLR(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput","Sockets", "Networking", "UMG",  "Slate"
            ,"Protobuf","SlateCore", "GameplayTags", "GameplayTasks", "AssetRegistry"});

        PublicIncludePaths.AddRange(new string[] { "RLR" });


        PrivateDependencyModuleNames.AddRange(new string[] { });

        if (Target.Type == TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.AddRange(new string[] { "UnrealEd", "Blutility" });
        }

        // 에디터 전용 모듈이 게임 타겟에 포함되지 않도록 보장
        if (Target.Type != TargetRules.TargetType.Editor)
        {
            PrivateDependencyModuleNames.Remove("UnrealEd");
        }
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
