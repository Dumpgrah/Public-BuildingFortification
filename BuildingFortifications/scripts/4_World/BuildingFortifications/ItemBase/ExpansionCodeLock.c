#ifdef EXPANSIONMODBASEBUILDING
modded class ExpansionCodeLock
{
	override protected void UpdateVisuals_Deferred()
	{
		super.UpdateVisuals_Deferred();

		ItemBase parent = ItemBase.Cast(GetHierarchyParent());

		//! Building Fortifications compat
		if (parent && parent.IsKindOf("BF_DoorBarricade"))
		{
			HideSelection( "camo" );
			HideSelection( "Codelock" );
			ShowSelection( "attach_fence" );
		}
	}
};
#endif