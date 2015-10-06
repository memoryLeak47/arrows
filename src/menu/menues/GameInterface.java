package menu.menues;

import java.util.LinkedList;

import core.Main;
import game.tilemap.LobbyTileMap;
import menu.NetworkingMenu;
import network.lobby.LobbyPlayer;
import network.Packet;

public abstract class GameInterface extends NetworkingMenu
{
	public GameInterface(LobbyTileMap map, LinkedList<LobbyPlayer> lobbyPlayers)
	{
		
	}
}
