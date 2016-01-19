package player.property.skill.skills;

import player.property.skill.Skill;

public abstract class NormalSkill extends Skill
{
	public NormalSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public void onKeyPressed()
	{
		if (getCharge() == MAX_CHARGE)
		{
			trigger();
			onTrigger();
		}
	}

	@Override protected void onTrigger()
	{
		resetCharge();
	}

	@Override protected boolean isRecharging() // Solange man nicht komplett aufgeladen ist, weiter aufladen
	{
		return (getCharge() < MAX_CHARGE);
	}
}
