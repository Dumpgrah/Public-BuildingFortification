modded class PluginRecipesManager 
{
 	override void RegisterRecipies()
	{
		super.RegisterRecipies();
		RegisterRecipe(new CraftWindowBarricadekit);
		RegisterRecipe(new CraftWindowBarricadeMedkit);
		RegisterRecipe(new CraftDoorBarricadekit);
		RegisterRecipe(new CraftBurlapCurtain);	
		RegisterRecipe(new BF_CraftSlottedPlank);			
    }
};

