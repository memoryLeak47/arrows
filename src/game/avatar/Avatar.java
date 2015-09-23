package game.avatar;

import game.avatar.avatars.*;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;

public abstract class Avatar
{
	private byte id;
	private static Avatar[] avatars;

	public Avatar()
	{
		id = -1;
	}

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

	public static Avatar[] getAvatars() { return avatars; }
	public final byte getID() { return id; }
	public ImageID getIconImageID() { return ImageFile.VOID_ICON.getImageID(); } // Wird in den Unterklassen weiter überschrieben
	public abstract String getName();
	public abstract String getClassName();
}
