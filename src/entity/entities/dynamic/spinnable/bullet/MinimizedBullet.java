package entity.entities.dynamic.spinnable.bullet;

import entity.MinimizedEntity;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public class MinimizedBullet extends MinimizedEntity
{
	private float rotation;

	public MinimizedBullet(GamePosition position, ImageID imageID, float rotation /*, Effects*/)
	{
		super(position, imageID);
		this.rotation = rotation;
	}

	public float getRotation() { return rotation; }
}
