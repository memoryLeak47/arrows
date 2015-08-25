package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class AttributeUserPacket extends UserPacket
{
	private int[] skillIDs;
	private int[] itemIDs;

	public AttributeUserPacket(int[] skillIDs, int[] itemIDs)
	{
		for (int i = 0; i < skillIDs.length; i++)
		{
			this.skillIDs[i] = skillIDs[i];
		}

		for (int i = 0; i < itemIDs.length; i++)
		{
			this.itemIDs[i] = itemIDs[i];
		}
	}

	public AttributeUserPacket(AttributeUserPacket packet)
	{
		this(packet.getSkillIDs(), packet.getItemIDs());
	}

	public int[] getSkillIDs()
	{
		return skillIDs;
	}

	public int[] getItemIDs()
	{
		return itemIDs;
	}
}
