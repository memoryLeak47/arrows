package network;

import core.Main;

public abstract class NetworkDevice
{
	public void onEvent(/*TODO: Event event*/)
	{
	}

	public final void tick() // calledby Main.run()
	{
		/*
		if (Main.getMenu() instanceof GameInterface)
		{
			gameTick();
		}
		else if (Main.getMenu() instanceof LobbyMenu)
		{
			lobbyTick();
		}
		else
		{
			System.out.println("ERROR: NetworkDevice.tick() - NetworkDevice created, but Menu != GameInterface and Menu != LobbyMenu");
			System.exit();
		}
		*/
	}

	public abstract void lobbyTick();
	public abstract void gameTick();
}
