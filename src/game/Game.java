package game;

import java.util.LinkedList;

import game.Player;
import game.TileMap;

public class Game
{
	private LinkedList<Player> players;
	private TileMap tileMap;

	public void tick()
	{
		for (int i = 0; i < players.size(); i++)
		{
			players.get(i).tick();
		} 
	}

	// TODO: public void render()???
}
