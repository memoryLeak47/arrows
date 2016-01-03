package playerproperty.skill.skills.normal;

import graphics.ImageFile;
import graphics.ImageID;
import playerproperty.skill.skills.NormalSkill;

public class ArrowShot extends NormalSkill
{
	@Override public ImageID getIconImageID() { return ImageFile.ARROWSHOT_ICON.getImageID(); }

	@Override public String getDescription() { return "shoots an arrow"; }
}
