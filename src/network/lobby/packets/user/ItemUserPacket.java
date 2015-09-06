package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class ItemUserPacket extends UserPacket
{
	private int[] itemIDs;

	public ItemUserPacket(int[] itemIDs)
	{
		for (int i = 0; i < itemIDs.length; i++)
		{
			this.itemIDs[i] = itemIDs[i];
		}
	}

	public ItemUserPacket(ItemUserPacket packet)
	{
		this(packet.getItemIDs());
	}

	public int[] getItemIDs()
	{
		return itemIDs;
	}
}
