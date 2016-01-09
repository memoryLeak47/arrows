package playerproperty.skill.skills;

import playerproperty.skill.Skill;

public abstract class HoldSkill extends Skill
{
	private boolean active = false;

	public void tick()
	{
	}

	protected abstract float getReduction();
}
