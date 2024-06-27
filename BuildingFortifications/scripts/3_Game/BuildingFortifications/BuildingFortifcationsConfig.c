
class BuildingFortificationsConfigBase
{
	string ConfigVersion = "6";
}

class BuildingFortificationsConfig_V5: BuildingFortificationsConfigBase
{
#ifdef EXPANSIONMODBASEBUILDING
	string Expan = "EXPANSION DETECTED : USE RAIDSETTINGS.JSON IN EXPANSIONMOD PROFILE FOLDER FOR DMG CONTROL";
#endif
	int Disable_Raiding_Tool = 0;
	int Raid_Destory_Part_Time = 120;
	int Enable_Destroy_Logs = 0;
	float Window_Barricade_FireArm_Dmg = 100;
	float Window_Barricade_Explosives_Dmg = 100;
	float Window_Barricade_Melee_Dmg = 100;
	string I ="Just a Spacer does Nothing";
	float Door_Barricade_FireArm_Dmg = 100;
	float Door_Barricade_Explosives_Dmg = 100;
	float Door_Barricade_Melee_Dmg = 100;
	bool RuinCodelock = 0;
	int Disable_Base_Damage = 0;
};

class BuildingFortificationsConfig: BuildingFortificationsConfig_V5
{
	protected static string VERSION = "6";
	protected static string DirPATH = "$profile:BuildingFortifications";
	protected static string ProfileFolder = DirPATH + "\\Fortifications Settings.json";

	//! New in version 6
	bool UseCustomMaterialsList = true;
	ref array<ref BFConstructionData> ConstructionMaterials = new array<ref BFConstructionData>;

	void BuildingFortificationsConfig() {}

	// Load config file or create default file if config doesn't exsit
	//! Callstack for instance is creation:
	//! MissionServer::OnInit -> GetBuildingFortificationsConfig()
	static BuildingFortificationsConfig Load()
	{
		BuildingFortificationsConfig bfConfig;

		if (FileExist(ProfileFolder)) //If config exist load File
		{
			Print("[BuildingFortificationsConfig] Loading existing Building Fortifications configuration file..");
			BuildingFortificationsConfig_V5 dataV5;
	        JsonFileLoader<BuildingFortificationsConfig_V5>.JsonLoadFile(ProfileFolder, dataV5);
			
			if (dataV5.ConfigVersion.ToInt() < VERSION.ToInt())
			{
				Print("[BuildingFortificationsConfig] Version is outdated. Convert configuration from " + dataV5.ConfigVersion + " to " + VERSION + ".");
				bool save;
				bfConfig = new BuildingFortificationsConfig();
				bfConfig.CopyFromConfig(dataV5); //! Copy over old settings to current instance

				if (dataV5.ConfigVersion.ToInt() < 6)
				{
					bfConfig.UseCustomMaterialsList = true;
					bfConfig.GenerateDefaultConstructionMaterials();
					save = true;
				}

				dataV5.ConfigVersion = VERSION; //! Should be always latest after file conversion
				if (save)
					JsonFileLoader<BuildingFortificationsConfig>.JsonSaveFile(ProfileFolder, bfConfig);
			}
			else
			{
				Print("[BuildingFortificationsConfig] Load existing Building Fortifications configuration file..");
				JsonFileLoader<BuildingFortificationsConfig>.JsonLoadFile(ProfileFolder, bfConfig);
			}
		}
		else//File does not exist create file
		{
			Print("[BuildingFortificationsConfig] Building Fortifications configuration file not found! Create file..");
			if (!FileExist(DirPATH))
				MakeDirectory(DirPATH);
			
			bfConfig = new BuildingFortificationsConfig();
			bfConfig.Defaults();
			JsonFileLoader<BuildingFortificationsConfig>.JsonSaveFile(ProfileFolder, bfConfig);
		}

		//! Set configuration base damage setting based on vanilla cfgGameplay.json "disableBaseDamage" value for this configuration class instance.
		bfConfig.Disable_Base_Damage = GetGame().ServerConfigGetInt("disableBaseDamage");

		return bfConfig;
	}

