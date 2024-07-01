<<<<<<< Updated upstream
// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MariaDBConnection : ModuleRules
{
	public MariaDBConnection(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "mariadbcpp.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libmariadb.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "mariadbclient.lib"));

        PublicIncludePaths.AddRange(
			new string[] {
                Path.Combine(ModuleDirectory,"Mariacxx","include"),
                Path.Combine(ModuleDirectory,"Mariac","include")
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
=======
// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class MariaDBConnection : ModuleRules
{
	public MariaDBConnection(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "mariadbcpp.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "libmariadb.lib"));
        PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "mariadbclient.lib"));

        PublicIncludePaths.AddRange(
			new string[] {
                Path.Combine(ModuleDirectory,"Mariacxx","include"),
                Path.Combine(ModuleDirectory,"Mariac","include")
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
>>>>>>> Stashed changes
