package network;

import java.net.DatagramSocket;
import java.lang.Thread;

import network.NetworkDevice;
import network.sendable.Event;

public class Client extends NetworkDevice
{
	DatagramSocket socket;

	public void onEvent(Event event)
	{
		// sends to Server
	}

	@Override
	public void lobbyTick()
	{
		// TODO
	}

	@Override
	public void gameTick() {}

	static class ClientReceiver extends Thread
	{
		public void run()
		{
			while (true)
			{
				// TODO: receive
				// TODO: render
			}
		}
	}
}
