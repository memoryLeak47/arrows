package entity.entities.dynamic.spinnable.bullet.bullets;

import entity.Entity;
import entity.entities.dynamic.spinnable.bullet.StickyBullet;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;

public class Arrow extends StickyBullet
{
	public Arrow(GamePosition position, GameVector velocity)
	{
		super(position, new StaticAnimation(ImageFile.ARROW1.getImageID()), velocity);
	}

/*
	@Override protected void onCollide(Entity e)
	{
		stop();
	}
*/
}
