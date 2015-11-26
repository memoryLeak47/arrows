package playerproperty.skill.skills;

import graphics.ImageFile;
import graphics.ImageID;
import playerproperty.skill.Skill;

public class ArrowShot extends Skill
{
	@Override public ImageID getIconImageID() { return ImageFile.ARROWSHOT_ICON.getImageID(); }

	@Override public String getDescription() { return "shoots an arrow"; }
}
