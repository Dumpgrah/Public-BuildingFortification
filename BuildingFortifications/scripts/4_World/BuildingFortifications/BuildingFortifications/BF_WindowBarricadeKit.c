class BF_WindowBarricadeKit extends BuildingFortficationsKit
{	
	override void Open()
	{
		PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (player && player.IsPlayerDisconnected())
			return;
		
		ReplaceItemWithNewLambdaBase lambda = new ReplaceItemWithNewLambdaBase(this, "BF_WindowBarricadeMedKit");
		player.ServerReplaceItemInHandsWithNew(lambda);
	}

	override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
	{
		super.OnPlacementComplete(player, position, orientation);
		
		if (GetGame().IsServer())
		{
			PlayerBase player_base = PlayerBase.Cast(player);
			BF_WindowBarricade Barricade = BF_WindowBarricade.Cast(GetGame().CreateObjectEx("BF_WindowBarricade", GetPosition(), ECE_PLACE_ON_SURFACE));
			Barricade.SetPosition(position);
			Barricade.SetOrientation(orientation);
			
			//make the kit invisible, so it can be destroyed from deploy UA when action ends
			HideAllSelections();

			SetIsDeploySound(true);

			GetGame().ObjectDelete(this);
		}	
	}
	
	override float HeightCheckOverride()
	{
		return 50;
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionBFTurnAroundKit);
	}
	
	override void OnDebugSpawn()
	{
		SpawnEntityOnGroundPos("Shovel", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Hammer", GetPosition());
		SpawnEntityOnGroundPos("Pliers", GetPosition());

		for (int i0 = 0; i0 < 10; i0++)
		{
			SpawnEntityOnGroundPos("WoodenPlank", GetPosition());
		}
		
		for (int i1 = 0; i1 < 5; i1++)
		{
			SpawnEntityOnGroundPos("WoodenStick", GetPosition());
		}
		
		for (int i2 = 0; i2 < 5; i2++)
		{
			SpawnEntityOnGroundPos("Nail", GetPosition());
		}	

		for (int i3 = 0; i3 < 4; i3++)
		{
			SpawnEntityOnGroundPos("MetalPlate", GetPosition());
		}
	}
};