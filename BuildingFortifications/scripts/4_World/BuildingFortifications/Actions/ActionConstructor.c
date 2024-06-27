modded class ActionConstructor 
{
    override void RegisterActions(TTypenameArray actions)
    {	
		super.RegisterActions(actions);
		actions.Insert(ActionOpenBuildingCore);
		actions.Insert(ActionCloseBuildingCore);
		actions.Insert(ActionDestroyBFPart);
		actions.Insert(ActionBFTurnAroundKit);
		
		#ifdef CodeLock
		actions.Insert(ActionManageLockOnDoor);
		actions.Insert(ActionAttachCodeLockToDoor);
		actions.Insert(ActionLockAdminOnBFDoor);
		actions.Insert(ActionDestroyCodeLockOnBFDoor);
		#endif
    }
};