package network.lobby.packets.user;

import game.item.Item;
import network.lobby.packets.UserPacket;

public class ItemUserPacket extends UserPacket
{
	private byte[] itemIDs;

	public ItemUserPacket(byte[] itemIDs)
	{
		this.itemIDs = new byte[3];
		for (byte i = 0; i < itemIDs.length; i++)
		{
			this.itemIDs[i] = itemIDs[i];
		}
	}

	public ItemUserPacket(ItemUserPacket packet)
	{
		this(packet.getItemIDs());
	}

	public Item[] getItems()
	{
		Item[] items = new Item[3];
		for (byte i = 0; i < 3; i++)
		{
			items[i] = Item.getByID(i);
		}
		return items;
	}

	public byte[] getItemIDs()
	{
		return itemIDs;
	}
}
