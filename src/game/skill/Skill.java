package game.skill;

import game.skill.skills.*;
import game.graphics.ImageID;
import misc.Debug;

public abstract class Skill
{
	private byte id;
	private static Skill[] skills;

	static
	{
		skills = new Skill[]
		{
			new Arrow()
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

	public final byte getID() { return id; }

	public abstract ImageID getIconImageID();
	public abstract int getMaxCooldown();
	public abstract String getDescription();
}
