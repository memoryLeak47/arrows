package player.property.skill;

import java.util.LinkedList;

import game.Game;
import game.ServerGame;
import graphics.ImageID;
import misc.Debug;
import player.property.PlayerProperty;
import player.property.avatar.Avatar;
import player.property.skill.skills.normal.*;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import player.ServerGamePlayer;
//import playerproperty.skill.skills.hold.*;
//import playerproperty.skill.skills.toggle.*;

public abstract class Skill extends PlayerProperty implements Cloneable
{
	public static final float MAX_CHARGE = 100;
	public static final byte SKILLS_SIZE = 4;

	private ServerGamePlayer player;

	private float charge;

	private byte id;
	private byte avatarID;
	private static Skill[] skills;

	static
	{
		skills = new Skill[]
		{
			new ArrowShotSkill(Avatar.ARCHER_ID),
			new SmokeCloudSkill(Avatar.ROGUE_ID),
			new ShadowJumpSkill(Avatar.ROGUE_ID),
			new DaggerTossSkill(Avatar.ROGUE_ID)
		};

		for (byte i = 0; i < skills.length; i++)
		{
			skills[i].id = i;
		}
	}

	public Skill(byte avatarID)
	{
		this.avatarID = avatarID;
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
			try
			{
				Skill skill = (Skill) skills[id].clone();
				return skill;
			} catch (Exception e)
			{
				Debug.error("Skill.createByID(): can't clone Skill");
			}
		}
		Debug.warn("Skill.createByID(" + id + "): skill not found", Debug.Tags.EXTENDED_WARNINGS);
		return null;
	}

	protected ServerGamePlayer getPlayer() { return player; }

	public float getCharge() { return charge; }

	@Override public final byte getID() { return id; }
	public static Skill[] getAllSkillsByAvatarID(byte id)
	{
		LinkedList<Skill> tmp = new LinkedList<Skill>();
		for (Skill skill : skills)
		{
			if (skill.getAvatarID() == id)
				tmp.add(skill);
		}
		Skill[] results = new Skill[tmp.size()];
		for (int i = 0; i < tmp.size(); i++)
		{
			results[i] = tmp.get(i);
		}
		return results;
	}

	protected abstract boolean isRecharging();
	protected float getRecharge() { return 1.0f; }

	// setter
	public void setPlayer(ServerGamePlayer player)
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

	public byte getAvatarID() { return avatarID; }
}
