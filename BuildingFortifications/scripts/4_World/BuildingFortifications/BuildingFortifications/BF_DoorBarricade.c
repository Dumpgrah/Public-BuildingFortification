
class BF_SlottedPlank extends ItemBase
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionClapBearTrapWithThisItem);

		AddAction(ActionAttach);
		//AddAction(ActionDetach);
	}	
};

class BF_DoorBarricade extends BuildingFortficationsCore
{
	const int GATE_STATE_NONE 				= 0;
	const int GATE_STATE_PARTIAL 			= 1;
	const int GATE_STATE_FULL 				= 2;
	
	const string ATTACHMENT_SLOT_COMBINATION_LOCK 	= "Att_CombinationLock";
	const string ATTACHMENT_SLOT_CROSSBOARD 	    = "CrossBoard";
	const string SOUND_GATE_OPEN_START				= "DoorWoodTowerOpen_SoundSet";
	const string SOUND_GATE_CLOSE_START				= "DoorWoodTowerClose_start_SoundSet";
	const string SOUND_GATE_CLOSE_END				= "DoorWoodTowerClose_end_SoundSet";
	const string SOUND_RATTLE_METAL					= "DG_MetalRattle_SoundSet";
	const string SOUND_RATTLE_WOOD   				= "DG_WoodRattle_SoundSet";
	
	//gate openining
	const float GATE_ROTATION_ANGLE_DEG 			= 100;
	const float GATE_ROTATION_TIME_APPROX			= 2000;		//ms
	
	typename ATTACHMENT_COMBINATION_LOCK	= CombinationLock;
	
	protected bool m_ToDiscard 				= false; //for legacy OnStoreLoad handling
	protected bool m_IsOpened 				= false;
	protected bool m_IsOpenedClient			= false;
	protected int m_GateState 				= 0;
	protected bool m_SoundRattle			= false;
	protected int m_SoundRattleClient 		= -1;
	
	protected EffectSound m_SoundGate_Start;
	protected EffectSound m_SoundGate_End;

	bool BreakCodeLock;
	
	void BF_DoorBarricade()
	{
		RegisterNetSyncVariableBool( "m_IsOpened" );
		RegisterNetSyncVariableInt( "m_GateState" );
		RegisterNetSyncVariableBool( "m_SoundRattle" );
		
		ProcessInvulnerabilityCheck(GetInvulnerabilityTypeString());
		
	#ifdef SERVER
		BreakCodeLock = GetBuildingFortificationsConfig().RuinCodelock;
	#endif
	}

	override float GetDmgPercentage(int damageType)
	{
		if(damageType == DT_CLOSE_COMBAT)
		{
			return GetBuildingFortificationsConfig().Door_Barricade_Melee_Dmg / 100;
		}
		else if(damageType == DT_FIRE_ARM)
		{
			return GetBuildingFortificationsConfig().Door_Barricade_FireArm_Dmg / 100;
		}
		else if(damageType == DT_EXPLOSION)
		{
			return GetBuildingFortificationsConfig().Door_Barricade_Explosives_Dmg / 100;
		}
		return 1.0;
	}
	
	override bool HasHinges()
	{
		return m_GateState > GATE_STATE_NONE;
	}
	
	bool HasFullyConstructedGate()
	{
		return m_GateState == GATE_STATE_FULL;
	}

	void SetGateState( int state )
	{
		m_GateState = state;
		SetSynchDirty();
	}
	
	int GetGateState()
	{
		return m_GateState;
	}
		
	int CheckGateState()
	{
		ConstructionPart gate_part = GetConstruction().GetGateConstructionPart();
		int state = GATE_STATE_NONE;
		if ( gate_part.IsBuilt() )
		{
			ConstructionPart req_part;
			array<string> req_parts = gate_part.GetRequiredParts();
			for (int i = 0; i < req_parts.Count(); i++)
			{
				req_part = GetConstruction().GetConstructionPart(req_parts.Get(i));
				if (!req_part.IsBuilt())
					break;
			}
			
			if ( i != req_parts.Count() )
			{
				state = GATE_STATE_PARTIAL;
			}
			else
			{
				state = GATE_STATE_FULL;
			}
			
		}
		return state;
	}
	
	void SetOpenedState( bool state )
	{
		m_IsOpened = state;
	}
	
	override bool IsOpened()
	{
		return m_IsOpened;
	}
	
