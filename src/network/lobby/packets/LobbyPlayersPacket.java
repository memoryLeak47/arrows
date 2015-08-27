package network.lobby.packets;

import java.util.LinkedList;

import network.Packet;
import network.lobby.LobbyPlayer;

public class LobbyPlayersPacket extends Packet // sent from server to client as answer to LoginUserPacket, to give him the current state of the lobby
{
	private LinkedList<LobbyPlayer> players;
}
