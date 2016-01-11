package player.property.skill.skills;

import player.property.skill.Skill;

public abstract class HoldSkill extends Skill
{
	private boolean active = false;

	public HoldSkill(byte avatarID)
	{
		super(avatarID);
	}

	public void tick()
	{
	}

	protected abstract float getReduction();
}