	//! Loads old data from existing configuration json file.
	//! Uses BuildingFortificationsConfig_V5 class to get current values from older version files.
	void CopyFromConfig(BuildingFortificationsConfig_V5 config)
	{
	#ifdef EXPANSIONMODBASEBUILDING
		Expan = config.Expan;
	#endif
		Disable_Raiding_Tool = config.Disable_Raiding_Tool;
		Raid_Destory_Part_Time = config.Raid_Destory_Part_Time;
		Enable_Destroy_Logs = config.Enable_Destroy_Logs;
		Window_Barricade_FireArm_Dmg = config.Window_Barricade_FireArm_Dmg;
		Window_Barricade_Explosives_Dmg = config.Window_Barricade_Explosives_Dmg;
		Window_Barricade_Melee_Dmg = config.Window_Barricade_Melee_Dmg;
		I = config.I;
		Door_Barricade_FireArm_Dmg = config.Door_Barricade_FireArm_Dmg;
		Door_Barricade_Explosives_Dmg = config.Door_Barricade_Explosives_Dmg;
		Door_Barricade_Melee_Dmg = config.Door_Barricade_Melee_Dmg;
		RuinCodelock = config.RuinCodelock;
		Disable_Base_Damage = config.Disable_Base_Damage;
	}

	void GenerateDefaultConstructionMaterials()
	{
		TStringArray bfObjects = {"BF_WindowBarricade", "BF_WindowBarricadeMed" , "BF_DoorBarricade"};
		
		if (ConstructionMaterials && ConstructionMaterials.Count())
			ConstructionMaterials.Clear();
		
		foreach(string bfObj: bfObjects)
		{
			BFConstructionData bfConData;
			array<ref BFConstructionData> bfConDataArray;

			string cfg_path = "cfgVehicles" + " " + bfObj + " "+ "Construction";
			if ( !GetGame().ConfigIsExisting( cfg_path ) )
				continue;

			int	child_count = GetGame().ConfigGetChildrenCount( cfg_path );
			for ( int i = 0; i < child_count; i++ )
			{
				string base_name;
				GetGame().ConfigGetChildName( cfg_path, i, base_name );
				string cfg_path_base = "cfgVehicles" + " " + bfObj + " "+ "Construction" + " " + base_name;

				bfConDataArray = new array<ref BFConstructionData>;
				
				int	base_childs = GetGame().ConfigGetChildrenCount( cfg_path_base );
				for ( int j = 0; j < base_childs; j++ )
				{
					string part_name;
					GetGame().ConfigGetChildName( cfg_path_base, j, part_name );
					string cfg_path_materials = "cfgVehicles" + " " + bfObj + " "+ "Construction" + " " + base_name + " " + part_name + " " + "Materials";

					bfConData = new BFConstructionData(bfObj, part_name);

					int	child_count_mat = GetGame().ConfigGetChildrenCount( cfg_path_materials );
					for ( int k = 0; k < child_count_mat; k++ )
					{
						string mat_child_name;
						GetGame().ConfigGetChildName( cfg_path_materials, k, mat_child_name );
						
						//! Get type and quantity from material
						string material_path;
						string slot_name;
						float quantity;
						material_path = cfg_path_materials + " " + mat_child_name + " " + "slot_name";
						GetGame().ConfigGetText( material_path, slot_name );
						material_path = cfg_path_materials + " " + mat_child_name + " " + "quantity";
						quantity = GetGame().ConfigGetFloat( material_path );
						bfConData.AddMaterial(slot_name, quantity);
					}

					ConstructionMaterials.Insert(bfConData);
				}
			}
		}
	}

#ifdef DIAG
	void Debug()
	{
		Print("----------------------------------------");
	#ifdef EXPANSIONMODBASEBUILDING
		Print(ToString() + "::Debug - Expan: " + Expan);
	#endif
		Print(ToString() + "::Debug - Disable_Raiding_Tool: " + Disable_Raiding_Tool);
		Print(ToString() + "::Debug - Enable_Destroy_Logs: " + Enable_Destroy_Logs);
		Print(ToString() + "::Debug - Window_Barricade_FireArm_Dmg: " + Window_Barricade_FireArm_Dmg);
		Print(ToString() + "::Debug - Window_Barricade_Explosives_Dmg: " + Window_Barricade_Explosives_Dmg);
		Print(ToString() + "::Debug - Window_Barricade_Melee_Dmg: " + Window_Barricade_Melee_Dmg);
		Print(ToString() + "::Debug - I: " + I);
		Print(ToString() + "::Debug - Door_Barricade_FireArm_Dmg: " + Door_Barricade_FireArm_Dmg);
		Print(ToString() + "::Debug - Door_Barricade_Explosives_Dmg: " + Door_Barricade_Explosives_Dmg);
		Print(ToString() + "::Debug - Door_Barricade_Melee_Dmg: " + Door_Barricade_Melee_Dmg);
		Print(ToString() + "::Debug - RuinCodelock: " + RuinCodelock);
		Print(ToString() + "::Debug - Disable_Base_Damage: " + Disable_Base_Damage);
		foreach (BFConstructionData data: ConstructionMaterials)
		{
			data.Debug();
		}
		Print("----------------------------------------");
	}
#endif
	
