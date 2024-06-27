//! BF RPC ENUMUMS
enum BF_ERPCs: ERPCs
{
	RPC_SERVER_SEND_BFCONFIG,
};

modded class DayZGame
{
    override void OnRPC(PlayerIdentity sender, Object target, int rpc_type, ParamsReadContext ctx)
    {
        super.OnRPC(sender, target, rpc_type, ctx);

        switch (rpc_type)
        {
		#ifndef SERVER
			//! Client only
			//! Recieves and set BuildingFortificationsConfig class instance from the server on the client.
			case BF_ERPCs.RPC_SERVER_SEND_BFCONFIG:
			{
				BuildingFortificationsConfig bfConfig = new BuildingFortificationsConfig();
				if (!bfConfig.OnRecive(ctx))
				{
					Error(string.Format("%1::OnRPC - Could not recive Building Fortifications config on client!"));
				}
				else
				{
					s_BuildingFortificationsConfig = bfConfig;
					Print(string.Format("%1::OnRPC - Recived Building Fortifications config on client!"));
					//s_BuildingFortificationsConfig.Debug(); //! Prints the recived BuildingFortificationsConfig data like the list of materials for each object and its parts into the script log.
				}
			    break;
			}
		#endif
        }
    }
};