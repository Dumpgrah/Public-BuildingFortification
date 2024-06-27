class BF_WindowBarricadeMed extends BuildingFortficationsCore
{
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
	
	void BF_WindowBarricadeMed()
	{
		ProcessInvulnerabilityCheck(GetInvulnerabilityTypeString());
	}
	
	override string GetConstructionKitType()
	{
		return "BF_WindowBarricadeMedKit";
	}

	override void OnPartBuiltServer(notnull Man player, string part_name, int action_id)
	{
		ConstructionPart constrution_part = GetConstruction().GetConstructionPart(part_name);
		super.OnPartBuiltServer(player, part_name, action_id);
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
		super.OnPartDestroyedServer( player, part_name, action_id );
		//update visuals (server)
		UpdateVisuals();
	}

	override void OnPartDestroyedClient(string part_name, int action_id)
	{
		UpdateVisuals();
		//play sound
		SoundDestroyStart( part_name );
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
		if (category_name == "Material" && !FullyConstructed())
			return true;
		else if (category_name == "Material" && !FullyConstructed())
			return true;
		else if (category_name == "Material" && HasBase() && FullyConstructed() && HasMaterialAttachments())
			return true;
		else
			return false;
    }

	override void OnStoreSave(ParamsWriteContext ctx)
	{   
		super.OnStoreSave(ctx);
	}

	override void AfterStoreLoad()
	{
		super.AfterStoreLoad();
		UpdateVisuals();
	}

	override bool HasHinges()
	{
		return false;
	}

	override bool CanOpenFence()
	{
		return false;
	}
	
	override bool CanCloseFence()
	{
		return false;
	}

	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionFoldBaseBuildingObject);
	}
};