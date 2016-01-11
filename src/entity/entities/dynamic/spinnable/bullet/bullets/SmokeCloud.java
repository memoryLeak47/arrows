package entity.entities.dynamic.spinnable.bullet.bullets;

import damage.Damage;
import entity.Entity;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;

public class SmokeCloud extends ExtendedBullet
{
	private boolean alive = true;

	public SmokeCloud(GamePosition position, GameVector velocity)
	{
		super(position, new StaticAnimation(ImageFile.SMOKECLOUD.getImageID()), velocity);
	}

	@Override public void onCollide(Entity e)
	{
		e.onDamage(getDamage());
		alive = false;
	}

	@Override protected Damage getDamage() { return new Damage(0,0,2); }

	@Override public boolean hasToBeRemoved() { return !alive; }
	
}
