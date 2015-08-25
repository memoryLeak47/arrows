package network.lobby.packets;

import java.util.LinkedList;

import network.Packet;
import network.lobby.LobbyPlayer;

public class LobbyPlayersPacket extends Packet
{
	private LinkedList<LobbyPlayer> players;
}
