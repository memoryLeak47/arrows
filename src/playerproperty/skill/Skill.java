package playerproperty.skill;

import playerproperty.PlayerProperty;
import playerproperty.skill.skills.*;
import graphics.ImageID;
import misc.Debug;

public abstract class Skill extends PlayerProperty
{
	public static final short FULL_CHARGE = 32767;
	public static final byte SKILLS_SIZE = 4;

	private short charge;

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
		Debug.warn("Skill.getByID(): skill not found");
		return null;
	}

	public short getCharge() { return charge; }

	@Override public final byte getID() { return id; }
	public static Skill[] getAllSkills() { return skills; }
}
