package entity.entities.dynamic.spinnable.bullet.bullets;

import damage.Damage;
import entity.Entity;
import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import graphics.ImageFile;
import graphics.animations.StaticAnimation;
import player.ServerGamePlayer;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;

public class Dagger extends ExtendedBullet
{
	private int counter = 0;

	public Dagger(ServerGamePlayer owner, GamePosition position, GameVector velocity)
	{
		super(owner, position, new StaticAnimation(ImageFile.DAGGER.getImageID()), velocity);
	}

	@Override public void tick()
	{
		super.tick();
		counter++;
	}

	@Override public void onCollide(Entity e)
	{
		if (e == getOwner())
		{
			return;
		}
		e.onDamage(getDamage());
		counter = 100; // --> he dies
	}

	@Override public float getRotation()
	{
		GameVector normal = new GameVector(1, 0);
		float rot = (float)-(Math.atan2(normal.getY(), normal.getX()) - Math.atan2(getVelocity().getY(), getVelocity().getX()));
		return rot;
	}

	@Override protected Damage getDamage() { return new Damage(0,6,0); }
	@Override public boolean hasToBeRemoved() { return counter > 10; }
}
