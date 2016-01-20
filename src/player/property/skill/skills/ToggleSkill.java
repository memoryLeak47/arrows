package player.property.skill.skills;

import player.property.skill.Skill;

public abstract class ToggleSkill extends Skill
{
	private boolean active = false;

	public ToggleSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public void tick()
	{
	}
}
