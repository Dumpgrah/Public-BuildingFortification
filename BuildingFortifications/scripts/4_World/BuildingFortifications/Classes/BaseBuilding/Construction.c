modded class Construction
{
	//! Only here for debuging
	/*override bool CanBuildPart( string part_name, ItemBase tool, bool use_tool )
	{
		bool isPartConstructed = IsPartConstructed(part_name);
		bool hasRequiredPart = HasRequiredPart(part_name);
		bool hasConflictPart = HasConflictPart(part_name);
		bool hasMaterials = HasMaterials(part_name);
		bool canUseTooToBuildPart = CanUseToolToBuildPart(part_name, tool);
		bool materialIsRuined = MaterialIsRuined(part_name);
		
		PrintFormat("%1::CanBuildPart - Part name=%2 | Tool=%3 | Is part constructed=%4 | Has required part=%5 | Has conflict part=%6 | Has materials=%7 | Can use tool=%8 | Material is ruined=%9", ToString(), part_name, tool.GetType(), isPartConstructed, hasRequiredPart, hasConflictPart, hasMaterials, canUseTooToBuildPart, materialIsRuined);
		
		if (!isPartConstructed && hasRequiredPart && !hasConflictPart && hasMaterials && (!use_tool || canUseTooToBuildPart) && !materialIsRuined)
		{
			return true;
		}
		
		return false;
	}*/
	
	override bool HasMaterials(string part_name, bool repairing = false)
	{
		//Print(ToString() + "::HasMaterials - Part name: " + part_name);
		if (GetParent().IsInherited(BuildingFortficationsCore) && GetBuildingFortificationsConfig().UseCustomMaterialsList)
		{
			//Print(ToString() + "::HasMaterials - Object is type BuildingFortficationsCore: " + GetParent().GetType());
			string main_part_name = GetConstructionPart(part_name).GetMainPartName();
			string cfg_path = "cfgVehicles" + " " + GetParent().GetType() + " "+ "Construction" + " " + main_part_name + " " + part_name + " " + "Materials";

			if (GetGame().ConfigIsExisting(cfg_path))
			{
				int	child_count = GetGame().ConfigGetChildrenCount(cfg_path);
				for (int i = 0; i < child_count; i++)
				{
					string child_name;
					GetGame().ConfigGetChildName(cfg_path, i, child_name);
					
					//get type, quantity from material
					string material_path;
					string slot_name;
					float quantity;
					material_path = cfg_path + " " + child_name + " " + "slot_name";
					GetGame().ConfigGetText( material_path, slot_name );
					material_path = cfg_path + " " + child_name + " " + "quantity";
					float vanillaQuantity = GetGame().ConfigGetFloat( material_path );
					//Print(ToString() + "::HasMaterials - Configured vanilla quantity: " + child_name + " | Quantity: " + vanillaQuantity);
					
					//! Here we check our custom data for the quantity of the current material
					bool found;
					array<ref BFConstructionData> constMaterials = GetBuildingFortificationsConfig().ConstructionMaterials;
					if (!constMaterials || !constMaterials.Count())
						Error(ToString() + "::HasMaterials - No configured material list!");
					
					foreach (BFConstructionData constData: constMaterials)
					{
						if (constData.ClassName != GetParent().GetType() || constData.PartName != part_name)
							continue;
	
						int materialQuantity;
						found = constData.GetMaterialQuantityForSlot(slot_name, materialQuantity);
						if (found)
						{
							//Print(ToString() + "::HasMaterials - Found material list for object " + GetParent().GetType() + " | Part Name: " + part_name + " | Slot Name: " + slot_name);
							quantity = materialQuantity;
							break;
						}
					}
					
					if (!found)
					{
						quantity = vanillaQuantity;
						Error(ToString() + "::HasMaterials - E1 - Could not find valid material list for object " + GetParent().GetType() + " | Part Name: " + part_name + " | Slot Name: " + slot_name);
					}
	
					if (repairing)
					{
						quantity *= REPAIR_MATERIAL_PERCENTAGE;
						quantity = Math.Max(Math.Floor(quantity),1);
					}
					
					bool hasMaterialsAttached = HasMaterialWithQuantityAttached(slot_name, quantity);
					//Print(ToString() + "::HasMaterials - Has materials with quantity attached: Slot name: " + slot_name + " | Quantity: " + quantity + " | Has materials attached:" + hasMaterialsAttached);
					//if the selected material (or its quantity) is not available
					if (!hasMaterialsAttached)
					{
						//Print(ToString() + "::HasMaterials - F1 - End and return FALSE. Required materials are not attached! Slot name: " + slot_name + " | Quantity: " + quantity);
						return false;
					}
				}
			}
		}
		else
		{
			//Print(ToString() + "::HasMaterials - Object is type: " + GetParent().GetType());
			if (!super.HasMaterials( part_name, repairing))
			{
				//Print(ToString() + "::HasMaterials - F2 - End and return FALSE");
				return false;
			}
		}
	
		//Print(ToString() + "::HasMaterials - End and return TRUE");
		return true;	//return true even if no material required
	}

    override void TakeMaterialsServer(string part_name, bool repairing = false)
    {
		if (GetParent().IsInherited(BuildingFortficationsCore) && GetBuildingFortificationsConfig().UseCustomMaterialsList)
		{
			string main_part_name = GetConstructionPart( part_name ).GetMainPartName();
			string cfg_path = "cfgVehicles" + " " + GetParent().GetType() + " "+ "Construction" + " " + main_part_name + " " + part_name + " " + "Materials";
			
			if (GetGame().ConfigIsExisting(cfg_path))
			{
				int	child_count = GetGame().ConfigGetChildrenCount(cfg_path);
				for (int i = 0; i < child_count; i++)
				{
					string child_name;
					GetGame().ConfigGetChildName(cfg_path, i, child_name);
					
					//get type, quantity from material
					string config_path;
					string slot_name;
					config_path = cfg_path + " " + child_name + " " + "slot_name";
					GetGame().ConfigGetText(config_path, slot_name);
					config_path = cfg_path + " " + child_name + " " + "quantity";
					float vanillaQuantity = GetGame().ConfigGetFloat( config_path );
					config_path = cfg_path + " " + child_name + " " + "lockable";
					bool lockable = GetGame().ConfigGetInt(config_path);
					float quantity;
	
					array<ref BFConstructionData> constMaterials = GetBuildingFortificationsConfig().ConstructionMaterials;
					if (!constMaterials || !constMaterials.Count())
						Error(ToString() + "::HasMaterials - No configured material list!");
					
					bool found;
					foreach (BFConstructionData constData: constMaterials)
					{
						#ifdef DIAG
						constData.Debug();
						#endif
						if (constData.ClassName != GetParent().GetType() || constData.PartName != part_name)
							continue;
	
						int materialQuantity;
						found = constData.GetMaterialQuantityForSlot(slot_name, materialQuantity);
						if (found)
						{
							//Print(ToString() + "::TakeMaterialsServer - Found material list for object " + GetParent().GetType() + " | Part Name: " + part_name + " | Slot Name: " + slot_name);
							quantity = materialQuantity;
							break;
						}
					}
					
					if (!found)
					{
						quantity = vanillaQuantity;
						Error(ToString() + "::TakeMaterialsServer - E1 - Could not find valid material list for object " + GetParent().GetType() + " | Part Name: " + part_name + " | Slot Name: " + slot_name);
					}
					
					ItemBase attachment = ItemBase.Cast( GetParent().FindAttachmentBySlotName(slot_name));
					if (lockable)
					{
						//lock attachment
						InventoryLocation inventory_location = new InventoryLocation;
						attachment.GetInventory().GetCurrentInventoryLocation(inventory_location);
						GetParent().GetInventory().SetSlotLock(inventory_location.GetSlot(), true);
					}
					else
					{
						if (quantity > -1) //0 - ignores quantity
						{
							if (repairing)
							{
								quantity *= REPAIR_MATERIAL_PERCENTAGE;
								quantity = Math.Max(Math.Floor(quantity),1);
							}
							//subtract quantity
							attachment.AddQuantity(-quantity);
						}
						else //-1 - deletes the object
						{
							GetGame().ObjectDelete(attachment);
						}
					}
				}
			}
		}
		else
		{
			super.TakeMaterialsServer(part_name, repairing);
		}
    }
	
	override protected void ReceiveMaterialsServer( notnull Man player, string part_name, string damagezone_name )
	{		
		if (!GetParent().IsInherited(BuildingFortficationsCore) || !GetBuildingFortificationsConfig().UseCustomMaterialsList)
		{
			super.ReceiveMaterialsServer(player, part_name, damagezone_name);
			return;
		}
		
		ConstructionPart construction_part = GetConstructionPart(part_name);
		bool is_base = construction_part.IsBase();
		string main_part_name = construction_part.GetMainPartName();
		string cfg_path = "cfgVehicles" + " " + GetParent().GetType() + " "+ "Construction" + " " + main_part_name + " " + part_name + " " + "Materials";
		int	child_count = GetGame().ConfigGetChildrenCount(cfg_path);
		
		for (int i = 0; i < child_count; i++)
		{
			string child_name;
			GetGame().ConfigGetChildName(cfg_path, i, child_name);
			
			//get type, quantity from material
			string config_path;
			string type;
			string slot_name;
			config_path = cfg_path + " " + child_name + " " + "type";
			GetGame().ConfigGetText(config_path, type);
			config_path = cfg_path + " " + child_name + " " + "slot_name";
			GetGame().ConfigGetText(config_path, slot_name);
			config_path = cfg_path + " " + child_name + " " + "quantity";
			float vanillaQuantity = GetGame().ConfigGetFloat(config_path);
			config_path = cfg_path + " " + child_name + " " + "lockable";
			bool lockable = GetGame().ConfigGetInt(config_path);
			
			//receive material quantity
			ItemBase attachment = ItemBase.Cast(GetParent().FindAttachmentBySlotName(slot_name));
			int slot_id;
			
			//material still attached
			if (lockable)			//if lockable 
			{
				if (attachment)
				{
					InventoryLocation src = new InventoryLocation;
					attachment.GetInventory().GetCurrentInventoryLocation(src);
					if (LogManager.IsBaseBuildingLogEnable()) bsbDebugPrint("[bsb] " + Object.GetDebugName(GetParent()) + " DropNonUsableMaterials UNlocking slot=" + src.GetSlot());
					GetParent().GetInventory().SetSlotLock(src.GetSlot() , false);
					
					//detach if base
					if (is_base)
					{
						if (GetGame().IsMultiplayer() && player)
						{
							InventoryLocation dst = new InventoryLocation;
							GameInventory.SetGroundPosByOwner(player, src.GetItem(), dst);
							player.ServerTakeToDst(src, dst);
						}
						else
						{
							GetParent().GetInventory().DropEntity(InventoryMode.PREDICTIVE, GetParent(), attachment);
						}
					}
				}
			}
			else
			{
				bool found;
				float quantity;
				array<ref BFConstructionData> constMaterials = GetBuildingFortificationsConfig().ConstructionMaterials;
				if (!constMaterials || !constMaterials.Count())
					Error(ToString() + "::ReceiveMaterialsServer - No configured material list!");
				
				foreach (BFConstructionData constData: constMaterials)
				{
					if (constData.ClassName != GetParent().GetType() || constData.PartName != part_name)
						continue;

					int materialQuantity;
					found = constData.GetMaterialQuantityForSlot(slot_name, materialQuantity);
					if (!found)
					{
						Print(ToString() + "::ReceiveMaterialsServer - Found material list for object " + GetParent().GetType() + " | Part Name: " + part_name + " | Slot Name: " + slot_name);
						quantity = materialQuantity;
						break;
					}
				}
				
				if (!found)
				{
					quantity = vanillaQuantity;
					Error(ToString() + "::ReceiveMaterialsServer - E1 - Could not find valid material list for object " + GetParent().GetType() + " | Part Name: " + part_name + " | Slot Name: " + slot_name);
				}
				
				float pile_health;
				float qty_coef;
				vector destination = GetParent().GetPosition();
				//placed on helper memory point, if available
				if (GetParent().MemoryPointExists("" + main_part_name + "_materials"))
				{
					destination = GetParent().GetMemoryPointPos("" + main_part_name + "_materials");
					destination = GetGame().ObjectModelToWorld(GetParent(), destination);
				}
				else if (GetParent().MemoryPointExists(main_part_name))
				{
					destination = GetParent().GetMemoryPointPos(main_part_name);
					destination = GetGame().ObjectModelToWorld(GetParent(), destination);
				}
				//pile_health = GameConstants.DAMAGE_WORN_VALUE * MiscGameplayFunctions.GetTypeMaxGlobalHealth(type);
				pile_health = GetParent().GetHealth01(damagezone_name,"Health") * MiscGameplayFunctions.GetTypeMaxGlobalHealth(type);
				qty_coef =  1 - (GetParent().GetHealthLevel(damagezone_name) * Construction.DECONSTURCT_MATERIAL_LOSS) - Construction.DECONSTURCT_MATERIAL_LOSS;
				quantity *= qty_coef;
				quantity = Math.Max(Math.Floor(quantity), 1);				
				MiscGameplayFunctions.CreateItemBasePiles(type, destination, quantity, pile_health, true);
			}
		}
	}
	
}