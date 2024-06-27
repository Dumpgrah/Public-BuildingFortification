class ActionOpenBuildingCore: ActionInteractBase
{
	protected string LockState = "#open";
	ref NoiseParams m_NoisePar;
	const string SELECTION_INTERACT = "door_interact";
	
	void ActionOpenBuildingCore()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTCursor;
	}

	override string GetText()
	{
		return LockState;
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		#ifdef CodeLock 
        CodeLock codelock;
		#endif
		
		if ( targetObject && targetObject.CanUseConstruction() )
		{
			EntityAI target_entity = EntityAI.Cast( target.GetObject() );
			BuildingFortficationsCore fence = BuildingFortficationsCore.Cast( targetObject );
			BF_DoorBarricade Test25 = BF_DoorBarricade.Cast( targetObject );
			if ( fence && !fence.IsOpened() && fence.HasHinges())
			{
				#ifdef CodeLock
          	  	codelock = CodeLock.Cast(fence.GetCodeLock());
				if (codelock) 
				{
	                if (codelock.GetLockState()) 
					{
	                    LockState = "#open";
	                } else 
					{
	                    LockState = "Set Passcode";
	                }
            	} 
				else 
				{
	               	LockState = "#open";
				}
				#endif
				array<string> selections = new array<string>;
				targetObject.GetActionComponentNameList(target.GetComponentIndex(), selections);
				
				for ( int i = 0; i < selections.Count(); i++ )
				{
					if ( selections[i] == SELECTION_INTERACT )
						return true;
				}
			}

		}
		
		return false;
	}
	
	override void OnStartServer( ActionData action_data )
	{
		BuildingFortficationsCore fence = BuildingFortficationsCore.Cast( action_data.m_Target.GetObject() );
		PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
	#ifdef CodeLock 
        CodeLock codelock = CodeLock.Cast(fence.GetCodeLock());

		if (codelock) {
			if (codelock.GetLockState()) {
				if (codelock.IsOwner(identity.GetId()) || codelock.IsGuest(identity.GetId())) {
					GetCodeLockLogger().WriteLog("acceSS", action_data.m_Player.GetIdentity(), codelock.GetPosition());
					fence.OpenFence();
					return;
				}
			}
		}
	#endif
		if (fence.CanOpenFence())
		{
			fence.OpenFence();
		};
	};
	override void OnStartClient( ActionData action_data)
	{
		super.OnStartClient(action_data);
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
		BuildingFortficationsCore fence = BuildingFortficationsCore.Cast( action_data.m_Target.GetObject() );
		
	
		#ifdef CodeLock 
	        
       	 	CodeLock codelock = CodeLock.Cast(fence.GetCodeLock());
	
	        if (codelock) 
			{
				if (codelock.GetLockState()) 
				{
					if (!codelock.IsOwner(identity.GetId()) && !codelock.IsGuest(identity.GetId())) 
					{
						GetCLUIManager().ShowMenu(CLMENU.GUEST_CODE_MENU, ItemBase.Cast(fence));
					}
				} else {
					GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, ItemBase.Cast(fence));
				}

				if (codelock.GetLockState()) 
				{
					if (codelock.IsOwner(identity.GetId()) || codelock.IsGuest(identity.GetId())) 
					{
						return;
					}
				}
			}
		#endif
		if (!fence.CanOpenFence())
		{
			fence.PlayRattleSound();
		}
		
	};
	
	
	override void OnEndServer( ActionData action_data )
	{
		BuildingFortficationsCore fence = BuildingFortficationsCore.Cast( action_data.m_Target.GetObject() );
	
		if ( fence.CanOpenFence() )
		{
			m_NoisePar = new NoiseParams();
			m_NoisePar.LoadFromPath("CfgVehicles SurvivorBase NoiseActionDefault");

			NoiseSystem noise = GetGame().GetNoiseSystem();
			if ( noise )
			{
				if ( action_data.m_Player )
					noise.AddNoisePos(action_data.m_Player, action_data.m_Target.GetObject().GetPosition(), m_NoisePar);
			}
		}

	};
}