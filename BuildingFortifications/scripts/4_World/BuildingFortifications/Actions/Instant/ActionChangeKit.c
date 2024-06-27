class ActionBFTurnAroundKit: ActionSingleUseBase
{
	void ActionBFTurnAroundKit()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENITEM_ONCE;
		m_CommandUIDProne = DayZPlayerConstants.CMD_ACTIONFB_OPENITEM_ONCE;
		//m_Animation = "open";
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNone;
	}

	override bool HasTarget()
	{
		return false;
	}

	override string GetText()
	{
		return "Change Kit";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( item )
		{ 
			return true;
		}
		return false;
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{
		return true;
	}
	
	override void OnExecuteClient( ActionData action_data )
	{
		if( !GetGame().IsMultiplayer() )
			#ifdef DAYZ_1_11
                ClearInventoryReservation(action_data);
            #else
                ClearInventoryReservationEx(action_data);
            #endif
		
		action_data.m_MainItem.Open();
	}

	override void OnExecuteServer( ActionData action_data )
	{
		if( !GetGame().IsMultiplayer() )
		    #ifdef DAYZ_1_11
                ClearInventoryReservation(action_data);
            #else
                ClearInventoryReservationEx(action_data);
            #endif
		
		action_data.m_MainItem.Open();
	}
};