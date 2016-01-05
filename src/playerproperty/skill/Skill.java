package playerproperty.skill;

import playerproperty.PlayerProperty;
import playerproperty.skill.skills.normal.*;
//import playerproperty.skill.skills.hold.*;
//import playerproperty.skill.skills.toggle.*;
import graphics.ImageID;
import misc.Debug;

public abstract class Skill extends PlayerProperty
{
	public static final float MAX_CHARGE = 100;
	public static final byte SKILLS_SIZE = 4;

	private float charge;

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

	public void tick()
	{
		if (isRecharging())
		{
			setCharge(getCharge() + getRecharge());
		}
	}

	public void onKeyPressed() { }
	public void onKeyReleased() { }

	protected abstract void onTrigger(); // Wird nach trigger ausgeführt (resetet charges)
	protected abstract void trigger(); // wird aufgerufen, wenn der Skill eingesetzt wird

	// getter
	public static Skill getByID(byte id)
	{
		if (id >= 0 && id < skills.length)
		{
			return skills[id];
		}
		Debug.warn("Skill.getByID(" + id + "): skill not found");
		return null;
	}

	public float getCharge() { return charge; }

	@Override public final byte getID() { return id; }
	public static Skill[] getAllSkills() { return skills; }

	protected abstract boolean isRecharging();
	protected float getRecharge() { return 1.0f; }

	// setter
	protected final void setCharge(float c)
	{
		if (c > MAX_CHARGE)
		{
			charge = MAX_CHARGE;
		}
		else if (c < 0.0f)
		{
			charge = 0.0f;
		}
		else
		{
			charge = c;
		}
	}
}
