package game.skill;

import game.PlayerProperty;
import game.skill.skills.*;
import graphics.ImageID;
import misc.Debug;

public abstract class Skill extends PlayerProperty
{
	private byte id;
	private static Skill[] skills;

	static
	{
		skills = new Skill[]
		{
			new ArrowShot()
		};

		for (byte i = 0; i < skills.length; i++)
		{
			skills[i].id = i;
		}
	}

	// Getter
	public static Skill getByID(byte id)
	{
		if (id >= 0 && id < skills.length)
		{
			return skills[id];
		}
		return null;
	}

	@Override public final byte getID() { return id; }
	public static Skill[] getAllSkills() { return skills; }

	// for sub
	public abstract int getMaxCooldown();
	// TODO what happens if skill is casted
}
