
modded class CombinationLock
{
	override void UnlockServer( EntityAI player, EntityAI parent )
	{
		BF_DoorBarricade BF_DB = BF_DoorBarricade.Cast( parent );
		BF_DoubleDoorBarricade BF_DDB = BF_DoubleDoorBarricade.Cast( parent );
		
		if ( BF_DB || BF_DDB)
		{
			if ( IsLockAttached() )
			{				
				InventoryLocation inventory_location = new InventoryLocation;
				GetInventory().GetCurrentInventoryLocation( inventory_location );			
				BF_DB.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );
				BF_DDB.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );
		
				if (player)
					player.ServerDropEntity( this );
				else
					parent.GetInventory().DropEntity(InventoryMode.SERVER, parent, this);
				SetPosition( player.GetPosition() );
				PlaceOnSurface();
				
				m_LockActionPerformed = LockAction.UNLOCKED;
				SetTakeable(true);
				CheckLockedStateServer();
				Synchronize();
			};
		}
		else
		{
			super.UnlockServer(player, parent );
		};		
	}
	override bool IsLockedOnGate()
	{
		BF_DoorBarricade BF_DB = BF_DoorBarricade.Cast( GetHierarchyParent() );
		BF_DoubleDoorBarricade BF_DDB = BF_DoubleDoorBarricade.Cast( GetHierarchyParent() );
		if (BF_DB || BF_DDB)
		{
			if ( IsLocked() )
			{
				return true;
			}
		};
		return super.IsLockedOnGate();
	}
 		
	override bool IsLockAttached()
	{
		
		BF_DoorBarricade BF_DB = BF_DoorBarricade.Cast( GetHierarchyParent() );
		BF_DoubleDoorBarricade BF_DDB = BF_DoubleDoorBarricade.Cast( GetHierarchyParent() );
		if (BF_DB || BF_DDB)
		{
			return true;
		}
		
		return super.IsLockAttached();
	} 
	
}
