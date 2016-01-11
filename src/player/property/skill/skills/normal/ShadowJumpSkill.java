package player.property.skill.skills.normal;

import entity.entities.dynamic.spinnable.bullet.bullets.Arrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class ShadowJumpSkill extends NormalSkill
{
	@Override public ImageID getIconImageID() { return ImageFile.SHADOWJUMP_ICON.getImageID(); }

	@Override public String getDescription() { return "moves you"; }

	@Override protected void trigger()
	{
		if (getPlayer().getPosition().minus(getPlayer().getMousePosition()).getMagnitude() < 5)
		{
			GamePosition pos = getPlayer().getMousePosition();
			if (getPlayer().isFlashPossible(pos))
			{
				getPlayer().flash(pos);
				setCharge(0.0f);
			}
		}
	}

	@Override protected void onTrigger() {} // charge will not be set to 0
}
