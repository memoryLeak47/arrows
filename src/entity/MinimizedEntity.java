package entity;

import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;

public abstract class MinimizedEntity
{
	private ImageID imageID;
	private GamePosition position;

	public MinimizedEntity(ImageID imageID, GamePosition position)
	{
		this.imageID = imageID;
		this.position = position;
	}

	public ImageID getImageID()
	{
		Debug.warnIf(imageID == null, "MinimizedEntity.getImageID(): imageID == null");
		return imageID;
	}

	public GamePosition getPosition()
	{
		Debug.warnIf(position == null, "MinimizedEntity.getPosition(): position == null");
		return position;
	}

	public abstract void render();
}