	//! We only send the data that the client rly needs to know.
	void OnSend(ParamsWriteContext ctx)
	{
		ctx.Write(Disable_Raiding_Tool);
		ctx.Write(UseCustomMaterialsList);
		
		if (UseCustomMaterialsList)
		{
			ctx.Write(ConstructionMaterials.Count());
			
			for (int i = 0; i < ConstructionMaterials.Count(); i++)
			{
				ConstructionMaterials[i].OnSend(ctx);
			}	
		}	
	}
	
	//! We only revice the data that the client rly needs to know.
	bool OnRecive(ParamsReadContext ctx)
	{
		if (!ctx.Read(Disable_Raiding_Tool))
			return false;
		
		if (!ctx.Read(UseCustomMaterialsList))
			return false;
		
		if (UseCustomMaterialsList)
		{
			if (ConstructionMaterials && ConstructionMaterials.Count()) //! Clear list
				ConstructionMaterials.Clear();
			
			int constMatCount;
			if (!ctx.Read(constMatCount))
				return false;
			
			for (int i = 0; i < constMatCount; i++)
			{
				BFConstructionData data = new BFConstructionData("", "");
				if (!data.OnRecive(ctx))
					return false;
	
				ConstructionMaterials.Insert(data);
			}
		}
		
		return true;
	}

	void Defaults()
	{
		Print("[BuildingFortificationsConfig] Set defaults in Building Fortifications configuration file..");
	#ifdef EXPANSIONMODBASEBUILDING
		Expan = "EXPANSION DETECTED : USE RAIDSETTINGS.JSON IN EXPANSIONMOD PROFILE FOLDER FOR DMG CONTROL";
	#endif
		Disable_Raiding_Tool = 0;
		Raid_Destory_Part_Time = 120;
		Enable_Destroy_Logs = 0;
		Window_Barricade_FireArm_Dmg = 100;
		Window_Barricade_Explosives_Dmg = 100;
		Window_Barricade_Melee_Dmg = 100;
		I ="Just a Spacer does Nothing";
		Door_Barricade_FireArm_Dmg = 100;
		Door_Barricade_Explosives_Dmg = 100;
		Door_Barricade_Melee_Dmg = 100;
		RuinCodelock = 0;
		Disable_Base_Damage = 0;
		UseCustomMaterialsList = true;

		GenerateDefaultConstructionMaterials();
	}
};

// Static referance to BF config class.
static ref BuildingFortificationsConfig s_BuildingFortificationsConfig;
// Helper function to return Config
static ref BuildingFortificationsConfig GetBuildingFortificationsConfig()
{
#ifdef SERVER
	if (!s_BuildingFortificationsConfig)
	{
		Print("[BuildingFortificationsConfig] Create Building Fortifications configuration instance..");
		s_BuildingFortificationsConfig = BuildingFortificationsConfig.Load();
	#ifdef DIAG
		s_BuildingFortificationsConfig.Debug();
	#endif
	}
#endif

	return s_BuildingFortificationsConfig;
};