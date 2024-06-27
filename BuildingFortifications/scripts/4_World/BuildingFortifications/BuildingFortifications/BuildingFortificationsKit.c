class BuildingFortficationsKit extends ItemBase
{
	ref protected EffectSound m_DeployLoopSound;
	protected bool m_DeployedRegularly;

	void BuildingFortficationsKit()
	{
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
		RegisterNetSyncVariableBool("m_IsDeploySound");
	}
	
	void ~BuildingFortficationsKit()
	{
		SEffectManager.DestroyEffect(m_DeployLoopSound);
	}
	
	//! Breaks the deploy action?!
	/*override bool IsBasebuildingKit()
	{
		return true;
	}*/
	
	override bool HasProxyParts()
	{
		return true;
	}
	
	override bool CanProxyObstruct()
	{
		return false;
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
		
		if (IsDeploySound())
			PlayDeploySound();
				
		if (CanPlayDeployLoopSound())
			PlayDeployLoopSound();
					
		if (m_DeployLoopSound && !CanPlayDeployLoopSound())
			StopDeployLoopSound();
		
		if (m_DeployedRegularly && IsSoundSynchRemote())
			PlayDeployFinishSound();
	}
	
	override void EEInit()
	{
		super.EEInit();
		
		UpdateVisuals();
		UpdatePhysics();
		
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Call(AssembleKit);
		}
	}
	
	override bool DisassembleOnLastDetach()
	{
		return true;
	}
	
	override void EEItemDetached(EntityAI item, string slot_name)
	{
		super.EEItemDetached(item, slot_name);

		PlayerBase player = PlayerBase.Cast(GetHierarchyRootPlayer());
		if (player && player.IsPlayerDisconnected())
			return;
		
		if (item && slot_name == "Rope")
		{
			if (GetGame().IsServer())
			{
				DisassembleKit(ItemBase.Cast(item));
				Delete();
			}
		}
	}
	
	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner) 
	{
		super.OnItemLocationChanged(old_owner, new_owner);
		
		//update visuals after location change
		UpdatePhysics();
	}
	
	override void OnEndPlacement()
	{
		m_DeployedRegularly = true;
		SoundSynchRemote();
	}
	
	override void OnPlacementCancelled(Man player)
	{
		super.OnPlacementCancelled(player);
		m_DeployedRegularly = false;
	}
	
	override bool IsDeployable()
	{
		return true;
	}
	
	override bool CanAssignAttachmentsToQuickbar()
	{
		return false;
	}
	
	override string GetDeploySoundset()
	{
		return "putDown_FenceKit_SoundSet";
	}
	
	override string GetLoopDeploySoundset()
	{
		return "Shelter_Site_Build_Loop_SoundSet";
	}

	override string GetDeployFinishSoundset()
	{
		return "Shelter_Wooden_Stick_Build_Finish_SoundSet";
	}
	
	//Update visuals and physics
	void UpdateVisuals()
	{
		SetAnimationPhase("Inventory", 0);
		SetAnimationPhase("Placing", 1);
	}
	
	void UpdatePhysics()
	{
		AddProxyPhysics("Inventory");
		RemoveProxyPhysics("Placing" );		
	}

	void PlayDeployLoopSound()
	{		
		if (!GetGame().IsDedicatedServer())
		{		
			if (!m_DeployLoopSound || !m_DeployLoopSound.IsSoundPlaying())
				m_DeployLoopSound = SEffectManager.PlaySound(GetLoopDeploySoundset(), GetPosition());
		}
	}
	
	void StopDeployLoopSound()
	{
		if (!GetGame().IsDedicatedServer())
		{
			m_DeployLoopSound.SetSoundFadeOut(0.5);
			m_DeployLoopSound.SoundStop();
		}
	}
	
	void AssembleKit()
	{
		if (!IsHologram())
			GetInventory().CreateAttachment("Rope");
	}
	
	void DisassembleKit(ItemBase item)
	{
		if (item.GetAttachmentByType(Rope))
		{
			if (!IsHologram())
			{
				ItemBase stick = ItemBase.Cast(GetGame().CreateObjectEx("WoodenStick",GetPosition(),ECE_PLACE_ON_SURFACE));
				MiscGameplayFunctions.TransferItemProperties(this, stick);
				stick.SetQuantity(2);
				Rope rope = Rope.Cast(item);
				CreateRope(rope);
			}
		}
	}
	
	void CreateRope(Rope rope)
	{
		if (!rope)
			return;
		
		InventoryLocation targetLoc = rope.GetTargetLocation();
		if (targetLoc && targetLoc.GetType() != InventoryLocationType.GROUND)
		{
			MiscGameplayFunctions.TransferItemProperties(this, rope);
			return;
		}
		
		EntityAI newRope = EntityAI.Cast(GetGame().CreateObjectEx(rope.GetType(), GetPosition(), ECE_PLACE_ON_SURFACE));
		
		if (newRope)
			MiscGameplayFunctions.TransferItemProperties(this, newRope);
		
		rope.Delete();
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionDeployObject);
	}
	
	override void RefreshPhysics()
	{
		super.RefreshPhysics();
		
		UpdatePhysics();
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		if (!super.CanReceiveAttachment(attachment, slotId))
			return false;
		
		ItemBase att = ItemBase.Cast(GetInventory().FindAttachment(slotId));
		if (att)
			return false;
		
		return true;
	}

	override string GetPlaceSoundset()
	{
		return "seachest_drop_SoundSet";
	}
	
	//! Set to false but the kits have a HeightCheckOverride ?!
	override bool DoPlacingHeightCheck()
	{
		return false;
	}
};

class BFKitLambda : ReplaceItemWithNewLambdaBase
{
	override void CopyOldPropertiesToNew(notnull EntityAI old_item, EntityAI new_item)
	{
		super.CopyOldPropertiesToNew(old_item, new_item);
	}
};