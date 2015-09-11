package game.avatar;

import game.avatar.avatars.*;
import game.graphics.ImageID;
import misc.Debug;

public abstract class Avatar
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

	// Getter
	public static Avatar getByID(byte id)
	{
		if (id >= 0 && id < avatars.length)
		{
			return avatars[id];
		}
		return null;
	}

	public final byte getID() { return id; }

	public abstract ImageID getIconImageID();
	public abstract String getName();
}
