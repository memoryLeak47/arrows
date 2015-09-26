package game.item.items;

import game.item.Item;

public abstract class CastableItem extends Item
{
	public abstract void activate();

	@Override public boolean isCastable() { return true; }
}
