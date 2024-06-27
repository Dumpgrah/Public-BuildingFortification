class BF_DoorBarricadeKit extends BuildingFortficationsKit
{
	override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
	{
		super.OnPlacementComplete(player, position, orientation);
		
		if (GetGame().IsServer())
		{
			PlayerBase player_base = PlayerBase.Cast(player);

			BF_DoorBarricade DoorBar = BF_DoorBarricade.Cast(GetGame().CreateObjectEx("BF_DoorBarricade", GetPosition(), ECE_PLACE_ON_SURFACE));
			
			DoorBar.SetPosition(position);
			DoorBar.SetOrientation(orientation);
			
			//make the kit invisible, so it can be destroyed from deploy UA when action ends
			HideAllSelections();
			
			SetIsDeploySound(true);

			GetGame().ObjectDelete(this);
		}	
	}
	
	override float HeightCheckOverride()
	{
		return 20;
	}
	
	override void OnDebugSpawn()
	{
		SpawnEntityOnGroundPos("Shovel", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Pliers", GetPosition());

		for (int i0 = 0; i0 < 25; i0++)
		{
			SpawnEntityOnGroundPos("WoodenLog", GetPosition());
		}
		
		for (int i1 = 0; i1 < 30; i1++)
		{
			SpawnEntityOnGroundPos("WoodenPlank", GetPosition());
		}
		
		for (int i2 = 0; i2 < 6; i2++)
		{
			SpawnEntityOnGroundPos("Nail", GetPosition());
		}	
		
		for (int i3 = 0; i3 < 10; i3++)
		{
			SpawnEntityOnGroundPos("WoodenStick", GetPosition());
		}
		
		for (int i4 = 0; i4 < 1; i4++)
		{
			SpawnEntityOnGroundPos("MetalWire", GetPosition());
		}

		for (int i5 = 0; i5 < 4; i5++)
		{
			SpawnEntityOnGroundPos("MetalPlate", GetPosition());
		}
	}
};