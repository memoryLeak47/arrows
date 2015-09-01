package game;

import java.util.LinkedList;

import game.Entity;
import game.Bullet;

public class Player extends Entity
{
	private Team team; // team == 0: all players are enemies
	private LinkedList<Bullet> bullets;
}
