modded class ActionNextCombinationLockDialOnTarget
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		if (!target.GetObject())
			return false;
		
		CombinationLock lock = CombinationLock.Cast( target.GetObject() );
		if ( lock && lock.GetHierarchyParent() && Fence.Cast(lock.GetHierarchyParent()) || lock && lock.GetHierarchyParent() && BuildingFortficationsCore.Cast(lock.GetHierarchyParent()) )
		{
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			construction_action_data.SetCombinationLock( lock );
			
			return true;
		}
		
		return false;
	}
}