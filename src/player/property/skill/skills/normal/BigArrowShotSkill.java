package player.property.skill.skills.normal;

import bullet.bullets.BigArrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class BigArrowShotSkill extends NormalSkill
{
	public BigArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.BIGARROWSHOT_ICON.getImageID(); }
	@Override public String getDescription() { return "shoots a big arrow"; }
	@Override public float getRecharge() { return 0.3f; }

	@Override protected void trigger()
	{
		addBullet(new BigArrow(getOwner(), getOwner().getPosition(), getVelocityToMouse().times(0.6f)));
	}
}