	bool IsLocked()
	{
		CombinationLock combination_lock = GetCombinationLock();
		BF_SlottedPlank Barricade = GetBarricade();
		if ( combination_lock && combination_lock.IsLocked() )
		{
			return true;
		}
		else if (Barricade && GetConstruction().IsPartConstructed("h_middle_holder"))
		{
			return true;
		}
		#ifdef CodeLock
	        if (IsCodeLocked() ) 
			{
	            return true;
	        }
			else if (Barricade && GetConstruction().IsPartConstructed("h_middle_holder"))
			{
				return true;
			}
		#endif
		return false;
	}
	
	override bool NameOverride(out string output)
	{
		if ( m_GateState != GATE_STATE_NONE )
		{
			output = "Door";  //changes object displayed name if in 'gate' state
			output.ToUpper();
			return true;
		}
		return false;
	}
	
	CombinationLock GetCombinationLock()
	{
		CombinationLock combination_lock = CombinationLock.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_COMBINATION_LOCK ) );
		return combination_lock;
	}

	BF_SlottedPlank GetBarricade()
	{
		BF_SlottedPlank Barricaded = BF_SlottedPlank.Cast( FindAttachmentBySlotName( ATTACHMENT_SLOT_CROSSBOARD ) );
		return Barricaded;
	}
	
	override string GetConstructionKitType()
	{
		return "BF_DoorBarricadeKit";
	}
	
	override bool CanDisplayAttachmentSlot( string slot_name )
	{
		if (!super.CanDisplayAttachmentSlot(slot_name))
			return false;
		
		if ( slot_name == "Att_CombinationLock" )
		{
			if ( !GetConstruction().IsPartConstructed("i_hindges"))
			{
				return false;
			}
			return true;
		}
		if(slot_name == "CrossBoard")
		{
			if (BarricadeHolders())
			{
				return true;
			}
			return false;
		}
		//if ( !GateAttachmentConditions(InventorySlots.GetSlotIdFromString(slot_name)) )
		//	return false;
		//
		return true;
	}
	
	bool BarricadeHolders()
	{
		if (GetConstruction().IsPartConstructed("h_barricade_holders") && GetConstruction().IsPartConstructed("h_middle_holder") )
		{
			return true;
		}
		return false;
	}

	bool FullyConstructed()
	{
		if (GetConstruction().IsPartConstructed("a_base") && GetConstruction().IsPartConstructed("b_lower_frame") && GetConstruction().IsPartConstructed("b_upper_frame") && GetConstruction().IsPartConstructed("c_outer_lower_planks") && GetConstruction().IsPartConstructed("c_outer_upper_planks") && GetConstruction().IsPartConstructed("d_lower_outer_finalplanks") && GetConstruction().IsPartConstructed("e_outer_lower_plate") && GetConstruction().IsPartConstructed("d_upper_outer_finalplanks") && GetConstruction().IsPartConstructed("e_outer_upper_plate") && GetConstruction().IsPartConstructed("f_inner_lower_planks") && GetConstruction().IsPartConstructed("f_inner_upper_planks") && GetConstruction().IsPartConstructed("g_inner_lower_plate") && GetConstruction().IsPartConstructed("g_inner_upper_plate") && GetConstruction().IsPartConstructed("i_hindges") && GetConstruction().IsPartConstructed("h_barricade_holders") && GetConstruction().IsPartConstructed("h_middle_holder"))
			return true;
		else 
			return false;
	}

	bool HasMaterialAttachments()
	{
		if (FindAttachmentBySlotName("Material_Nails") || FindAttachmentBySlotName("Material_WoodenPlanks") || FindAttachmentBySlotName("Material_MetalSheets") || FindAttachmentBySlotName("Material_MetalWire") || FindAttachmentBySlotName("Material_Shelter_Sticks") )
			return true;
		else 
			return false;
	}

	bool HasMetalParts()
	{
		if (GetConstruction().IsPartConstructed("e_outer_lower_plate") || GetConstruction().IsPartConstructed("e_outer_upper_plate") || GetConstruction().IsPartConstructed("g_inner_lower_plate") || GetConstruction().IsPartConstructed("g_inner_upper_plate") )
			return true;
		else 
			return false;
	}

	override bool CanDisplayAttachmentCategory(string category_name) 
	{	
		if (category_name == "Base" && !HasBase())
			return true;
		else if (category_name == "Material" && HasBase() && GetConstruction().IsPartConstructed("a_base") && !FullyConstructed())
			return true;
		else if (category_name == "Material" && FullyConstructed() && HasMaterialAttachments())
			return true;
		else if (category_name == "Attachments" && GetConstruction().IsPartConstructed("i_hindges"))
			return true;
		else
			return false;
    }
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		
		//write
		ctx.Write(m_GateState);
		ctx.Write(m_IsOpened);
		bsbDebugPrint("[bsb] OnStoreSave - build=" + m_GateState + " opened=" + m_IsOpened);
	}
	
	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		//--- Fence data ---
		//has gate
		if (version < 110)
		{
			if (!ctx.Read(m_ToDiscard))
			{
				m_ToDiscard = false;
				return false;
			}
			m_GateState = GATE_STATE_NONE;
		}
		else if (!ctx.Read(m_GateState))
		{
			m_GateState = GATE_STATE_NONE;
			return false;
		}
		
		//is opened
		if (!ctx.Read(m_IsOpened))
		{
			m_IsOpened = false;
			return false;
		}
		
		bsbDebugPrint("[bsb] OnStoreLoad - build=" + m_GateState + " opened=" + m_IsOpened);
		//---
		
		return true;
	}
	
	override void OnPartBuiltServer(notnull Man player, string part_name, int action_id)
	{
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart(part_name);
		
		super.OnPartBuiltServer(player, part_name, action_id);
		
		SetGateState(CheckGateState());
		
		//drop attachments without carrier part
		if (constrution_part.IsGate())
			//GateAttachmentsSanityCheck();
		
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void OnPartDismantledServer(notnull Man player, string part_name, int action_id)
	{
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart(part_name);
		
		//check gate state
		if (constrution_part.IsGate())
		{
		#ifdef CodeLock
			CodeLock codelock = CodeLock.Cast(GetCodeLock());
			if (IsCodeLocked() && BreakCodeLock == 0) 
			{
				
				codelock.UnlockServer(player, this);
			}
			if(IsCodeLocked() && BreakCodeLock == 1)
			{
				codelock.SetHealth("", "", 0);
				codelock.UnlockServer(player, this);
			}
		#endif
			
			if (IsLocked())
			{
				CombinationLock combination_lock = CombinationLock.Cast(FindAttachmentBySlotName(ATTACHMENT_SLOT_COMBINATION_LOCK));
				combination_lock.UnlockServer(player , this);
			}
		}
		
		super.OnPartDismantledServer( player, part_name, action_id );
		
		SetGateState(CheckGateState());
		
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void OnPartDestroyedServer(Man player, string part_name, int action_id, bool destroyed_by_connected_part = false)
	{
		super.OnPartDestroyedServer(player, part_name, action_id);
		
		Construction construction = GetConstruction();
		
		//check gate state
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart(part_name);

		if (constrution_part.IsGate() && destroyed_by_connected_part) //avoids attachment dropping on regular hinges destruction
		{
			//drop regular attachments
			HandleDropAttachment(GetCombinationLock());
			
			//rotate back to place
			if (IsOpened())
				CloseFence();
		}

		if (part_name == "b_lower_frame")
		{
			HandleDropAttachment(GetCombinationLock());
		}

		if (part_name == "b_upper_frame")
		{
			HandleDropAttachment(GetCombinationLock());
		}

	#ifdef CodeLock
		if (constrution_part.IsGate() && destroyed_by_connected_part)
		{
            CodeLock codelock = GetCodeLock();
            if (codelock && BreakCodeLock == 0)
            {
                codelock.NewUnlockServer(null, this);
				HandleDropAttachment(GetCodeLock());
            }
			else if(codelock && BreakCodeLock == 1)
			{
				codelock.NewUnlockServer(null, this);
				codelock.SetHealth(0);
				HandleDropAttachment(GetCodeLock());
				
			}
        }
	#endif
		
	#ifdef EXPANSIONMODBASEBUILDING
		if (constrution_part.IsGate() && destroyed_by_connected_part)
		{
            ExpansionCodeLock Ecodelock = ExpansionGetCodeLock();
            if (Ecodelock && BreakCodeLock == 0)
            {
                Ecodelock.ExpansionUnlock();
				HandleDropAttachment(ExpansionGetCodeLock());
            }
			else if(Ecodelock && BreakCodeLock == 1)
			{
				Ecodelock.ExpansionUnlock();
				Ecodelock.SetHealth(0);
				HandleDropAttachment(ExpansionGetCodeLock());
				
			}
        }
	#endif
		
		SetGateState(CheckGateState());
		//update visuals (server)
		UpdateVisuals();
	}

	override bool HasProperDistance(string selection, PlayerBase player)
	{
		if (MemoryPointExists(selection))
		{
			vector selection_pos = ModelToWorld(GetMemoryPointPos(selection));
			float distance = vector.Distance(selection_pos, player.GetPosition());
			if (distance >= MAX_ACTION_DETECTION_DISTANCE)
				return false;
		}
		
		return true;
	}

	override void AfterStoreLoad()
	{	
		super.AfterStoreLoad();
		
		//set gate state
		ConstructionPart gate_part = GetConstruction().GetGateConstructionPart();
		SetGateState(CheckGateState());
		
		//update gate state visual
		if (IsOpened())
			OpenFence();
		
		UpdateVisuals();
		
		bsbDebugPrint("[bsb] AfterStoreLoad - build=" + gate_part.IsBuilt() + " opened=" + IsOpened());
	}	
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();

		if (m_IsOpenedClient != m_IsOpened)
		{
			m_IsOpenedClient = m_IsOpened;
			
			if (m_IsOpenedClient)
				OpenFence();
			else
				CloseFence();
		}

		if (m_SoundRattleClient == -1) //First Sync don't play sound
			m_SoundRattleClient = m_SoundRattle;

		if (m_SoundRattleClient != m_SoundRattle) //Local state doesn't equal server state play sound
			PlayRattleSound();
	}

	override bool CanOpenFence()
	{
		if (HasHinges() && !IsOpened() && !IsLocked())
			return true;
		
		return false;
	}
	
	override bool CanCloseFence()
	{
		if (HasHinges() && IsOpened())
			return true;
		
		return false;
	}
	
	override void OpenFence()
	{
		//server or single player
		if (GetGame().IsServer())
		{
			float value = GATE_ROTATION_ANGLE_DEG;
			SetAnimationPhase("Wall_Interact_Rotate", value);
			SetAnimationPhase("Wall_Base_Down_Rotate", value);
			SetAnimationPhase("Wall_Base_Up_Rotate", value);
			SetAnimationPhase("Wall_Wood_Down_Rotate", value);
			SetAnimationPhase("Wall_Wood_Up_Rotate", value);
			SetAnimationPhase("Wall_Metal_Down_Rotate", value);
			SetAnimationPhase("Wall_Metal_Up_Rotate", value);

			SetAnimationPhase("Wall_Rotate", value);
			SetAnimationPhase("Wall2_Rotate", value);
			SetAnimationPhase("Wall3_Rotate", value);
			SetAnimationPhase("Wall4_Rotate", value);
			SetAnimationPhase("Wall5_Rotate", value);
			SetAnimationPhase("Wall6_Rotate", value);
			SetAnimationPhase("Wall7_Rotate", value);
			
			SetOpenedState(true);
			
			//regenerate navmesh
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false);
			
			//synchronize
			SynchronizeBaseState();
		}
		
		//client or single player
		if (!GetGame().IsDedicatedServer())
			SoundGateOpenStart(); //play sound
		
		//remove BarbedWire AreaDamageTrigger
		//UpdateBarbedWireAreaDamagePos(0,true);
		
		//add check
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(CheckFenceClosed);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckFenceOpened, 0, true);
	}

	override void CloseFence()
	{
		//server or single player
		if (GetGame().IsServer())
		{
			float value = 0;
			SetAnimationPhase("Wall_Interact_Rotate", value);
			SetAnimationPhase("Wall_Base_Down_Rotate", value);
			SetAnimationPhase("Wall_Base_Up_Rotate", value);
			SetAnimationPhase("Wall_Wood_Down_Rotate", value);
			SetAnimationPhase("Wall_Wood_Up_Rotate", value);
			SetAnimationPhase("Wall_Metal_Down_Rotate", value);
			SetAnimationPhase("Wall_Metal_Up_Rotate", value);
			
			SetAnimationPhase("Wall_Rotate", value);
			SetAnimationPhase("Wall2_Rotate", value);
			SetAnimationPhase("Wall3_Rotate", value);
			SetAnimationPhase("Wall4_Rotate", value);
			SetAnimationPhase("Wall5_Rotate", value);
			SetAnimationPhase("Wall6_Rotate", value);
			SetAnimationPhase("Wall7_Rotate", value);

			SetOpenedState(false);
			
			//regenerate navmesh
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false);
			
			//synchronize
			SynchronizeBaseState();
		}
		
		//client or single player
		if (!GetGame().IsDedicatedServer())
		{
			//play sound
			SoundGateCloseStart();
		}
		
		//remove BarbedWire AreaDamageTrigger
		//UpdateBarbedWireAreaDamagePos(0,true);
		
		//add check
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(CheckFenceOpened);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckFenceClosed, 0, true);
	}

	protected void CheckFenceOpened()
	{
		if (GetAnimationPhase("Wall7_Rotate") == GATE_ROTATION_ANGLE_DEG) //animation finished - open
		{
			//UpdateBarbedWireAreaDamagePos(GetAnimationPhase("Wall_Gate_Rotate"));
			//remove check
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(CheckFenceOpened);
		}
	}

	protected void CheckFenceClosed()
	{
		if (GetAnimationPhase("Wall7_Rotate") == 0)	//animation finished - closed
		{
			//client or single player
			if (!GetGame().IsDedicatedServer())
			{
				//play sound
				SoundGateCloseEnd();
			}
			//UpdateBarbedWireAreaDamagePos(GetAnimationPhase( "Wall_Gate_Rotate" ));
			//remove check
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(CheckFenceClosed);
		}
	}

	override bool CanUseConstructionBuild()
	{
		return !IsOpened();
	}
	
	protected void SoundGateOpenStart()
	{
		//client or single player
		if (!GetGame().IsDedicatedServer())
			PlaySoundSet(m_SoundGate_Start, SOUND_GATE_OPEN_START, 0.1, 0.1);
	}

	protected void SoundGateCloseStart()
	{
		//client or single player
		if (!GetGame().IsDedicatedServer())
			PlaySoundSet(m_SoundGate_Start, SOUND_GATE_CLOSE_START, 0.1, 0.1);
	}

	protected void SoundGateCloseEnd()
	{
		//client or single player
		if (!GetGame().IsDedicatedServer())
			PlaySoundSet(m_SoundGate_End, SOUND_GATE_CLOSE_END, 0.1, 0.1);
	}
	
	override void PlayRattleSound()
	{
		//if its the server toggle state
		if (GetGame().IsDedicatedServer())
		{
			m_SoundRattle = !m_SoundRattle;
			SetSynchDirty(); //Sync with clients
		}

		m_SoundRattleClient = m_SoundRattle; //Set Local state
		if (!GetGame().IsDedicatedServer())
		{
			if (HasMetalParts())
				PlaySoundSet(m_SoundGate_End, SOUND_RATTLE_METAL, 0.1, 0.1);
			else
				PlaySoundSet(m_SoundGate_End, SOUND_RATTLE_WOOD, 0.1, 0.1);			
		}
	}
	
	//void GateAttachmentsSanityCheck()
	//{
	//	ConstructionPart wall_base_down = GetConstruction().GetConstructionPart("wall_base_down");
	//	ConstructionPart wall_base_up = GetConstruction().GetConstructionPart("wall_base_up");
	//	if(GetBarbedWire1() && !wall_base_down.IsBuilt())
	//	{
	//		HandleDropAttachment(GetBarbedWire1());
	//		HandleDropAttachment(GetCombinationLock());
	//	}
	//	if( ( GetCamoNet() || GetBarbedWire2() ) && !wall_base_up.IsBuilt() )
	//	{
	//		HandleDropAttachment(GetBarbedWire2());
	//		HandleDropAttachment(GetCamoNet());
	//		HandleDropAttachment(GetCombinationLock());
	//	}
	//}
	
	void HandleDropAttachment(ItemBase item)
	{
		BarbedWire wire;
		CombinationLock lock;
		if (Class.CastTo(wire,item)) //special barbed wire beh.
		{
			wire.SetMountedState( false );
			GetInventory().DropEntity(InventoryMode.SERVER, this, wire);
		}
		else if (Class.CastTo(lock,item))
		{
			lock.UnlockServer(null,this);
		}
		else if (item)//generic behaviour
		{
			GetInventory().DropEntity(InventoryMode.SERVER, this, item);
		}
	}
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionFoldBaseBuildingObject);
	#ifndef EXPANSIONMODBASEBUILDING
		AddAction(ActionOpenBuildingCore);
		AddAction(ActionCloseBuildingCore);
	#endif
	#ifdef CodeLock
	    AddAction(ActionManageLockOnDoor);
	    AddAction(ActionLockAdminOnFence);
	#endif
	}

#ifdef EXPANSIONMODBASEBUILDING
	override void Close()
	{
		CloseFence();
	}

	override void Open()
	{
		OpenFence();
	}
#endif
};