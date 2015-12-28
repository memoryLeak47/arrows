package entity.entities.bullet;

import entity.MinimizedEntity;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public class MinimizedBullet extends MinimizedEntity
{
	private float rotation;

	public MinimizedBullet(ImageID imageID, GamePosition position, float rotation /*Effects*/)
	{
		super(imageID, position);
		this.rotation = rotation;
	}

	public float getRotation() { return rotation; }
}
