package game;

import java.util.LinkedList;

import game.Entity;
import game.Bullet;
import network.packets.EventPacket;
import network.PlayerInfo;

public class Player extends Entity
{
	private PlayerInfo info;
	private int team; // team == 0: all players are enemies
	private LinkedList<Bullet> bullets;

	public void onEvent(EventPacket event)
	{
		// TODO
	}
}
