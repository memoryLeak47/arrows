package network.lobby.packets.user;

import playerproperty.item.Item;
import playerproperty.PlayerProperty;
import network.lobby.packets.UserPacket;
import network.lobby.packets.PlayerPropertyUserPacket;

public class ItemUserPacket extends UserPacket implements PlayerPropertyUserPacket
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

	public void assign(ItemUserPacket itemPacket)
	{
		// TODO fehlerabfragen
		itemIDs = itemPacket.itemIDs;
	}

	// Setter
	@Override public void setIDs(byte[] ids)
	{
		for (int i = 0; i < ids.length; i++)
		{
			itemIDs[i] = ids[i];
		}
	}

	// Getter
	public Item[] getItems()
	{
		Item[] items = new Item[3];
		for (byte i = 0; i < 3; i++)
		{
			items[i] = Item.getByID(itemIDs[i]);
		}
		return items;
	}

	public byte[] getItemIDs() { return itemIDs; }

	@Override public PlayerProperty[] getPlayerProperty() { return getItems(); }
}
