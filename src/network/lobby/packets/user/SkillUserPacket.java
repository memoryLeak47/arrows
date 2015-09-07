package network.lobby.packets.user;

import network.lobby.packets.UserPacket;

public class SkillUserPacket extends UserPacket
{
	private byte[] skillIDs;

	public SkillUserPacket(byte[] skillIDs)
	{
		this.skillIDs = new byte[4];
		for (int i = 0; i < skillIDs.length; i++)
		{
			this.skillIDs[i] = skillIDs[i];
		}
	}

	public SkillUserPacket(SkillUserPacket packet)
	{
		this(packet.getSkillIDs());
	}

	public byte[] getSkillIDs()
	{
		return skillIDs;
	}
}
