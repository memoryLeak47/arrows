package playerproperty.skill;

import core.game.Game;
import core.game.ServerGame;
import graphics.ImageID;
import misc.Debug;
import playerproperty.PlayerProperty;
import playerproperty.skill.skills.normal.*;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import network.game.player.ServerGamePlayer;
//import playerproperty.skill.skills.hold.*;
//import playerproperty.skill.skills.toggle.*;

public abstract class Skill extends PlayerProperty implements Cloneable
{
	public static final float MAX_CHARGE = 100;
	public static final byte SKILLS_SIZE = 4;

	private ServerGamePlayer player;

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

	protected final void addBullet(ExtendedBullet bullet)
	{
		Debug.warnIf(bullet == null, "Skill.addBullet(): bullet == null");
		((ServerGame) Game.get()).addBullet(bullet);
	}

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

	public static Skill createByID(byte id, ServerGamePlayer player)
	{
		if (id >= 0 && id < skills.length)
		{
			try
			{
				Skill skill = (Skill) skills[id].clone();
				skill.setPlayer(player);
				return skill;
			} catch (Exception e)
			{
				Debug.error("Skill.createByID(): can't clone Skill");
			}
		}
		Debug.warn("Skill.createByID(" + id + "): skill not found");
		return null;
	}

	protected ServerGamePlayer getPlayer() { return player; }

	public float getCharge() { return charge; }

	@Override public final byte getID() { return id; }
	public static Skill[] getAllSkills() { return skills; }

	protected abstract boolean isRecharging();
	protected float getRecharge() { return 1.0f; }

	// setter
	private void setPlayer(ServerGamePlayer player)
	{
		Debug.warnIf(player == null, "Skill.setPlayer(): player == null");
		this.player = player;
	}

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
