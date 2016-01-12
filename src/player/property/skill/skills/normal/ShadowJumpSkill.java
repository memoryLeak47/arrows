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
	public ShadowJumpSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.SHADOWJUMP_ICON.getImageID(); }

	@Override public String getDescription() { return "moves you"; }

	@Override protected void trigger()
	{
		GameVector vec = getPlayer().getMousePosition().minus(getPlayer().getPosition());
		if (vec.getMagnitude() > 5)
		{
			vec.setMagnitude(5);
		}
		GamePosition pos = new GamePosition(vec.plus(getPlayer().getPosition()));
		if (getPlayer().isFlashPossible(pos))
		{
			getPlayer().flash(pos);
			setCharge(0.0f);
		}
	}

	@Override protected void onTrigger() {} // charge will not be set to 0
	@Override protected float getRecharge() { return 0.6f; }
}
