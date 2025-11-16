#ifdef HDSN_BreachingCharge
modded class HDSN_DestructionManager
{
	string GenerateBF_DoorBarricadeType(string type, Construction constr)
	{
		type = "lower_frame"; 

		int WoodCount = 0;

		//wallConstruction.IsPartConstructed("wall_base_down") || wallConstruction.IsPartConstructed("wall_base_up");
		/* 	if(constr.IsPartConstructed("c_outer_lower_planks"))
		{
			type = "_first_lower_planks";
		}	 
		*/	
				
		if(constr.IsPartConstructed("c_outer_lower_planks"))
		{
			WoodCount++; 
		} 	
			
		if(constr.IsPartConstructed("d_lower_outer_finalplanks")) 
		{
			WoodCount++; 
		}

		if(WoodCount == 1)
		{
			type += "_first_lower_planks";
		}
		else if(WoodCount == 2)
		{
			type += "_second_lower_planks";
		}

		return type;
	}
	
	override string GetWallType(Object target, int level = 0, int wall = 0)
	{	
		super.GetWallType(target,level,wall);
		
		string type = target.GetType();
		BaseBuildingBase baseBuildingBase = BaseBuildingBase.Cast(target);
		
		if(baseBuildingBase)
		{
			Construction wallConstruction = baseBuildingBase.GetConstruction();
					 			
			switch(type)
			{
				case "Fence": 
					type = GenerateFenceType(type, wallConstruction);
				break; 
				case "Watchtower":
					type = GenerateWatchtowerType(type, wallConstruction, level, wall);
				break;

				case "ExpansionWall6x3":
					type = GenerateExpansionWallType(type, wallConstruction);
				break;
				
				case "BF_DoorBarricade" :
					type = GenerateBF_DoorBarricadeType(type, wallConstruction);
				break;
				
				
				case "BBP_Bwall":
				case "BBP_Swall":
				case "BBP_BDoor":
				case "BBP_SDoor":
				case "BBP_Bfloor":
				case "BBP_Sfloor":
				case "BBP_Roof_Hatch":
				case "BBP_Bfoundation":
				case "BBP_Sfoundation":
				case "BBP_LGate":
				case "BBP_RGate":
				case "BBP_Half_Bwall":
				case "BBP_Half_Swall":				
				case "BBP_Broof":
				case "BBP_Sroof":
				case "BBP_LHanger_Roof":
				case "BBP_RHanger_Roof":
				case "BBP_Slope_Roof":
				case "BBP_Left_Slope_Wall":
				case "BBP_Right_Slope_Wall":
				case "BBP_Triangle_Bfloor":
				case "BBP_Triangle_Broof":
				case "BBP_BWindow":
				case "BBP_SWindow":
				case "BBP_SGate":
				case "BBP_Floor_Hatch":
				case "BBP_Mesh_Fence":
				case "BBP_Triangle_Foundation":
					type = GenerateBBPType_New(type, wallConstruction);		
				break;
				case "BBP_Bpillar":
				case "BBP_Spillar":
					type = GenerateBBPPillarType_New(type, wallConstruction);						
				break;
				case "BBP_Mesh_Gate":
					type = GenerateBBPMeshType_New(type, wallConstruction);
				break;
				case "BBP_DGate":
					type = GenerateBBPDGateType_New(type, wallConstruction);
				break;
				




				case "BBP_T1_Wall":
					type = GenerateBBPT1WallType(type, wallConstruction);		
				break;
				case "BBP_T2_Wall":
					type = GenerateBBPT2WallType(type, wallConstruction);	
				break; 
				case "BBP_T3_Wall":
					type = GenerateBBPT3WallType(type, wallConstruction);	
				break; 
				case "BBP_T1_Wall_Half": 
					type = GenerateBBPT1WallHalfType(type, wallConstruction);	
				break; 
				case "BBP_T2_Wall_Half": 
					type = GenerateBBPT2WallHalfType(type, wallConstruction);	
				break; 
				case "BBP_T3_Wall_Half":
					type = GenerateBBPT3WallHalfType(type, wallConstruction);	
				break; 
				case "BBP_T1_Window":
					type = GenerateBBPT1WindowType(type, wallConstruction);			
				break; 
				case "BBP_T2_Window":
					type = GenerateBBPT2WindowType(type, wallConstruction);					
				break; 
				case "BBP_T3_Window": 
					type = GenerateBBPT3WindowType(type, wallConstruction);
				break; 
				case "BBP_T1_Door":
					type = GenerateBBPT1DoorType(type, wallConstruction);
				break; 
				case "BBP_T2_Door":
					type = GenerateBBPT2DoorType(type, wallConstruction);
				break; 
				case "BBP_T3_Door": 
					type = GenerateBBPT3DoorType(type, wallConstruction);	
				break; 
				case "BBP_T1_Roof": 
					type = GenerateBBPT1RoofType(type, wallConstruction);
				break; 
				case "BBP_T2_Roof": 
					type = GenerateBBPT2RoofType(type, wallConstruction);
				break; 
				case "BBP_T3_Roof": 
					type = GenerateBBPT3RoofType(type, wallConstruction);
				break; 
				case "BBP_T1_Floor":
					type = GenerateBBPT1FloorType(type, wallConstruction);
				break; 
				case "BBP_T2_Floor":
					type = GenerateBBPT2FloorType(type, wallConstruction);
				break; 
				case "BBP_T3_Floor":
					type = GenerateBBPT3FloorType(type, wallConstruction);
				break; 
				case "BBP_T1_Stair":
					type = GenerateBBPT1StairType(type, wallConstruction);
				break; 
				case "BBP_T2_Stair":
					type = GenerateBBPT2StairType(type, wallConstruction);
				break; 
				case "BBP_T3_Stair":
					type = GenerateBBPT3StairType(type, wallConstruction);
				break; 
				case "BBP_T1_Floor_Hatch": 
					type = GenerateBBPT1FloorHatchType(type, wallConstruction);
				break;  
				case "BBP_T3_Floor_Hatch":
					type = GenerateBBPT3FloorHatchType(type, wallConstruction);
				break; 
				case "BBP_T1_Roof_Hatch":
					type = GenerateBBPT1RoofHatchType(type, wallConstruction);
				break; 
				case "BBP_T2_Roof_Hatch":
					type = GenerateBBPT2RoofHatchType(type, wallConstruction);
				break; 
				case "BBP_T3_Roof_Hatch":
					type = GenerateBBPT3RoofHatchType(type, wallConstruction);
				break; 
				case "BBP_T1_Ramp":
					type = GenerateBBPT1RampType(type, wallConstruction);
				break; 
				case "BBP_T1_Ramp_Wide":
					type = GenerateBBPT1RampWideType(type, wallConstruction);
				break; 
				case "BBP_T1_Gate":
					type = GenerateBBPT1GateType(type, wallConstruction);
				break; 
				case "BBP_T2_Gate":
					type = GenerateBBPT2GateType(type, wallConstruction);
				break; 
				case "BBP_T3_Gate":
					type = GenerateBBPT3GateType(type, wallConstruction);
				break; 
				case "BBP_T3_Door_Half":
					type = GenerateBBPT3DoorHalfType(type, wallConstruction);		
				break; 
				case "BBP_T1_Foundation": 
					type = GenerateBBPT1FoundationType(type, wallConstruction);
				break; 
				case "BBP_T2_Foundation": 
					type = GenerateBBPT2FoundationType(type, wallConstruction);
				break; 
				case "BBP_T3_Foundation":
					type = GenerateBBPT3FoundationType(type, wallConstruction);
				break;	
				case "BBP_Pillar":				
					type = GenerateBBPPillarType(type, wallConstruction);
				break;




				case "ChopperWall3":
					type = GenerateSimpleBaseWallType(type, wallConstruction);
				break;
				case "ChopperDoor2":
					type = GenerateSimpleBaseDoorType(type, wallConstruction);
				break;		
				case "ChopperGate":
					type = GenerateSimpleBaseGateType(type, wallConstruction);
				break;
				case "ChopperWallHalf":
					type = GenerateSimpleBaseWallHalfType(type, wallConstruction);
				break;
				case "ChopperWindow":
					type = GenerateSimpleBaseWindowType(type, wallConstruction);
				break;
				case "ChopperRoof2":
					type = GenerateSimpleBaseRoofType(type, wallConstruction);
				break;
				case "ChopperFloor4":
					type = GenerateSimpleBaseFloorType(type, wallConstruction);
				break;
				case "ChopperStaircase":
					type = GenerateSimpleBaseStaircaseType(type, wallConstruction);
				break;
				case "ChopperPost2":
					type = GenerateSimpleBasePostType(type, wallConstruction);
				break;
				case "ChopperPostHalf":
					type = GenerateSimpleBasePostHalfType(type, wallConstruction);
				break;




				case "EvenMoreDoor":
					type = GenerateEvenMoreDoorType(type, wallConstruction);
				break;	
				case "EvenMoreDoor_Double": 
                   type = GenerateEvenMoreDoorDoubleType(type, wallConstruction);
                break;

				default: 
					type = GenerateCustomBaseBuildingBaseObjectType(target, type, wallConstruction, level, wall);
				break;		
			}
		}
		else 
		{
			type = GenerateCustomObjectType(target, type);
		}
		
		
		//Print("Type ==> " + type);
		return type; 
	}
};
#endif