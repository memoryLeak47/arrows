package network;

import network.sendable.Event;
import core.menu.menues.GameInterface;
import core.menu.menues.LobbyMenu;
import core.Main;

public abstract class NetworkDevice // server or client
{

	public void onEvent(Event event)
	{
		// TODO
	}

	public final void tick() // calledby Main.run()
	{
		if (Main.getActiveMenu() instanceof GameInterface)
		{
			gameTick();
		}
		else if (Main.getActiveMenu() instanceof LobbyMenu)
		{
			lobbyTick();
		}
		else
		{
			System.out.println("ERROR: NetworkDevice.tick() - NetworkDevice created, but Menu != GameInterface and Menu != LobbyMenu");
			System.exit(1);
		}
	}

	public abstract void lobbyTick();
	public abstract void gameTick();
}
