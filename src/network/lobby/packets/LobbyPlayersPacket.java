package network.lobby.packets;

import java.util.LinkedList;

import misc.compress.*;
import network.Packet;
import player.LobbyPlayer;

public class LobbyPlayersPacket extends Packet // sent from server to client as answer to LoginUserPacket, to give him the current state of the lobby
{
	private LinkedList<LobbyPlayer> players;

	public LobbyPlayersPacket(LinkedList<LobbyPlayer> players)
	{
		this.players = players;
	}

	public LinkedList<LobbyPlayer> getPlayers() { return players; }

	public LobbyPlayersPacket(CompressBuffer buffer)
	{
		players = (LinkedList<LobbyPlayer>) buffer.cutListByCID(Compressor.LOBBY_PLAYER_CID);
	}

	@Override public byte getCID() { return Compressor.LOBBY_PLAYERS_PACKET_CID; }
	@Override public byte[] compress()
	{
		return Compressor.compressList(getPlayers());
	}
}
