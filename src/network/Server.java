package network;

import java.net.*;
import java.util.Map;
import java.net.InetAddress;
import java.lang.Thread;

import game.Player;
import game.Game;
import network.game.packets.EventPacket;
import network.Packet;

public class Server extends NetworkDevice
{
	private DatagramSocket socket;
	private Map<InetAddress, Player> IPtoPlayer;
	private Game game;

	public Server()
	{
		// TODO: init
	}

	public void onEvent(EventPacket event)
	{
		// TODO: manipulates server-player
	}

	@Override public void handlePacket(Packet packet, InetAddress ip)
	{
		
	}

	@Override public void lobbyTick()
	{
		// TODO
	}

	@Override public void gameTick()
	{
		game.tick();
		send();
	}

	private void send()
	{
		// sends image of Game to all clients (player-specific)
	}
}
