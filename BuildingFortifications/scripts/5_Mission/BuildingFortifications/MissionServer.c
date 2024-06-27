modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

	#ifdef SERVER
		GetBuildingFortificationsConfig();
	#endif
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player, identity);

	#ifdef SERVER
		//! Request building fortifications server configuration on client connection.
		BF_SyncBFConfig(identity);
	#endif
	}

	//! Server only
	//! Sends BuildingFortificationsConfig class instance of the server to the client.
	protected void BF_SyncBFConfig(PlayerIdentity identity)
	{
		Print(ToString() + "::SyncBFConfig - Send Building");
		BuildingFortificationsConfig config = GetBuildingFortificationsConfig();
		if (!config)
			return;

		ScriptRPC rpc = new ScriptRPC();
		//rpc.Write(config);
		config.OnSend(rpc);
		rpc.Send(null, BF_ERPCs.RPC_SERVER_SEND_BFCONFIG, true, identity);
	}
};