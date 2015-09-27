package network.lobby.packets.user;

import game.skill.Skill;
import game.PlayerProperty;
import misc.Debug;
import network.lobby.packets.UserPacket;
import network.lobby.packets.PlayerPropertyUserPacket;

public class SkillUserPacket extends UserPacket implements PlayerPropertyUserPacket
{
	private byte[] skillIDs;

	public SkillUserPacket(byte[] skillIDs)
	{
		this.skillIDs = new byte[4];
		for (byte i = 0; i < skillIDs.length; i++)
		{
			this.skillIDs[i] = skillIDs[i];
		}
	}

	public SkillUserPacket(SkillUserPacket packet)
	{
		this(packet.getSkillIDs());
	}

	public Skill[] getSkills()
	{
		Skill[] skills = new Skill[4];
		for (byte i = 0; i < 4; i++)
		{
			skills[i] = Skill.getByID(skillIDs[i]);	
		}
		return skills;
	}

	public byte[] getSkillIDs() { return skillIDs; }

	@Override public PlayerProperty[] getPlayerProperty() { return getSkills(); }
}
