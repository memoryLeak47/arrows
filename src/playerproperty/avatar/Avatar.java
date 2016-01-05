package playerproperty.avatar;

import playerproperty.PlayerProperty;
import misc.game.Damage;
import playerproperty.avatar.avatars.*;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;

public abstract class Avatar extends PlayerProperty
{
	private byte id;
	private static Avatar[] avatars;

	static
	{
		avatars = new Avatar[]
		{
			new Archer()
		};

		for (byte i = 0; i < avatars.length; i++)
		{
			avatars[i].id = i;
		}
	}

	// for sub
	public abstract int getMassStat();
	public abstract int getMaxHealthStat();
	public abstract int getRegenerationStat();
	public abstract int getAccelerationStat();
	public abstract Damage getDamageStat();
	public abstract Damage getResistanceStat();
	public abstract String getName();

	// getter
	public static Avatar getByID(byte id)
	{
		if (id >= 0 && id < avatars.length)
		{
			return avatars[id];
		}
		return null;
	}

	public static Avatar[] getAllAvatars() { return avatars; }
	@Override public final byte getID() { return id; }
}
