package game.skill.skills;

import graphics.ImageFile;
import graphics.ImageID;
import game.skill.Skill;

public class ArrowShot extends Skill
{
	@Override public ImageID getIconImageID() { return ImageFile.ARROWSHOT_ICON.getImageID(); }

	@Override public int getMaxCooldown() { return 2; }
	@Override public String getDescription() { return "shoots an arrow"; }
}
