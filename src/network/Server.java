package network;

import java.net.DatagramSocket;
import java.util.Map;
import java.net.InetAddress;
import java.lang.Thread;

import game.Player;
import game.Game;
import network.sendable.Event;

public class Server extends NetworkDevice
{
	DatagramSocket socket;
	Map<InetAddress, Player> IPtoPlayer;
	Game game;

	public Server()
	{
		// TODO: init
	}

	public void onEvent(Event event)
	{
		// TODO: manipulates server-player
	}

	@Override
	public void lobbyTick()
	{
		// TODO
	}

	@Override
	public void gameTick()
	{
		game.tick();
		send();
	}

	void send()
	{
		// sends image of Game to all clients (player-specific)
	}

	static class ServerReceiver extends Thread
	{
		public void run()
		{
			/* TODO: void run()
				receives Event from client
				tells it game
			*/
		}
	}
}
