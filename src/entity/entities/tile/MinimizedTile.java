package entity.entities.tile;

import entity.MinimizedEntity;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class MinimizedTile extends MinimizedEntity
{
	public MinimizedTile(ImageID imageID, GamePosition position)
	{
		super(imageID, position);
	}

	@Override public GameSize getSize() { return new GameSize(1, 1); }
}
