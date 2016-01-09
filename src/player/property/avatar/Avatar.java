package player.property.avatar;

import player.LobbyPlayer;
import player.ServerGamePlayer;
import player.property.PlayerProperty;
import damage.Damage;
import player.property.avatar.avatars.*;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.game.GamePosition;

public abstract class Avatar extends PlayerProperty
{
	private byte id;
	private static Avatar[] avatars;

	static
	{
		avatars = new Avatar[]
		{
			new Archer(),
			new Rogue()
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

	public abstract ServerGamePlayer createServerGamePlayer(LobbyPlayer player, GamePosition pos);

	@Override public final byte getID() { return id; }
}
