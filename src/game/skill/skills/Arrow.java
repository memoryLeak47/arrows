package game.skill.skills;

import graphics.ImageID;
import game.skill.Skill;

public class Arrow extends Skill
{
	@Override public ImageID getIconImageID() { return null; } // TODO

	@Override public int getMaxCooldown() { return 2; }
	@Override public String getDescription() { return "shoots an arrow"; }
	@Override public String getClassName() { return "Arrow"; }
}
