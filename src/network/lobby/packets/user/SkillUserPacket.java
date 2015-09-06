package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class SkillUserPacket extends UserPacket
{
	private int[] skillIDs;

	public SkillUserPacket(int[] skillIDs)
	{
		for (int i = 0; i < skillIDs.length; i++)
		{
			this.skillIDs[i] = skillIDs[i];
		}
	}

	public SkillUserPacket(SkillUserPacket packet)
	{
		this(packet.getSkillIDs());
	}

	public int[] getSkillIDs()
	{
		return skillIDs;
	}
}
