package game.item.items;

import game.item.Item;

public abstract class NotCastableItem extends Item
{
	@Override public boolean isCastable() { return false; }
}
