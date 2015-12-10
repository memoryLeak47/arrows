package network.lobby.packets.user;

import misc.Debug;
import network.lobby.packets.UserPacket;
import network.lobby.packets.PlayerPropertyUserPacket;
import playerproperty.skill.Skill;
import playerproperty.PlayerProperty;

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

	public void assign(SkillUserPacket skillPacket)
	{
		Debug.warnIf(skillPacket == null, "SkillUserPacket.assign(null)");
		skillIDs = skillPacket.skillIDs;
	}


	// Setter
	@Override public void setIDs(byte[] ids)
	{
		for (int i = 0; i < ids.length; i++)
		{
			skillIDs[i] = ids[i];
		}
	}

	// Getter
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
