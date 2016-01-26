package bullet;

import entity.entities.dynamic.spinnable.MinimizedSpinnableEntity;
import graphics.ImageID;
import misc.Debug;
import misc.compress.CompressBuffer;
import misc.math.game.GamePosition;

public class MinimizedBullet extends MinimizedSpinnableEntity
{
	public MinimizedBullet(GamePosition position, ImageID imageID, float rotation, boolean[] effectIDs)
	{
		super(position, imageID, rotation, effectIDs);
	}

	public MinimizedBullet(CompressBuffer buffer)
	{
		super(buffer);
	}
}
