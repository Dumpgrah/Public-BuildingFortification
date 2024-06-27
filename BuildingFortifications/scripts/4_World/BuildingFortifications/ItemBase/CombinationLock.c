
modded class CombinationLock
{
	override void UnlockServer( EntityAI player, EntityAI parent )
	{
		BF_DoorBarricade DoorBarricade = BF_DoorBarricade.Cast( parent );
		
		if ( DoorBarricade )
		{
			if ( IsLockAttached() )
			{				
				InventoryLocation inventory_location = new InventoryLocation;
				GetInventory().GetCurrentInventoryLocation( inventory_location );			
				DoorBarricade.GetInventory().SetSlotLock( inventory_location.GetSlot(), false );
		
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
		BF_DoorBarricade Barricade = BF_DoorBarricade.Cast( GetHierarchyParent() );
		if (Barricade)
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
		
		BF_DoorBarricade Barricade = BF_DoorBarricade.Cast( GetHierarchyParent() );
		if (Barricade)
		{
			return true;
		}
		
		return super.IsLockAttached();
	} 
	
}
