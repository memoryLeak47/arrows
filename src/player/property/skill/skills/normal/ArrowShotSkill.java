package player.property.skill.skills.normal;

import entity.entities.dynamic.spinnable.bullet.bullets.Arrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class ArrowShotSkill extends NormalSkill
{
	public ArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.ARROWSHOT_ICON.getImageID(); }
	@Override public String getDescription() { return "shoots an arrow"; }

	@Override public float getRecharge() { return 3.f; }

	@Override protected void trigger()
	{
		addBullet(new Arrow(getOwner(), getOwner().getPosition(), getVelocityToMouse().times(0.4f)));
	}
}
