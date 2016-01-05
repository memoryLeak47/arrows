package entity.entities.dynamic.spinnable.bullet.bullets;

import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import misc.math.game.GamePosition;

public class Arrow extends ExtendedBullet
{
	public Arrow(GamePosition position)
	{
		super(position, new StaticAnimation(ImageFile.ARROW1.getImageID()));
	}
}
