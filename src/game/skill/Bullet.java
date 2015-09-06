package game.skill;

import game.Player;
import game.skill.Skill;

public abstract class Bullet
{
	private Skill skill;

	private Skill getSkill() { return skill; }
	private Player getOwner() { return getSkill().getOwner(); }
}
