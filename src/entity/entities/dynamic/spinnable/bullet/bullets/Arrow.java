package entity.entities.dynamic.spinnable.bullet.bullets;

import damage.Damage;
import entity.Entity;
import entity.entities.dynamic.spinnable.bullet.StickyBullet;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.ServerGamePlayer;

public class Arrow extends StickyBullet
{
	public Arrow(ServerGamePlayer owner, GamePosition position, GameVector velocity)
	{
		super(owner, position, new StaticAnimation(ImageFile.ARROW.getImageID()), velocity);
	}

	@Override public void tick()
	{
		super.tick();
		updateRotationByVelocity();
	}

	@Override protected Damage getDamageStat() { return new Damage(1,6,0); }
}
