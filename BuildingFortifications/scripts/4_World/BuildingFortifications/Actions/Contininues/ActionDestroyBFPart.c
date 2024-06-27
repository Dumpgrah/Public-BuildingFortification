class ActionDestroyBFPartCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		int RaidTime = GetBuildingFortificationsConfig().Raid_Destory_Part_Time;
		
		m_ActionData.m_ActionComponent = new CAContinuousTime( RaidTime );
	}
};

class ActionDestroyBFPart: ActionContinuousBase
{
	static int CYCLES = 1;
	
	void ActionDestroyBFPart()
	{
		m_CallbackClass = ActionDestroyBFPartCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;		
		
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}
	
	override void CreateConditionComponents()  
	{	
		m_ConditionItem = new CCINonRuined;
		m_ConditionTarget = new CCTNonRuined( UAMaxDistances.BASEBUILDING );
	}
		
	override string GetText()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		int DisableDestory = GetBuildingFortificationsConfig().Disable_Raiding_Tool;
		if ( player && DisableDestory == 0 )
		{
			ConstructionActionData construction_action_data = player.GetConstructionActionData();
			ConstructionPart constrution_part = construction_action_data.GetTargetPart();
			
			if ( constrution_part )
			{
				return "#destroy" + " " + constrution_part.GetName();
			}
		}
		return "";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{	
		Object target_object = target.GetObject();
		int DisableDestory = GetBuildingFortificationsConfig().Disable_Raiding_Tool;
		if(DisableDestory <= 0)
		{
			BuildingFortficationsCore base_building = BuildingFortficationsCore.Cast( target_object );
			if ( base_building )
			{
				if (player.m_BrokenLegState == eBrokenLegs.BROKEN_LEGS)
					return false;
				
				return DestroyCondition( player, target, item, true );
	
			}
		}
        
		return false;
	}
	
	override bool ActionConditionContinue( ActionData action_data )
	{	
		return DestroyCondition( action_data.m_Player, action_data.m_Target, action_data.m_MainItem , false );
	}	
	
	override void OnFinishProgressServer( ActionData action_data )
	{	
		BuildingFortficationsCore base_building = BuildingFortficationsCore.Cast( action_data.m_Target.GetObject() );
		Construction construction = base_building.GetConstruction();
		ConstructionActionData construction_action_data = action_data.m_Player.GetConstructionActionData();
		ConstructionPart construction_part = construction_action_data.GetTargetPart();

		
		if ( construction.CanDestroyPart( construction_part.GetPartName() ) )
		{
			//build
			construction.DestroyPartServer( action_data.m_Player, construction_part.GetPartName(), AT_DESTROY_PART );
			
			//add damage to tool
			action_data.m_MainItem.DecreaseHealth( UADamageApplied.DESTROY, false );
		}

		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		int EnableLogging = GetBuildingFortificationsConfig().Enable_Destroy_Logs;
		if(	EnableLogging >= 1 )
		{
			PlayerBase player;
			string Firsthalf = player.GetIdentity().GetName() + " (GUID: " +  player.GetIdentity().GetId() + ") " + " Destroyed" + action_data.m_Target.GetObject().GetDisplayName();
			string SecondHalf = " With " + action_data.m_MainItem.GetDisplayName() + " at Postion: " + action_data.m_Target.GetObject().GetPosition();
	
			GetGame().AdminLog( Firsthalf + SecondHalf );
		}
	}
	
	protected bool DestroyCondition( PlayerBase player, ActionTarget target, ItemBase item, bool camera_check )
	{	
		if ( player && !player.IsLeaning() )
		{
			Object target_object = target.GetObject();
			if ( target_object && target_object.CanUseConstruction() )
			{
				string part_name = target_object.GetActionComponentName( target.GetComponentIndex() );
				BaseBuildingBase base_building = BaseBuildingBase.Cast( target_object );
				Construction construction = base_building.GetConstruction();		
				ConstructionPart construction_part = construction.GetConstructionPartToDestroy( part_name );
				BuildingFortficationsCore NDBase = BuildingFortficationsCore.Cast( target.GetObject() );
				
				if ( construction_part )
				{
					//camera and position checks
					if ( base_building.IsFacingPlayer( player, part_name ) && !player.GetInputController().CameraIsFreeLook() )
					{
						//Camera check (client-only)
						if ( camera_check )
						{
							if ( GetGame() && ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) )
							{
								if ( !base_building.IsFacingCamera( part_name ) )
								{
									return false;
								}
							}
						}
						ConstructionActionData construction_action_data = player.GetConstructionActionData();
						construction_action_data.SetTargetPart( construction_part );
						return true;
					}
				}
				
			
				
				//this if statement was added
				else if ( base_building)
				{
					if ( Class.CastTo(base_building, target.GetObject()) )
					{
						if ( construction_part )
						{
							if ( NDBase && NDBase.HasProperDistanceDestory( "outside", player ) )
							{
								ConstructionActionData construction_action_data_flat = player.GetConstructionActionData();
								construction_action_data_flat.SetTargetPart( construction_part );
								return true;
							}
							return false;
						}
					}
				}
			}
		}
		
		return false;
	}
	
	override string GetAdminLogMessage(ActionData action_data)
	{
		return " destroyed " + action_data.m_Target.GetObject().GetDisplayName() + " with " + action_data.m_MainItem.GetDisplayName();
	}
}