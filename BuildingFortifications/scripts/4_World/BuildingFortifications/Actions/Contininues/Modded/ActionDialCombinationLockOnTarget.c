modded class ActionDialCombinationLockOnTarget
{
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if (!target.GetObject())
			return false;
		
		CombinationLock lock = CombinationLock.Cast( target.GetObject() );
		if ( lock && lock.GetHierarchyParent() && Fence.Cast(lock.GetHierarchyParent()) || lock && lock.GetHierarchyParent() && BuildingFortficationsCore.Cast(lock.GetHierarchyParent())  )
		{
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			construction_action_data.SetCombinationLock( lock );
			
			return true;
		}
		super.ActionCondition( player, target, item);
		if (lock && lock.GetHierarchyParent() && BuildingFortficationsCore.Cast(lock.GetHierarchyParent())  )
		{
			ConstructionActionData construction_action_data1 = player.GetConstructionActionData();
			construction_action_data1.SetCombinationLock( lock );
			
			return true;
		}
		return false;
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{	
		//set dialed number
		ConstructionActionData constructionActionData = action_data.m_Player.GetConstructionActionData();
		CombinationLock combination_lock = constructionActionData.GetCombinationLock();
		if (combination_lock)
		{
			combination_lock.DialNextNumber();
	
			//check for unlock state
			if (!combination_lock.IsLockedOnGate())
			{
				
				EntityAI target_entity = EntityAI.Cast(action_data.m_Target.GetObject());
				combination_lock.UnlockServer(action_data.m_Player, target_entity.GetHierarchyParent());
			}
		}
	}
}