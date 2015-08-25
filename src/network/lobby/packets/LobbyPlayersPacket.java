package network.lobby.packets;

import java.util.LinkedList;

import network.Packet;
import network.lobby.LobbyPlayer;

public class LobbyPlayersPacket implements Packet
{
	private LinkedList<LobbyPlayer> players;
}
