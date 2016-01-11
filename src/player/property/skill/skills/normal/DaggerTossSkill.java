package player.property.skill.skills.normal;

import entity.entities.dynamic.spinnable.bullet.bullets.Dagger;
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
		GameVector vel = getPlayer().getMousePosition().minus(getPlayer().getPosition());
		vel.divide(vel.getMagnitude());
		addBullet(new Dagger(getPlayer(), getPlayer().getPosition(), vel.times(0.2f)));
	}

	@Override protected float getRecharge() { return 0.8f; }
}
