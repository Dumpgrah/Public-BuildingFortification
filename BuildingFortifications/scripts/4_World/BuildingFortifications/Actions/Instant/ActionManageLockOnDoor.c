#ifdef CodeLock
class ActionManageLockOnDoor : ActionManageLockOnFence 
{
	
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        BF_DoorBarricade fence = BF_DoorBarricade.Cast(target.GetObject());
        CodeLock codelock;

        if (fence && !fence.IsOpened()) {
            if (!GetDayZGame().GetCodeLockConfig().CanOpenAnywhere()) {
                string selection = fence.GetActionComponentName(target.GetComponentIndex());

                if (selection != "door_interact") 
				{
                    return false;
                }
            }
            codelock = CodeLock.Cast(fence.GetCodeLock());

            if (codelock) 
			{
                bool isOwner = codelock.IsOwner(player.GetIdentity().GetId());
                bool isGuest = codelock.IsGuest(player.GetIdentity().GetId());
                
                if (codelock.GetLockState()) 
				{
                    if (isOwner) {
                        lockState = "Manage Lock";
                        return true;
                    } else if (codelock.HasNoOwner()) {
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
        BF_DoorBarricade fence = BF_DoorBarricade.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (fence) {
            codelock = CodeLock.Cast(fence.GetCodeLock());

            if (codelock) {
                if (codelock.GetLockState()) {
                    if (codelock.IsOwner(identity.GetId())) {
                        GetCLUIManager().ShowMenu(CLMENU.ENTER_CODE_MENU, fence);
                    } else if (codelock.HasNoOwner()) {
                        GetCLUIManager().ShowMenu(CLMENU.CLAIM_CODE_MENU, fence);
                    }
                }
            }
        }
    }

}

class ActionAttachCodeLockToDoor : ActionAttachCodeLockToFence {
	
    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item) {
        BF_DoorBarricade fence = BF_DoorBarricade.Cast(target.GetObject());

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
        BF_DoorBarricade fence = BF_DoorBarricade.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;

		ClearInventoryReservationEx(action_data);

        if (fence) {
            int slotID = InventorySlots.GetSlotIdFromString(CLConst.clAttachment);

            action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx(fence, action_data.m_MainItem, slotID);
            GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, fence);
        }
    }

    override void OnExecuteServer(ActionData action_data) {
        BF_DoorBarricade fence = BF_DoorBarricade.Cast(action_data.m_Target.GetObject());
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
        BF_DoorBarricade DB = BF_DoorBarricade.Cast(target.GetObject());
        CodeLock codelock;

        if (DB) 
		{
            codelock = CodeLock.Cast(DB.GetCodeLock());

            if (codelock) 
			{
                if (codelock.GetLockState()) {
                    if (GetCLPermissionManager().UserIsAdmin(player.GetIdentity().GetPlainId())) 
					{
                        lockState = "Admin Lock Testing";
                        return true;
                    }
                }
            }
        }
		lockState = "Admin Lock Testing";
        return true;
    }

    override void OnStartClient(ActionData action_data) {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        BF_DoorBarricade fence = BF_DoorBarricade.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (fence) 
		{
            codelock = CodeLock.Cast(fence.GetCodeLock());

            if (codelock) 
			{
                if (codelock.GetLockState()) 
				{
                    if (GetCLPermissionManager().UserIsAdmin()) 
					{
                        GetCLUIManager().ShowMenu(CLMENU.ADMIN_CODE_MENU, fence);
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
        BF_DoorBarricade fence = BF_DoorBarricade.Cast(target.GetObject());
        CodeLock codelock;

        _Health = 0;
        _maxHealth = 0;

        if (fence) {
            Class.CastTo(codelock, fence.GetCodeLock());

            if (codelock && GetDayZGame().GetCodeLockConfig().CanRaidGates()) {
                _Health = codelock.GetSynchronizedHealth();
                _maxHealth = codelock.GetMaxHealth("", "Health");
                return true;
            }
        }
        return false;
    }

    override void OnFinishProgressServer(ActionData action_data) {
        if (!GetDayZGame().GetCodeLockConfig().CanRaidGates()) { return; }

        BF_DoorBarricade fence = BF_DoorBarricade.Cast(action_data.m_Target.GetObject());
        float raidIncrementAmount = _maxHealth / GetDayZGame().GetCodeLockConfig().GetIncrementAmount();
        int toolDamage = GetDayZGame().GetCodeLockConfig().GetToolDamageonRaid();

        if (fence) {
            CodeLock codelock = fence.GetCodeLock();

            if (codelock) {
                codelock.AddHealth("", "Health", -raidIncrementAmount);

                float _Health = codelock.GetHealth();

                codelock.SetSynchronizedHealth(_Health);

                if (_Health > 0) {
                    GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), codelock.GetPosition(), "", false, false, raidIncrementAmount, _Health);
                } else {
                    codelock.UnlockServer(action_data.m_Player, fence);

                    if (GetDayZGame().GetCodeLockConfig().DeleteLockonRaid()) {
                        codelock.Delete();
                    }
                    if (toolDamage > 0) {
                        action_data.m_MainItem.DecreaseHealth(toolDamage, false);
                    }
                    GetCodeLockLogger().WriteLog("RAID", action_data.m_Player.GetIdentity(), codelock.GetPosition(), "", false, true);
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