package game.skill;

import game.skill.Skill;
import game.graphics.ImageID;
import game.Player;

public abstract class SkillInfo
{
	public static final SkillInfo getByID(int id)
	{
		// TODO
		return null;
	}

	public abstract ImageID getIcon();
	public abstract int getMaxCooldown();
	public abstract String getDescription();
	public abstract Skill createSkill(Player owner);
}
