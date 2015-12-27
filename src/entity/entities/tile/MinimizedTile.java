package entity.entities.tile;

import entity.MinimizedEntity;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public class MinimizedTile extends MinimizedEntity
{
	public MinimizedTile(ImageID imageID, GamePosition position)
	{
		super(imageID, position);
	}

	@Override public void render()
	{
		Debug.warn("MinimizedTile.render(): TODO");
	}
}
