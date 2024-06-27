class CfgPatches
{
	class BF_Define
	{
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};
class CfgMods
{
	class BF_Define
	{
		dir = "0_BF_Define";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "BuildingFortifications";
		credits = "";
		author = "Dumpgrah";
		authorID = "0";
		version = "1";
		extra = 0;
		type = "mod";
		dependencies[] = {"Core","Game","World","Mission"};
		class defs
		{
			class engineScriptModule
			{
				value = "";
				files[] = {"0_BF_Define/scripts/Common"};
			};
			class gameLibScriptModule
			{
				files[] = {"0_BF_Define/scripts/Common"};
			};
			class gameScriptModule
			{
				files[] = {"0_BF_Define/scripts/Common"};
			};
			class worldScriptModule
			{
				files[] = {"0_BF_Define/scripts/Common"};
			};
			class missionScriptModule
			{
				files[] = {"0_BF_Define/scripts/Common"};
			};
		};
	};
};