class BF_WindowBarricade extends BuildingFortficationsCore
{
	const int GATE_STATE_NONE = 0;
	const int GATE_STATE_PARTIAL = 1;
	const int GATE_STATE_FULL = 2;
	
	const string SOUND_GATE_OPEN_START = "DoorWoodTowerOpen_SoundSet";
	const string SOUND_GATE_CLOSE_START	= "DoorWoodTowerClose_start_SoundSet";
	const string SOUND_GATE_CLOSE_END = "DoorWoodTowerClose_end_SoundSet";
	const string SOUND_RATTLE_METAL	= "DG_MetalRattle_SoundSet";
	
	//gate openining
	const float GATE_ROTATION_ANGLE_DEG = 100;
	const float GATE_ROTATION_TIME_APPROX = 2000;		//ms
	
	typename ATTACHMENT_COMBINATION_LOCK = CombinationLock;
	
	protected bool m_ToDiscard = false; //for legacy OnStoreLoad handling
	protected bool m_IsOpened = false;
	protected bool m_IsOpenedClient	= false;
	protected int m_GateState = 0;
	protected bool m_SoundRattle = false;
	protected int m_SoundRattleClient = -1;
	
	protected EffectSound m_SoundGate_Start;
	protected EffectSound m_SoundGate_End;

	override float GetDmgPercentage(int damageType)
	{
		if(damageType == DT_CLOSE_COMBAT)
		{
			return GetBuildingFortificationsConfig().Window_Barricade_Melee_Dmg / 100;
		}
		else if(damageType == DT_FIRE_ARM)
		{
			return GetBuildingFortificationsConfig().Window_Barricade_FireArm_Dmg / 100;
		}
		else if(damageType == DT_EXPLOSION)
		{
			return GetBuildingFortificationsConfig().Window_Barricade_Explosives_Dmg / 100;
		}
		return 1.0;
	}
	
	void ReplaceEdibleWithNew (string typeName)
	{
		PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (player)
		{
			ReplaceEdibleWithNewLambda lambda = new ReplaceEdibleWithNewLambda(this, typeName, player);
			player.ServerReplaceItemInHandsWithNew(lambda);
		}
		else
		{
			Error("ReplaceEdibleWithNew - cannot use edible without player");
		}
	}
	
	void BF_WindowBarricade()
	{
		RegisterNetSyncVariableBool("m_IsOpened");
		RegisterNetSyncVariableInt("m_GateState");
		RegisterNetSyncVariableBool("m_SoundRattle");		
		ShowSimpleSelection("Curtain Closed", 0);
		ShowSimpleSelection("Curtain Open", 0);
		ProcessInvulnerabilityCheck(GetInvulnerabilityTypeString());
	}
	
	override bool HasHinges()
	{
		return m_GateState > GATE_STATE_NONE;
	}
	
	bool HasFullyConstructedGate()
	{
		return m_GateState == GATE_STATE_FULL;
	}

