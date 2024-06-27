modded class SledgeHammer
{
	/*override bool IsMeleeFinisher()
	{
		return true;
	}*/
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionDestroyBFPart);
	}
}
#ifdef CodeLock
modded class Hacksaw
{
    override void SetActions()
	{
		super.SetActions();

        AddAction(ActionDestroyCodeLockOnBFDoor);
    }
}
#endif