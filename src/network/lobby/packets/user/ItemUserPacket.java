package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class ItemUserPacket extends UserPacket
{
	private byte[] itemIDs;

	public ItemUserPacket(byte[] itemIDs)
	{
		this.itemIDs = new byte[3];
		for (int i = 0; i < itemIDs.length; i++)
		{
			this.itemIDs[i] = itemIDs[i];
		}
	}

	public ItemUserPacket(ItemUserPacket packet)
	{
		this(packet.getItemIDs());
	}

	public byte[] getItemIDs()
	{
		return itemIDs;
	}
}
