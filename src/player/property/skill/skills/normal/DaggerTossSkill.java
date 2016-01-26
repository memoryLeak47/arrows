package player.property.skill.skills.normal;

import bullet.bullets.Dagger;
import graphics.ImageID;
import graphics.ImageFile;
import player.property.skill.skills.NormalSkill;
import misc.math.game.GameVector;

public class DaggerTossSkill extends NormalSkill
{
	public DaggerTossSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.DAGGERTOSS_ICON.getImageID(); }
	@Override public String getDescription() { return "throws a lovely dagger"; }

	@Override public void trigger()
	{
		addBullet(new Dagger(getOwner(), getOwner().getPosition(), getVelocityToMouse().times(0.8f)));
	}

	@Override protected float getRecharge() { return 0.8f; }
}
