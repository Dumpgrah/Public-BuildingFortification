#ifdef CodeLock
class ActionManageLockOnDoor : ActionManageLockOnFence 
{
	
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        BuildingFortficationsCore fence = BuildingFortficationsCore.Cast(target.GetObject());
        CodeLock codelockRS;

        if (fence && !fence.IsOpened()) {
            if (!GetDayZGame().GetCodeLockConfig().CanOpenAnywhere()) {
                string selection = fence.GetActionComponentName(target.GetComponentIndex());

                if (selection != "door_interact") 
				{
                    return false;
                }
            }
            codelockRS = CodeLock.Cast(fence.GetCodeLockRS());

            if (codelockRS) 
			{
                bool isOwner = codelockRS.IsOwner(player.GetIdentity().GetId());
                bool isGuest = codelockRS.IsGuest(player.GetIdentity().GetId());
                
                if (codelockRS.GetLockState()) 
				{
                    if (isOwner) {
                        lockState = "Manage Lock";
                        return true;
                    } else if (codelockRS.HasNoOwner()) {
                        lockState = "Claim Ownership";
                        return true;
                    }
                }
            }
        }
        return false;
    }


    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        BuildingFortficationsCore fence = BuildingFortficationsCore.Cast(action_data.m_Target.GetObject());
        CodeLock codelockRS;

        if (fence) {
            codelockRS = CodeLock.Cast(fence.GetCodeLockRS());

            if (codelockRS) {
                if (codelockRS.GetLockState()) {
                    if (codelockRS.IsOwner(identity.GetId())) {
                        GetCLUIManager().ShowMenu(CLMENU.ENTER_CODE_MENU, fence);
                    } else if (codelockRS.HasNoOwner()) {
                        GetCLUIManager().ShowMenu(CLMENU.CLAIM_CODE_MENU, fence);
                    }
                }
            }
        }
    }

}

class ActionAttachCodeLockToDoor : ActionAttachCodeLockToFence {
	
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        BuildingFortficationsCore fence = BuildingFortficationsCore.Cast(target.GetObject());

        if (fence) {
            if (!fence.HasFullyConstructedGate()) {
                return false;
            }
            if (!GetDayZGame().GetCodeLockConfig().CanAttachToGates()) {
                return false;
            }
            if (!fence.IsCodeLocked()) {
                return true;
            }
        }
        return false; 
    }

    override void OnExecuteClient(ActionData action_data) {
        BuildingFortficationsCore fence = BuildingFortficationsCore.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

		ClearInventoryReservationEx(action_data);

        if (fence) {
            int slotID = InventorySlots.GetSlotIdFromString(CLConst.clAttachment);

            action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx(fence, action_data.m_MainItem, slotID);
            GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, fence);
        }
    }

    override void OnExecuteServer(ActionData action_data) {
        BuildingFortficationsCore fence = BuildingFortficationsCore.Cast(action_data.m_Target.GetObject());
        PlayerIdentity playerId = action_data.m_Player.GetIdentity();

        if (fence) {
            GetCodeLockLogger().WriteLog("attach", playerId, fence.GetPosition());
        }
    }
}
class ActionLockAdminOnBFDoor : ActionLockAdminOnFence 
{
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) 
	{
        BuildingFortficationsCore DB = BuildingFortficationsCore.Cast(target.GetObject());
        CodeLock codelockRS;

        if (DB && !DB.IsOpened()) {
            codelockRS = CodeLock.Cast(DB.GetCodeLockRS());

            if (codelockRS) {
                if (codelockRS.GetLockState()) {
                    if (GetCLPermissionManager().UserIsAdmin(player.GetIdentity().GetPlainId())) {
                        lockState = "Admin Lock";
                        return true;
                    }
                }
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        BuildingFortficationsCore DB = BuildingFortficationsCore.Cast(action_data.m_Target.GetObject());
        CodeLock codelockRS;

        if (DB) 
		{
            codelockRS = CodeLock.Cast(DB.GetCodeLockRS());

            if (codelockRS) 
			{
                if (codelockRS.GetLockState()) 
				{
                    if (GetCLPermissionManager().UserIsAdmin()) 
					{
                        GetCLUIManager().ShowMenu(CLMENU.ADMIN_CODE_MENU, DB);
                    }
                }
            }
        }
    }
}
class ActionDestroyCodeLockOnBFDoor : ActionDestroyCodeLockOnFence 
{


    void ActionDestroyCodeLockOnBFDoor() 
	{
        m_CallbackClass = ActionDestroyCodeLockOnFenceCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_DISASSEMBLE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
        m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_MEDIUM;
        m_FullBody = true;
    }
	
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        BuildingFortficationsCore fence = BuildingFortficationsCore.Cast(target.GetObject());
        CodeLock codelockRS;

        _Health = 0;
        _maxHealth = 0;

        if (fence) {
            codelockRS = CodeLock.Cast(fence.GetCodeLockRS());

            if (codelockRS && GetDayZGame().GetCodeLockConfig().CanRaidGates()) {
                _Health = codelockRS.GetSynchronizedHealth();
                _maxHealth = codelockRS.GetMaxHealth("", "Health");
                return true;
            }
        }
        return false;
    }

    override void OnFinishProgressServer(ActionData action_data) 
	{
		CodeLock codelockRS;
        if (!GetDayZGame().GetCodeLockConfig().CanRaidGates()) { return; }

        BuildingFortficationsCore fence = BuildingFortficationsCore.Cast(action_data.m_Target.GetObject());
        float raidIncrementAmount = _maxHealth / GetDayZGame().GetCodeLockConfig().GetIncrementAmount();
        int toolDamage = GetDayZGame().GetCodeLockConfig().GetToolDamageonRaid();

        if (fence) 
		{
            codelockRS = CodeLock.Cast(fence.GetCodeLockRS());

            if (codelockRS) {
                codelockRS.AddHealth("", "Health", -raidIncrementAmount);

                float _Health = codelockRS.GetHealth();

                codelockRS.SetSynchronizedHealth(_Health);

                if (_Health > 0) {
                    GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), codelockRS.GetPosition(), "", false, false, raidIncrementAmount, _Health);
                } 
				else if (codelockRS)
				{
					
                    codelockRS.NewUnlockServer(action_data.m_Player, fence);

                    if (GetDayZGame().GetCodeLockConfig().DeleteLockonRaid()) {
                        codelockRS.Delete();
                    }
                    if (toolDamage > 0) {
                        action_data.m_MainItem.DecreaseHealth(toolDamage, false);
                    }
                    GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), codelockRS.GetPosition(), "", false, true);
                }
            }
        }
    }

    override string GetAdminLogMessage(ActionData action_data) {
        return " destroyed CodeLock on " + action_data.m_Target.GetObject().GetDisplayName() + " at " + action_data.m_Player.GetPosition();
    }
}
modded class CodeLock : ItemBase
{

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionAttachCodeLockToDoor);
    }
};
#endif