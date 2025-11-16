class BuildingFortficationsCore extends BaseBuildingBase
{
	const float MAX_FLOOR_VERTICAL_DISTANCE 		= 0.5;
	const float MIN_ACTION_DETECTION_ANGLE_RAD 		= 0.35;		//0.35 RAD = 20 DEG
	const float MAX_ACTION_DETECTION_DISTANCE 		= 2.0;		//meters
	const float MAX_ACTION_DETECTION_ANGLE_RAD 		= 1.3;		//1.3 RAD = ~75 DEG
	
	protected int m_GateState 				= 0;
	const int GATE_STATE_NONE 				= 0;
	const int GATE_STATE_PARTIAL 			= 1;
	const int GATE_STATE_FULL 				= 2;
	
	float GetDmgPercentage(int damageType)
	{		
		return 1.0;
	}	
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		
		int DisableDmg = GetBuildingFortificationsConfig().Disable_Base_Damage;
		//Print(DisableDmg);
		if (GetGame().IsServer() && DisableDmg < 1)
		{
			PlayerBase player;
			string tool = "";
			float distance = 0;		
			if (source)
			{
				distance = vector.Distance(this.GetPosition(), source.GetPosition());
				tool = source.GetType();
				player = PlayerBase.Cast(source.GetHierarchyRootPlayer());
			
				array<string> FullZonesList = new array<string>;
				GetDamageZones(FullZonesList);
				int i;
				for (i = 0; i < FullZonesList.Count(); i++)
	
				float zoneDmg = damageResult.GetDamage(FullZonesList.Get(i), "Health");
				string zoneName = FullZonesList.Get(i);
				float beforeHealth = GetHealth(zoneName, "Health");
				if (zoneDmg > 0)
				{
					float HealBackAmount = zoneDmg - (zoneDmg * GetDmgPercentage(damageType));
					
					float resultingDamage = zoneDmg;
					if (HealBackAmount > 0 && beforeHealth >= 10)
					{
						if (HealBackAmount > zoneDmg)
						{
							HealBackAmount = zoneDmg;
						}
						AddHealth(zoneName, "Health", HealBackAmount);
						resultingDamage = zoneDmg - HealBackAmount;
					}

					int EnableLogging = GetBuildingFortificationsConfig().Enable_Destroy_Logs;
					if(EnableLogging >= 1)
					{
						string FirstHalf = player.GetIdentity().GetName() + " (GUID: " +  player.GetIdentity().GetId() + ")" + " Shot From: " + distance + "m" + " with Weapon =: "+ source.GetDisplayName() + " at " + this.GetDisplayName();
						string SecondHalf = " Damage Done: " + resultingDamage + " To Zone Part: " + zoneName + "  Current Health: " + GetHealth(zoneName, "Health") + " at Postion: " + this.GetPosition();
						if (resultingDamage > 0)
						{
							if (player && player.GetIdentity())
							{
								GetGame().AdminLog(FirstHalf + SecondHalf);
							}
							else
							{
								GetGame().AdminLog(FirstHalf + SecondHalf);
							}
						}	
					}
				}
			}
		}
	}
	bool HasFullyConstructedGate()
	{
		return m_GateState == GATE_STATE_FULL;
	}
	
	override ItemBase FoldBaseBuildingObject()
	{
		ItemBase item = CreateConstructionKit();
		DestroyConstruction();
		return item;
	}

	override int GetMeleeTargetType()
	{
		return EMeleeTargetType.NONALIGNABLE;
	}
	
	//--- CONSTRUCTION KIT
	override ItemBase CreateConstructionKit()
	{
		ItemBase construction_kit = ItemBase.Cast(GetGame().CreateObject(GetConstructionKitType(), GetKitSpawnPosition()));
		if (m_ConstructionKitHealth > 0)
		{
			construction_kit.SetHealth(m_ConstructionKitHealth);
		}
		
		return construction_kit;
	}
	
	override vector GetKitSpawnPosition()
	{
		if (MemoryPointExists("kit_spawn_position"))
		{
			vector position;
			position = GetMemoryPointPos("kit_spawn_position");
			
			return ModelToWorld(position);
		}
		
		return GetPosition();
	}
	
	override string GetConstructionKitType()
	{
		return "WindowBarricadeKit";
	}
	
	override bool CanDisplayAttachmentSlot(string slot_name)
	{
		return true;
	}

	override bool CanDisplayAttachmentCategory(string category_name)
	{
		return true;
	}	
	
	//returns true if attachment slot position is within given range
	override bool CheckSlotVerticalDistance(int slot_id, PlayerBase player)
	{	
		return true;		
	}
	//--- ATTACHMENT & CONDITIONS
	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		//Remove super
		//if ( !super.CanReceiveAttachment(attachment, slotId) )
		//	return false;
		
		//manage action initiator (AT_ATTACH_TO_CONSTRUCTION)
		if (!GetGame().IsMultiplayer() || GetGame().IsClient())
		{
			PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
			if (player)
			{
				ConstructionActionData construction_action_data = player.GetConstructionActionData();
				//reset action initiator
				construction_action_data.SetActionInitiator(NULL);				
			}
		}
		
		//Remove conditions
		//conditions
		//if ( attachment.Type() != ATTACHMENT_WOODEN_LOG )
		//{
		//	if ( !HasBase() )
		//	{
		//		return false;
		//	}
		//}
		
		return true;
	}
	//can put into hands
	override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
	}
	
	override bool CanBeRepairedToPristine()
	{
		return true;
	}
	
	//returns true if player->mem_point position is within given range
	override bool CheckMemoryPointVerticalDistance(float max_dist, string selection, PlayerBase player)
	{
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
	// ---	
	
	override void OnPartBuiltServer(notnull Man player, string part_name, int action_id)
	{
		super.OnPartBuiltServer(player, part_name, action_id);
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void OnPartDismantledServer(notnull Man player, string part_name, int action_id)
	{
		super.OnPartDismantledServer(player, part_name, action_id);
		//update visuals (server)
		UpdateVisuals();
	}
	
	override void OnPartDestroyedServer(Man player, string part_name, int action_id, bool destroyed_by_connected_part = false)
	{
		super.OnPartDestroyedServer(player, part_name, action_id);
		//update visuals (server)
		UpdateVisuals();
	}
	
	//--- ACTION CONDITIONS
	//returns dot product of player->construction direction based on existing/non-existing reference point
	override bool IsFacingPlayer(PlayerBase player, string selection)
	{
		vector fence_pos = GetPosition();
		vector player_pos = player.GetPosition();
		vector ref_dir = GetDirection();
		
		//vector fence_player_dir = player_pos - fence_pos;
		vector fence_player_dir = player.GetDirection();
		fence_player_dir.Normalize();
		fence_player_dir[1] = 0; 	//ignore height
		
		ref_dir.Normalize();
		ref_dir[1] = 0;			//ignore height
		
		if (ref_dir.Length() != 0)
		{
			float angle = Math.Acos(fence_player_dir * ref_dir);
			
			if (angle >= MAX_ACTION_DETECTION_ANGLE_RAD)
			{
				return true;
			}
		}
		
		return false;
	}
		
	override bool IsFacingCamera(string selection)
	{
		vector ref_dir = GetDirection();
		vector cam_dir = GetGame().GetCurrentCameraDirection();
		
		//ref_dir = GetGame().GetCurrentCameraPosition() - GetPosition();
		ref_dir.Normalize();
		ref_dir[1] = 0;		//ignore height
		
		cam_dir.Normalize();
		cam_dir[1] = 0;		//ignore height
		
		if (ref_dir.Length() != 0)
		{
			float angle = Math.Acos(cam_dir * ref_dir);
			
			if (angle >= MAX_ACTION_DETECTION_ANGLE_RAD)
			{
				return true;
			}
		}

		return false;
	}

	override bool IsPlayerInside(PlayerBase player, string selection)
	{
		if (!HasProperDistance("center", player) && !HasProperDistance("center2", player) && !HasProperDistance("center3", player))
		{
			return false;
		}
		
		return true;
	}
	override bool HasProperDistance(string selection, PlayerBase player)
	{
		if (MemoryPointExists(selection))
		{
			vector selection_pos = ModelToWorld(GetMemoryPointPos(selection));
			float distance = vector.Distance(selection_pos, player.GetPosition());
			if (distance >= 1.4)
			{
				return false;
			}
		}
			
		return true;
	}
	bool HasProperDistanceDestory(string selection, PlayerBase player)
	{
		if (MemoryPointExists(selection))
		{
			vector selection_pos = ModelToWorld(GetMemoryPointPos(selection));
			float distance = vector.Distance(selection_pos, player.GetPosition());
			if (distance >= 2)
			{
				return false;
			}
		}
		return true;
	}
	/*
	Future Use for Clear Percise Building Areas
	bool IsPointInPolygon( vector point, array<vector> polygon )
    {
        float minX = polygon[0][0];
        float maxX = polygon[0][0];
        float minZ = polygon[0][2];
        float maxZ = polygon[0][2];
        float minY = polygon[0][1];
        float maxY = polygon[0][1];
        int i = 1;
        for ( i = 1 ; i < polygon.Count() ; i++ )
        {
            CataVector q = polygon[ i ];
            minX = Math.Min( q[0], minX );
            maxX = Math.Max( q[0], maxX );
            minY = Math.Min( q[1], minY );
            maxY = Math.Max( q[1], maxY );
            minZ = Math.Min( q[2], minZ );
            maxZ = Math.Max( q[2], maxZ );
        }
    
        if ( point[0] < minX || point[0] > maxX || point[2] < minZ || point[2] > maxZ || point[1] < minY || point[1] >  maxY)
        {
            return false;
        }
    
        // https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
        bool inside = false;
        int j = polygon.Count() - 1;
        for ( i = 0; i < polygon.Count() ; j = i++ )
        {
            if ( ( polygon[i][2] > point[2] ) != ( polygon[j][2] > point[2] ) && (point[0] < ( polygon[j][0] - polygon[i][0] ) * ( point[2] - polygon[i][2] ) / ( polygon[j][2] - polygon[i][2] ) + polygon[i][0]) )
            {
                inside = !inside;
            }
        }
    
        return inside;
    }
    
    vector calcVec(vector p1, vector p2) {
        float x = p2[0] - p1[0];
        float z = p2[2] - p1[2];
        return Vector( x, 0, z);
    }
    
    float dot(vector u, vector v) {
        return (u[0] * v[0]) + (u[2] * v[2]); 
    }
	*/
	void PlayRattleSound() {}
	
#ifdef EXPANSIONMODBASEBUILDING
	//! Building Fortifications compat
	bool CanCloseFence()
	{
		return false;
	}

	//! Building Fortifications compat
	bool CanOpenFence()
	{
		return false;
	}

	//! Building Fortifications compat
	override void Close()
	{
		CloseFence();
	}

	//! Building Fortifications compat
	void CloseFence()
	{
	}

	//! Building Fortifications compat
	override bool ExpansionCanClose(PlayerBase player, string selection)
	{
		if (!super.ExpansionCanClose(player, selection))
			return false;

		return CanCloseFence();
	}

	//! Building Fortifications compat
	override bool ExpansionCanOpen(PlayerBase player, string selection)
	{
		if (!super.ExpansionCanOpen(player, selection))
			return false;

		return CanOpenFence();
	}

	//! Building Fortifications compat
	override void Open()
	{
		OpenFence();
	}

	//! Building Fortifications compat
	void OpenFence() {}
#else
	bool CanOpenFence()
	{
		return true;
	}
	
	bool CanCloseFence()
	{
		return true;
	}

	void OpenFence()
	{	
		SynchronizeBaseState();
	}

	void CloseFence()
	{
		SynchronizeBaseState();
	}
#endif
	bool HasHinges()
	{
		return true;
	}
};