	void SetGateState(int state)
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
		if (gate_part.IsBuilt())
		{
			ConstructionPart req_part;
			array<string> req_parts = gate_part.GetRequiredParts();
			for (int i = 0; i < req_parts.Count(); i++)
			{
				req_part = GetConstruction().GetConstructionPart(req_parts.Get(i));
				if (!req_part.IsBuilt())
					break;
			}
			
			if (i != req_parts.Count())
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
	
	void SetOpenedState(bool state)
	{
		m_IsOpened = state;
	}
	
	override bool IsOpened()
	{
		return m_IsOpened;
	}
	
	override string GetConstructionKitType()
	{
		return "BF_WindowBarricadeKit";
	}
	
	override bool NameOverride(out string output)
	{
		if (m_GateState != GATE_STATE_NONE)
		{
			output = "Metal Hatch";  //changes object displayed name if in 'gate' state
			output.ToUpper();
			return true;
		}
		return false;
	}

	override void OnPartBuiltServer(notnull Man player, string part_name, int action_id)
	{
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart(part_name);
		super.OnPartBuiltServer(player, part_name, action_id);
		SetGateState(CheckGateState());
		
		//drop attachments without carrier part
		/*if (constrution_part.IsGate())
			GateAttachmentsSanityCheck();*/
		
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void OnPartDismantledServer(notnull Man player, string part_name, int action_id)
	{
		super.OnPartDismantledServer(player, part_name, action_id);
		
		SetGateState(CheckGateState());
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void OnPartDestroyedServer(Man player, string part_name, int action_id, bool destroyed_by_connected_part = false)
	{
		super.OnPartDestroyedServer(player, part_name, action_id);
		
		if(part_name =="step_four")
			CloseFence();

		SetGateState(CheckGateState());
		//update visuals (server)
		UpdateVisuals();
	}

	override void OnPartDestroyedClient(string part_name, int action_id)
	{
		if(part_name == "step_four")
			CloseFence();
				
		SetGateState(CheckGateState());
		//update visuals (server)
		UpdateVisuals();
		//play sound
		SoundDestroyStart(part_name);
	}

	override void EEItemAttached(EntityAI item, string slot_name)
	{
		super.EEItemAttached(item,slot_name);
		
		if(slot_name == "Open_Curtain")
		{
			if (item.IsKindOf("BurlapCurtain")) // any attachment but coal
			{
				ShowSimpleSelection("Curtain Closed", 0);
				ShowSimpleSelection("Curtain Open", 1);
			};
		};

		if(slot_name == "Closed_Curtain")
		{
			if (item.IsKindOf("BurlapCurtain")) // any attachment but coal
			{
				ShowSimpleSelection("Curtain Closed", 1);
				ShowSimpleSelection("Curtain Open", 0);
			};
		};
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);
		
		if (item.IsKindOf("BurlapCurtain"))
		{
			if(slot_name == "Open_Curtain")
			{
				if (item.IsKindOf("BurlapCurtain")) // any attachment but coal
				{
					ShowSimpleSelection("Curtain Closed", 0);
					ShowSimpleSelection("Curtain Open", 1);
				};
			};

			if(slot_name == "Closed_Curtain")
			{
				if (item.IsKindOf("BurlapCurtain")) // any attachment but coal
				{
					ShowSimpleSelection("Curtain Closed", 1);
					ShowSimpleSelection("Curtain Open", 0);
				};
			};

			ShowSimpleSelection("Curtain Closed", 0);
			ShowSimpleSelection("Curtain Open", 0);

		};
		
	}
	
	void ShowSimpleSelection(string selectionName, bool hide = false)
    {
        TStringArray selectionNames = new TStringArray;
        ConfigGetTextArray("simpleHiddenSelections",selectionNames);
        int selectionId = selectionNames.Find(selectionName);
        SetSimpleHiddenSelectionState(selectionId, hide);
    }
	
	bool FullyConstructed()
	{
		if(GetConstruction().IsPartConstructed("base") && GetConstruction().IsPartConstructed("step_one") && GetConstruction().IsPartConstructed("step_two") && GetConstruction().IsPartConstructed("step_three") && GetConstruction().IsPartConstructed("step_Four"))
			return true;
		else 
			return false;
	}

	bool HasMaterialAttachments()
	{
		if(FindAttachmentBySlotName("Material_Nails") || FindAttachmentBySlotName("Material_WoodenPlanks"))
			return true;
		else 
			return false;
	}
	
	override bool CanDisplayAttachmentCategory(string category_name) 
	{	
		if ( category_name == "Curtains" && HasBase() )
			return true;
		else if ( category_name == "Material" && !FullyConstructed())
			return true;
		else if ( category_name == "Material" && !FullyConstructed())
			return true;
		else if ( category_name == "Material" && HasBase() && FullyConstructed() && HasMaterialAttachments())
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
			{
				OpenFence();
			}
			else
			{
				CloseFence();
			}
		}

		//First Sync don't play sound
		if (m_SoundRattleClient == -1)
		{
			m_SoundRattleClient = m_SoundRattle;
		}
		
		//Local state doesn't equal server state play sound
		if (m_SoundRattleClient != m_SoundRattle)
		{
			PlayRattleSound();
		}
	}
	
	override bool CanOpenFence()
	{
		if (HasHinges() && !IsOpened())
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
			SetAnimationPhase("Window_Interact_Rotate", value);
			SetAnimationPhase("Metal_Plate_Upward", value);
			SetAnimationPhase("Stick_Up_Ward", value);

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
			SetAnimationPhase("Window_Interact_Rotate", value );
			SetAnimationPhase("Metal_Plate_Upward", value );
			SetAnimationPhase("Stick_Up_Ward", value );

			SetOpenedState(false);
			
			//regenerate navmesh
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(UpdateNavmesh, GATE_ROTATION_TIME_APPROX, false);
			//synchronize
			SynchronizeBaseState();
		}
		
		//client or single player
		if (!GetGame().IsDedicatedServer())
			SoundGateCloseStart(); //play sound
		
		//remove BarbedWire AreaDamageTrigger
		//UpdateBarbedWireAreaDamagePos(0,true);
		
		//add check
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(CheckFenceOpened);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckFenceClosed, 0, true);
	}

	protected void CheckFenceOpened()
	{
		if (GetAnimationPhase("Metal_Plate_Upward") == GATE_ROTATION_ANGLE_DEG)	//animation finished - open
		{
			//UpdateBarbedWireAreaDamagePos(GetAnimationPhase("Wall_Gate_Rotate"));
			//remove check
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(CheckFenceOpened);
		}
	}
	
	protected void CheckFenceClosed()
	{
		if (GetAnimationPhase("Metal_Plate_Upward") == 0) //animation finished - closed
		{
			//client or single player
			if (!GetGame().IsDedicatedServer())
			{
				//play sound
				if (this)
					SoundGateCloseEnd();
			}
			//UpdateBarbedWireAreaDamagePos(GetAnimationPhase("Wall_Gate_Rotate"));
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
			PlaySoundSet(m_SoundGate_End, SOUND_RATTLE_METAL, 0.1, 0.1);
		}
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionFoldBaseBuildingObject);
		AddAction(ActionOpenBuildingCore);
		AddAction(ActionCloseBuildingCore);		
	}

	override bool CheckMemoryPointVerticalDistance(float max_dist, string selection, PlayerBase player)
	{
		max_dist = 5;
		
		if (player)
		{
			//check vertical distance
			vector player_pos = player.GetPosition();
			vector pos;
			
			if (MemoryPointExists(selection))
			{
				pos = ModelToWorld(GetMemoryPointPos(selection));
			}
			
			if (Math.AbsFloat(player_pos[1] - pos[1]) <= max_dist)
			{
				return true;
			}
			else
			{
				return false;
			}
		}			

		return true;
	}	
};