class CfgPatches
{
	class BuildingFortifications
	{
		requiredVersion = 0.1;
		requiredAddons[] = 
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Consumables",
			"BuildingFortifications_Data",
			"BuildingFortifications_LanguageCore",
			"BuildingFortifications_GUI"
		};
	};
};
class CfgMods
{
	class BuildingFortifications
	{
		dir="BuildingFortifications";
        name="BasicDoor";
        credits="";
        author="Dumpgrah";
        authorID="0";
        version="0.1";
        extra=0;
        type = "Mod";
	    dependencies[]={"gui","Game","World","Mission"};
	    class defs
	    {
			class imageSets
            {
                files[]={"BuildingFortifications\GUI\BuldingFortIcons.imageset"};
            };
			class gameScriptModule
            {
                value="";
                files[]={"BuildingFortifications/scripts/3_Game"};
            };
			class worldScriptModule
            {
                value="";
                files[]={"BuildingFortifications/scripts/4_World"};
            };
			class missionScriptModule
            {
                value="";
                files[]={ "BuildingFortifications/scripts/5_Mission" };
            };
        };
    };
};
class CfgSlots
{
    class Slot_Open_Curtain
    {
        name="Open_Curtain";
        displayName="$STR_Bf_ClosedCurtain";
		ghostIcon="set:BuildingFortIcons image:ClosedCurtain";
    };
    class Slot_Closed_Curtain
    {
        name="Closed_Curtain";
        displayName="$STR_Bf_OpenCurtain";
		ghostIcon="set:BuildingFortIcons image:OpenWindow";
    };
	class Slot_CrossBoard
    {
        name="CrossBoard";
        displayName="Notched Plank";
		ghostIcon="set:BuildingFortIcons image:Barricade";
		stackMax=1;
    };
};
class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyDoorPlankcrossboard : ProxyAttachment
	{
		scope = 2;
		InventorySlot[]={"CrossBoard"};
		model="BuildingFortifications\Data\Door Barricade\Proxies\DoorPlankcrossboard.p3d";
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class BaseBuildingBase;
	class HouseNoDestruct;
	class BuildingFortficationsCore : BaseBuildingBase {};

	class BF_WindowBarricade: BuildingFortficationsCore
	{
		scope = 2;
		displayName = "$STR_Bf_WindowBarricade";
		descriptionShort = "$STR_Bf_bfswafh";
		model = "BuildingFortifications\Data\Window Barricade\WindowBarricadeFullModelV2.p3d";
		bounding = "BSphere";
		overrideDrawArea = "3.0";
		forceFarBubble = "true";
		handheld = "false";
		lootCategory = "Crafted";
		carveNavmesh = 1;
		weight = 10000;
		itemSize[] = {2,3};
		physLayer = "item_large";
		createProxyPhysicsOnInit = "false";
		createdProxiesOnInit[] = {"deployed"};
		rotationFlags = 2;
		simpleHiddenSelections[] = {"Curtain Closed","Curtain Open"};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1.0,
							
							{
								""
							}
						},
						
						{
							0.69999999,
							
							{
								""
							}
						},
						
						{
							0.5,
							
							{
								""
							}
						},
						
						{
							0.30000001,
							
							{
								""
							}
						},
						
						{
							0.0,
							
							{
								""
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
			class DamageZones
			{
				class Body
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.0,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"body"
					};
					fatalInjuryCoef=-1;
				};
				class Step_Two
				{
					class Health
					{
						hitpoints=8000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					displayName="Boards";
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=50;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"step_two"
					};
					fatalInjuryCoef=-1;
				};
				class Step_One: Step_Two
				{
					displayName="Upper Boards";
					componentNames[]=
					{
						"step_one"
					};
				};
				class Step_Three
				{
					class Health
					{
						hitpoints=15750;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					displayName="Plate";
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=35;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"step_three"
					};
					fatalInjuryCoef=-1;
				};
				class Step_Four: Step_Two
				{
					displayName="Prop Stick";
					class Health
					{
						hitpoints=10;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					componentNames[]=
					{
						"step_four"
					};
				};
				class Step_Five : Step_Two
				{
					displayName="Boarded Up";
					componentNames[]=
					{
						"step_five"
					};
					
				};
			};
		};
		attachments[]=
		{
			"Material_Nails",
			"Material_WoodenPlanks",
			"Material_MetalSheets",
			"Open_Curtain",
			"Closed_Curtain",
			"Material_Shelter_FrameSticks"
		};
		class GUIInventoryAttachmentsProps
		{
			class Curtains
			{
				name="$STR_BF_CurtainMount";
				description="";
				attachmentSlots[]=
				{
					"Open_Curtain",
					"Closed_Curtain"
				};
				icon="set:BuildingFortIcons image:MasterCurtainIcon";
			};
			class Material
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Materials";
				description="";
				attachmentSlots[]=
				{
					"Material_Nails",
					"Material_WoodenPlanks",
					"Material_MetalSheets",
					"Material_Shelter_FrameSticks"
				};
				icon="set:BuildingFortIcons image:WindowBarricade";
				selection="wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class AnimRotate
			{
				source="user";
				animPeriod=0.017999999;
				initPhase=0;
			};
			class Deployed: AnimSourceHidden
			{};
			class Base: AnimSourceHidden
			{};
			class Step_Two: AnimSourceHidden
			{};
			class Step_One: AnimSourceHidden
			{};
			class Step_Three:AnimSourceHidden
			{};
			class Step_Four:AnimSourceHidden
			{};
			class Step_Five:AnimSourceHidden
			{};
			class Window_Interact_Rotate: AnimRotate
			{};
			class Metal_Plate_Upward: AnimRotate
			{};
			class Stick_Up_Ward: AnimRotate
			{};
		};
		class Construction
		{
			class wall
			{
				class base
				{
					name="$STR_BF_BarricadeBase";
					is_base=1;
					id=1;
					required_parts[]={};
					conflicted_parts[]={};
					collision_data[]={};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=2;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class step_one
				{
					name="$STR_BF_BoardUpWindow";
					is_base = 0;
					is_gate=0;
					id=2;
					required_parts[]=
					{
						"base"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=3;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class step_two
				{
					name="$STR_BF_AddMoreBoards";
					is_base = 0;
					is_gate=0;
					id=3;
					required_parts[]=
					{
						"step_one"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=2;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
					
				};
				class step_three
				{
					name="Plate";
					is_base = 0;
					is_gate=0;
					id=4;
					required_parts[]=
					{
						"step_two"
					};
					conflicted_parts[]={"step_five"};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_MetalSheets";
							quantity=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=10;
						};
					};
				};
				class step_four
				{
					name="Stick Prop";
					is_base = 0;
					is_gate=1;
					id=5;
					required_parts[]=
					{
						"step_three"
					};
					conflicted_parts[]={"step_five"};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=1;
					dismantle_action_type=1;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="LongWoodenStick";
							slot_name="Material_Shelter_FrameSticks";
							quantity=-1;
							lockable=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=2;
						};
					};
				};
				class step_five
				{
					name="Board up Gaps";
					is_base = 0;
					is_gate=0;
					id=6;
					required_parts[]=
					{
						"step_two"
					};
					conflicted_parts[]={"step_three","step_four"};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=2;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
					
				};
			};
		};
	};	
	class BF_WindowBarricadeMed: BuildingFortficationsCore
	{
		scope = 2;
		displayName = "Medium Window  Barricade";
		descriptionShort = "$STR_Bf_bfswafh";
		model = "BuildingFortifications\Data\Window Barricade\Medium Window\Medium_Window_Barricade_Full_Model.p3d";
		bounding = "BSphere";
		overrideDrawArea = "3.0";
		forceFarBubble = "true";
		handheld = "false";
		lootCategory = "Crafted";
		carveNavmesh = 1;
		weight = 10000;
		itemSize[] = {2,3};
		physLayer = "item_large";
		createProxyPhysicsOnInit = "false";
		createdProxiesOnInit[] = {"deployed"};
		rotationFlags = 2;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1.0,
							
							{
								""
							}
						},
						
						{
							0.69999999,
							
							{
								""
							}
						},
						
						{
							0.5,
							
							{
								""
							}
						},
						
						{
							0.30000001,
							
							{
								""
							}
						},
						
						{
							0.0,
							
							{
								""
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
			class DamageZones
			{
				class A_Base
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.0,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"a_base"
					};
					fatalInjuryCoef=-1;
				};
				class B_Stage_One
				{
					class Health
					{
						hitpoints=8000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					displayName="First Planks";
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=50;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"b_stage_one"
					};
					fatalInjuryCoef=-1;
				};
				class C_Stage_Two: B_Stage_One
				{
					displayName="Second Planks";
					componentNames[]=
					{
						"c_stage_two"
					};
				};
				class D_Stage_Three
				{
					class Health
					{
						hitpoints=15750;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					displayName="Lower Plates";
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=35;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"d_stage_three"
					};
					fatalInjuryCoef=-1;
				};
				class F_Stage_Four: D_Stage_Three
				{
					displayName="Upper Plates";
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									////"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					componentNames[]=
					{
						"f_stage_four"
					};
				};
			};
		};
		attachments[]=
		{
			"Material_Nails",
			"Material_WoodenPlanks",
			"Material_MetalSheets",
		};
		class GUIInventoryAttachmentsProps
		{
			class Material
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Materials";
				description="";
				attachmentSlots[]=
				{
					"Material_Nails",
					"Material_WoodenPlanks",
					"Material_MetalSheets"
				};
				icon="set:BuildingFortIcons image:WindowBarricade";
				selection="wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Deployed: AnimSourceHidden
			{};
			class A_Base: AnimSourceHidden
			{};
			class B_Stage_One: AnimSourceHidden
			{};
			class C_Stage_Two: AnimSourceHidden
			{};
			class D_Stage_Three:AnimSourceHidden
			{};
			class F_Stage_Four:AnimSourceHidden
			{};
		};
		class Construction
		{
			class wall
			{
				class a_base
				{
					name="$STR_BF_BarricadeBase";
					is_base=1;
					id=1;
					required_parts[]={};
					conflicted_parts[]={};
					collision_data[]={};
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=6;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class b_stage_one
				{
					name="$STR_BF_BoardUpWindow";
					is_base = 0;
					is_gate=0;
					id=2;
					required_parts[]=
					{
						"a_base"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=6;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class c_stage_two
				{
					name="$STR_BF_AddMoreBoards";
					is_base = 0;
					is_gate=0;
					id=3;
					required_parts[]=
					{
						"b_stage_one"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=6;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
					
				};
				class d_stage_three
				{
					name="Lower Metal Plates";
					is_base = 0;
					is_gate=0;
					id=4;
					required_parts[]=
					{
						"c_stage_two"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_MetalSheets";
							quantity=2;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class f_stage_four
				{
					name="Upper Metal Plates";
					is_base = 0;
					is_gate=0;
					id=5;
					required_parts[]=
					{
						"c_stage_two"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_MetalSheets";
							quantity=2;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
			};
		};
	};
	class BuildingFortficationsKit: Inventory_Base {};
	class BF_WindowBarricadeKit: BuildingFortficationsKit
	{
		scope=2;
		displayName="$STR_BF_WindowBarricadeKit";
		descriptionShort="$STR_BF_pfbw";
		model = "BuildingFortifications\Data\Window Barricade\WindowBarricadeKit.p3d";
		weight=300;
		rotationFlags=17;
		itemSize[]={1,4};
		itemBehaviour=1;
		attachments[]=
		{
			"Rope"
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Inventory: AnimSourceShown
			{
			};
			class Placing: AnimSourceHidden
			{
			};
		};
	};
	class BF_WindowBarricadeMedKit: BuildingFortficationsKit
	{
		scope=2;
		displayName="Window Barricade Medium Kit";
		descriptionShort="$STR_BF_pfbw";
		model = "BuildingFortifications\Data\Window Barricade\Medium Window\WindowBarricadeMedKit.p3d";
		weight=300;
		rotationFlags=17;
		itemSize[]={1,4};
		itemBehaviour=1;
		attachments[]=
		{
			"Rope"
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Inventory: AnimSourceShown
			{
			};
			class Placing: AnimSourceHidden
			{
			};
		};
	};
	class BF_DoorBarricade: BuildingFortficationsCore
	{
		scope = 2;
		displayName = "$STR_BF_doorbarricade";
		descriptionShort = "$STR_BF_bfsdafh";
		model = "BuildingFortifications\Data\Door Barricade\Door_Barricade_Core.p3d";
		bounding = "BSphere";
		overrideDrawArea = "3.0";
		forceFarBubble = "true";
		handheld = "false";
		lootCategory = "Crafted";
		carveNavmesh = 1;
		weight = 10000;
		itemSize[] = {2,3};
		physLayer = "item_large";
		createProxyPhysicsOnInit = "false";
		createdProxiesOnInit[] = {"deployed"};
		rotationFlags = 2;
		expansionIsOpenable = 1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1.0,
							
							{
								""
							}
						},
						
						{
							0.69999999,
							
							{
								""
							}
						},
						
						{
							0.5,
							
							{
								""
							}
						},
						
						{
							0.30000001,
							
							{
								""
							}
						},
						
						{
							0.0,
							
							{
								""
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
			class DamageZones
			{
				class A_Base
				{
					class Health
					{
						hitpoints=100;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=0.000001;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					displayName="Post";
					componentNames[]=
					{
						"a_base"
					};
					fatalInjuryCoef=-1;
				};
				class B_Lower_Frame
				{
					class Health
					{
						hitpoints=9000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					displayName="$STR_BF_lowerframe";
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"b_lower_frame"
					};
					fatalInjuryCoef=-1;
				};
				class B_Upper_Frame: B_Lower_Frame
				{
					displayName="$STR_BF_upperframe";
					componentNames[]=
					{
						"b_upper_frame"
					};
				};
				class C_Outer_Lower_Planks
				{
					class Health
					{
						hitpoints=12000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=35;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					displayName="$STR_BF_outfirstplanks";
					componentNames[]=
					{
						"c_outer_lower_planks"
					};
				};
				class C_Outer_Upper_Planks: C_Outer_Lower_Planks
				{
					displayName="$STR_BF_outerupperfirstplank";
					componentNames[]=
					{
						"c_outer_upper_planks"
					};
				};
				class D_Lower_Outer_Finalplanks: C_Outer_Lower_Planks
				{
					displayName="$STR_BF_finalouterlowplanks";
					componentNames[]=
					{
						"d_lower_outer_finalplanks"
					};
				};
				class D_Upper_Outer_Finalplanks: C_Outer_Lower_Planks
				{
					displayName="$STR_BF_finalouterupperplank";
					componentNames[]=
					{
						"d_upper_outer_finalplanks"
					};
				};
				class E_Outer_Lower_Plate
				{
					class Health
					{
						hitpoints=15750;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=35;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					displayName="$STR_BF_outerlowplate";
					componentNames[]=
					{
						"e_outer_lower_plate"
					};
				};
				class E_Outer_Upper_Plate: E_Outer_Lower_Plate
				{
					displayName="$STR_BF_outerupplate";
					componentNames[]=
					{
						"e_outer_upper_plate"
					};
				};
				class F_Inner_Lower_Planks: C_Outer_Lower_Planks
				{
					displayName="$STR_BF_innerlowerplank";
					componentNames[]=
					{
						"f_inner_lower_planks"
					};
				};
				class F_Inner_Upper_Planks: C_Outer_Lower_Planks
				{
					displayName="$STR_BF_innerupperplank";
					componentNames[]=
					{
						"f_inner_upper_planks"
					};
				};
				class G_Inner_Lower_Plate: E_Outer_Lower_Plate
				{
					displayName="$STR_BF_innerlowerplate";
					componentNames[]=
					{
						"g_inner_lower_plate"
					};
				};
				class G_Inner_Upper_Plate: E_Outer_Lower_Plate
				{
					displayName="$STR_BF_innerupperplate";
					componentNames[]=
					{
						"g_inner_upper_plate"
					};
				};
				class I_Hindges: B_Lower_Frame
				{
					displayName="$STR_BF_hinges";
					componentNames[]=
					{
						"i_hindges"
					};
				};
				class H_Barricade_Holders
				{
					displayName="$STR_BF_postholders";
					class Health
					{
						hitpoints=2000;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1.0,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\gear\camping\data\fence_pile_of_planks.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_damage.rvmat"
								}
							},
							
							{
								0.00009,
								
								{
									//"DZ\gear\camping\data\fence_pile_of_planks_destruct.rvmat"
								}
							}
						};
					};
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=1;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=0.64999998;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=20;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
					componentNames[]=
					{
						"h_barricade_holders"
					};
				};
				class H_Middle_Holder: H_Barricade_Holders
				{
					displayName="$STR_BF_middleholders";
					componentNames[]=
					{
						"h_middle_holder"
					};
				};
				
			};
		};
		attachments[]=
		{
			"Att_CombinationLock",
			"Material_Nails",
			"Material_WoodenPlanks",
			"Material_MetalSheets",
			"Material_WoodenLogs",
			"Material_MetalWire",
			"Material_Shelter_Sticks",
			"CrossBoard"
		};
		class GUIInventoryAttachmentsProps
		{
			class Base
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Base";
				description="";
				attachmentSlots[]=
				{
					"Material_WoodenLogs"
				};
				icon="set:BuildingFortIcons image:PostsPLusFrame";
				selection="wall";
			};
			class Attachments
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Attachments";
				description="";
				attachmentSlots[]=
				{
					"Att_CombinationLock",
					"CrossBoard"
				};
				icon="set:BuildingFortIcons image:cat_bb_attachments";
				selection="wall";
			};
			class Material
			{
				name="$STR_CfgVehicles_Fence_Att_Category_Materials";
				description="";
				attachmentSlots[]=
				{
					"Material_Nails",
					"Material_WoodenPlanks",
					"Material_MetalSheets",
					"Material_MetalWire",
					"Material_Shelter_Sticks"
				};
				icon="set:BuildingFortIcons image:BuildBarricadeDoor";
				selection="wall";
			};
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class AnimRotate
			{
				source="user";
				animPeriod=0.017999999;
				initPhase=0;
			};
			class Deployed: AnimSourceHidden
			{};
			class A_Base: AnimSourceHidden
			{};
			class B_Lower_Frame: AnimSourceHidden
			{};
			class B_Upper_Frame: AnimSourceHidden
			{};
			class C_Outer_Lower_Planks: AnimSourceHidden
			{};
			class C_Outer_Upper_Planks: AnimSourceHidden
			{};
			class D_Lower_Outer_Finalplanks: AnimSourceHidden
			{};
			class D_Upper_Outer_Finalplanks: AnimSourceHidden
			{};
			class E_Outer_Lower_Plate: AnimSourceHidden
			{};
			class E_Outer_Upper_Plate: AnimSourceHidden
			{};
			class F_Inner_Lower_Planks: AnimSourceHidden
			{};
			class F_Inner_Upper_Planks: AnimSourceHidden
			{};
			class G_Inner_Lower_Plate: AnimSourceHidden
			{};
			class G_Inner_Upper_Plate: AnimSourceHidden
			{};
			class I_Hindges: AnimSourceHidden
			{};
			class H_Barricade_Holders: AnimSourceHidden
			{};
			class H_Middle_Holder : AnimSourceHidden
			{};
			class Wall_Interact_Rotate: AnimRotate
			{};
			class Wall_Base_Down_Rotate: AnimRotate
			{};
			class Wall_Base_Up_Rotate: AnimRotate
			{};
			class Wall_Wood_Down_Rotate: AnimRotate
			{};
			class Wall_Wood_Up_Rotate: AnimRotate
			{};
			class Wall_Metal_Down_Rotate: AnimRotate
			{};
			class Wall_Metal_Up_Rotate: AnimRotate
			{};
			class Wall_Rotate: AnimRotate
			{};
			class Wall2_Rotate: AnimRotate
			{};
			class Wall3_Rotate: AnimRotate
			{};
			class Wall4_Rotate: AnimRotate
			{};
			class Wall5_Rotate: AnimRotate
			{};
			class Wall6_Rotate: AnimRotate
			{};
			class Wall7_Rotate: AnimRotate
			{};
		};
		class Construction
		{
			class wall
			{
				class a_base
				{
					name="$STR_CfgVehicles_Fence_Att_Category_Base";
					is_base=1;
					id=1;
					required_parts[]={};
					conflicted_parts[]={};
					collision_data[]={};
					build_action_type=4;
					dismantle_action_type=4;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenLog";
							slot_name="Material_WoodenLogs";
							quantity=2;
							lockable=1;
						};
					};
				};
				class b_lower_frame
				{
					name="$STR_BF_lowerframe";
					is_base = 0;
					is_gate=0;
					id=2;
					required_parts[]=
					{
						"a_base"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenStick";
							slot_name="Material_Shelter_Sticks";
							quantity=5;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=4;
						};
					};
				};
				class b_upper_frame
				{
					name="$STR_BF_upperframe";
					is_base = 0;
					is_gate=0;
					id=3;
					required_parts[]=
					{
						"a_base"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenStick";
							slot_name="Material_Shelter_Sticks";
							quantity=5;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=4;
						};
					};
				};
				class c_outer_lower_planks
				{
					name="$STR_BF_outfirstplanks";
					is_base = 0;
					is_gate=0;
					id=4;
					required_parts[]=
					{
						"b_lower_frame"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=5;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class c_outer_upper_planks
				{
					name="$STR_BF_outerupperfirstplank";
					is_base = 0;
					is_gate=0;
					id=5;
					required_parts[]=
					{
						"b_upper_frame"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=5;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=8;
						};
					};
				};
				class d_lower_outer_finalplanks
				{
					name="$STR_BF_finalouterlowplanks";
					is_base = 0;
					is_gate=0;
					id=6;
					required_parts[]=
					{
						"c_outer_lower_planks"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=6;
						};
					};
				};
				class d_upper_outer_finalplanks
				{
					name="$STR_BF_finalouterupperplank";
					is_base = 0;
					is_gate=0;
					id=7;
					required_parts[]=
					{
						"c_outer_upper_planks"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=4;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=6;
						};
					};
				};
				class e_outer_lower_plate
				{
					name="$STR_BF_outerlowplate";
					is_base = 0;
					is_gate=0;
					id=8;
					required_parts[]=
					{
						"d_lower_outer_finalplanks"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_MetalSheets";
							quantity=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=6;
						};
					};
				};
				class e_outer_upper_plate
				{
					name="$STR_BF_outerupplate";
					is_base = 0;
					is_gate=0;
					id=9;
					required_parts[]=
					{
						"d_upper_outer_finalplanks"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_MetalSheets";
							quantity=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=6;
						};
					};
				};
				class f_inner_lower_planks
				{
					name="$STR_BF_innerlowerplank";
					is_base = 0;
					is_gate=0;
					id=10;
					required_parts[]=
					{
						"b_lower_frame"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=5;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=5;
						};
					};
				};
				class f_inner_upper_planks
				{
					name="$STR_BF_innerupperplank";
					is_base = 0;
					is_gate=0;
					id=11;
					required_parts[]=
					{
						"b_upper_frame"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=5;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=5;
						};
					};
				};
				class g_inner_lower_plate
				{
					name="$STR_BF_innerlowerplate";
					is_base = 0;
					is_gate=0;
					id=12;
					required_parts[]=
					{
						"f_inner_lower_planks"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_MetalSheets";
							quantity=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=5;
						};
					};
				};
				class g_inner_upper_plate
				{
					name="$STR_BF_innerupperplate";
					is_base = 0;
					is_gate=0;
					id=13;
					required_parts[]=
					{
						"f_inner_upper_planks"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="MetalPlate";
							slot_name="Material_MetalSheets";
							quantity=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=5;
						};
					};
				};
				class i_hindges
				{
					name="$STR_BF_hinges";
					is_base = 0;
					is_gate=1;
					id=14;
					required_parts[]=
					{
						"a_base","b_upper_frame"
					};
					collision_data[]={};
					build_action_type=1;
					dismantle_action_type=1;
					material_type=5;
					class Materials
					{
						class Material1
						{
							type="MetalWire";
							slot_name="Material_MetalWire";
							quantity=-1;
							lockable=1;
						};
					};
				};
				class h_barricade_holders
				{
					name="$STR_BF_postholders";
					is_base = 0;
					is_gate=0;
					id=15;
					required_parts[]=
					{
						"a_base"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=4;
						};
					};
				};
				class h_middle_holder
				{
					name="$STR_BF_middleholders";
					is_base = 0;
					is_gate=0;
					id=16;
					required_parts[]=
					{
						"a_base","b_lower_frame","b_upper_frame","i_hindges"
					};
					conflicted_parts[]={};
                    collision_data[]=
                    {
                        "wall_min",
                        "wall_max"
                    };
					build_action_type=2;
					dismantle_action_type=2;
					material_type=2;
					class Materials
					{
						class Material1
						{
							type="WoodenPlank";
							slot_name="Material_WoodenPlanks";
							quantity=1;
						};
						class Material2
						{
							type="Nail";
							slot_name="Material_Nails";
							quantity=2;
						};
					};
				};
			};
		};
	};	
	class BF_DoorBarricadeKit: Inventory_Base
	{
		scope=2;
		displayName="$STR_BF_doorbarricadekit";
		descriptionShort="$STR_BF_uipfbd";
		model = "BuildingFortifications\Data\Door Barricade\Door_Barricade_Kit.p3d";
		weight=300;
		rotationFlags=17;
		itemSize[]={1,4};
		itemBehaviour=1;
		attachments[]=
		{
			"Rope"
		};
		class AnimationSources
		{
			class AnimSourceShown
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=0;
			};
			class AnimSourceHidden
			{
				source="user";
				animPeriod=0.0099999998;
				initPhase=1;
			};
			class Inventory: AnimSourceShown
			{
			};
			class Placing: AnimSourceHidden
			{
			};
		};
	};	
	
	
	class BurlapCurtain: Inventory_Base
	{
		scope=2;
		displayName="$STR_BF_burlapcloth";
		descriptionShort="$STR_BF_burlapsewncloth";
		model = "BuildingFortifications\Data\Window Barricade\Canvas_Curtain.p3d";
		weight=300;
		rotationFlags=8;
		itemSize[]={1,4};
		itemBehaviour=1;
		inventorySlot[]={"Closed_Curtain","Open_Curtain"};
	};
	class BF_SlottedPlank : Inventory_Base
	{	
		scope=2;
		displayName="Notched Plank";
		descriptionShort="A Notched Plank. The slots help make it almost impossible to shake or rafftle the board off the hooks";
		model = "BuildingFortifications\Data\Door Barricade\Proxies\DoorPlankcrossboard.p3d";
		rotationFlags=17;
		weight=300;
		itemSize[]={2,8};
		itemBehaviour=1;
		inventorySlot[]={"CrossBoard"};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickup
				{
					soundSet="woodenlog_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="woodenlog_drop_SoundSet";
					id=898;
				};
			};
		};
	};
};
class CfgSoundShaders
{
    class DG_MetalRattle_SoundShader
    {
        samples[]=
        {
            {
                "\DZ\sounds\environment\buildings\doors\MetalRattle\doorMetalRattle_1",
                1
            }
        };
        range=50;
        volume=8.0;
    };
	class DG_WoodRattle_SoundShader
    {
        samples[]=
        {
            {
                "\DZ\sounds\environment\buildings\doors\WoodRattle\doorWoodRattle_1",
                1
            }
        };
        range=50;
        volume=6.0;
    };
};
class CfgSoundSets
{
    class DG_MetalRattle_SoundSet
    {
        soundShaders[]=
        {
            "DG_MetalRattle_SoundShader"
        };
    };
	class DG_WoodRattle_SoundSet
    {
        soundShaders[]=
        {
            "DG_WoodRattle_SoundShader"
        };
    };
};
