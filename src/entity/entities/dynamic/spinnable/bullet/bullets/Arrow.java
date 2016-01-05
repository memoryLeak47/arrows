package entity.entities.dynamic.spinnable.bullet.bullets;

import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;

public class Arrow extends ExtendedBullet
{
	public Arrow(GamePosition position, GameVector velocity)
	{
		super(position, new StaticAnimation(ImageFile.ARROW1.getImageID()), velocity);
	}
}
