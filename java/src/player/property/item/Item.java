package player.property.item;

import damage.Damage;
import player.property.PlayerProperty;
import player.property.item.items.*;
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
			new HealthRing(),
			new DamageRing()
		};

		for (byte i = 0; i < items.length; i++)
		{
			items[i].id = i;
		}
	}

	// for sub
	public abstract int getMassStat();
	public float getHealthStat() { return 0; }
	public float getRegenerationStat() { return 0; }
	public Damage getDamageStat() { return new Damage(0, 0, 0); }

	public static Item[] getAllItems() { return items; }

	// getter
	public static Item getByID(byte id)
	{
		if (id >= 0 && id < items.length)
		{
			return items[id];
		}
		return null;
	}

	@Override public final byte getID() { return id; }
}
