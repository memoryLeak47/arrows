package player.property.skill.skills.normal;

import bullet.bullets.Arrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class FrontArrowShotSkill extends NormalSkill
{
	public FrontArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.FRONTARROWSHOT_ICON.getImageID(); }
	@Override public String getDescription() { return "shoots an arrow in movement direction"; }

	@Override public float getRecharge() { return 3.f; }

	@Override protected void trigger()
	{
		GameVector speed;
		if (getOwner().getVelocity().getX() < 0)
		{
			speed = new GameVector(-0.5f, 0);
		} else
		{
			speed = new GameVector(0.5f, 0);
		}
		addBullet(new Arrow(getOwner(), getOwner().getPosition(), speed));
	}
}
