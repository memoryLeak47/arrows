package game.item;

import game.PlayerAttribute;
import game.item.items.*;
import graphics.ImageID;
import misc.Debug;

public abstract class Item extends PlayerAttribute
{
	private byte id;
	private static Item[] items;

	static
	{
		items = new Item[]
		{
			new HealthRing()
		};

		for (byte i = 0; i < items.length; i++)
		{
			items[i].id = i;
		}
	}

	// Getter
	public static Item getByID(byte id)
	{
		if (id >= 0 && id < items.length)
		{
			return items[id];
		}
		return null;
	}

	public final byte getID() { return id; }
}
