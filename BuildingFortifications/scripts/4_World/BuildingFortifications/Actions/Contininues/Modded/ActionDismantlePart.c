
modded class ActionDismantlePart
{
	override protected bool DismantleCondition( PlayerBase player, ActionTarget target, ItemBase item, bool camera_check )
	{	
		if ( player && !player.IsLeaning() && !player.IsPlacingLocal() && !player.IsPlacingServer() )
		{
			Object target_object = target.GetObject();
			EntityAI target_entity;
			if ( target_object && target_object.CanUseConstruction() )
			{
				//invalid if is gate and is locked
				if ( Class.CastTo(target_entity,target_object) && (target_entity.FindAttachmentBySlotName("Att_CombinationLock") || target_entity.FindAttachmentBySlotName("Material_FPole_Flag")) || target_entity.FindAttachmentBySlotName("CrossBoard")) 
				{
					return false;
				}
				
				string part_name = target_object.GetActionComponentName( target.GetComponentIndex() );
				
				BaseBuildingBase base_building = BaseBuildingBase.Cast( target_object );
				Construction construction = base_building.GetConstruction();		
				ConstructionPart construction_part = construction.GetConstructionPartToDismantle( part_name, item );
				
				if ( construction_part )
				{
					/*Print("DismantleCondition");
					Print(part_name);
					Print("construction_part.GetPartName: " + construction_part.GetPartName());
					Print("construction_part.GetMainPartName: " + construction_part.GetMainPartName());
					Print("-----");*/
					
					//invalid on gate if the gate is opened
					if ( construction_part.IsGate() && base_building.IsOpened() )
						return false;
					
					//camera and position checks
					bool checked = false;
					
					if ( construction_part.IsBase() )
						checked = true;
					
					if ( !checked && base_building.IsPlayerInside( player, part_name ) && !player.GetInputController().CameraIsFreeLook() )
					{
						//Camera check (client-only)
						if ( camera_check )
						{
							if ( GetGame() && ( !GetGame().IsDedicatedServer() ) )
							{
								if ( base_building.IsFacingCamera( part_name ) )
								{
									return false;
								}
							}
						}

						checked = true;
					}

					if ( checked )
					{
						ConstructionActionData construction_action_data = player.GetConstructionActionData();
						construction_action_data.SetTargetPart( construction_part );
						
						return true;
					}
				}
			}
		}
		
		return false;
	}
}