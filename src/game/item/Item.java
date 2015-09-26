package game.item;

import game.PlayerProperty;
import game.item.items.castable.*;
import game.item.items.notcastable.*;
import graphics.ImageID;
import misc.Debug;

public abstract class Item extends PlayerProperty
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

	// for sub
	public abstract boolean isCastable();
	public abstract int getMassStat();

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
