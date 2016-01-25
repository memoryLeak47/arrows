package entity.entities.dynamic.spinnable.bullet.bullets;

import damage.Damage;
import effect.effects.StunEffect;
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
		updateRotationByVelocity();
		counter++;
	}

	@Override public void onCollide(Entity e)
	{
		if (damageOnlyEnemyEntity(e))
		{
			e.applyEffect(new StunEffect((short) 20));
			counter = 100; // --> he dies
		}
	}

	@Override protected Damage getDamageStat() { return new Damage(2,12,0); }
	@Override public boolean isDead() { return counter > 10; }
}
