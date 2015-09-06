package game.skill;

import java.util.LinkedList;

import game.Player;
import game.skill.Bullet;

public class Skill
{
	private Player owner;
	private LinkedList<Bullet> bullets;

	public Skill(Player owner)
	{
		this.owner = owner;
		bullets = new LinkedList<Bullet>();
	}

	public Player getOwner() { return owner; }
	public LinkedList<Bullet> getBullets() { return bullets; }
}
