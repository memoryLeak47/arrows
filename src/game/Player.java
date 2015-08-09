package game;

import java.util.LinkedList;

import game.Entity;
import game.Bullet;
import network.sendable.Event;

public class Player extends Entity
{
	private int team; // team == 0: all players are enemies
	private LinkedList<Bullet> bullets;

	public void onEvent(Event event)
	{
		// TODO
	}
}
