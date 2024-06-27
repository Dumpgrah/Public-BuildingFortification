
modded class ModItemRegisterCallbacks
{
    override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterHeavy(pType, pBehavior);
		pType.AddItemInHandsProfileIK("BF_SlottedPlank", "dz/anims/workspaces/player/player_main/player_main_2h.asi", pBehavior,							"dz/anims/anm/player/ik/two_handed/wooden_plank.anm"); 
    };
};