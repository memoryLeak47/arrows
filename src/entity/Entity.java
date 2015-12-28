package entity;

import entity.MinimizedEntity;
import graphics.Animation;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class Entity
{
	private GamePosition position;
	private GameSize size;
	private Animation animation;

	public Entity(GamePosition position, GameSize size, Animation animation)
	{
		this.position = new GamePosition(position);
		this.size = new GameSize(size);
		this.animation = animation;
	}

	public GamePosition getPosition()
	{
		Debug.warnIf(position == null, "Entity.getPosition(): returns null");
		return position;
	}

	public GameSize getSize()
	{
		Debug.warnIf(size == null, "Entity.getSize(): returns null");
		return size;
	}

	// Getter
	public ImageID getImageID()
	{
		Debug.warnIf(getAnimation().getImageID() == null, "Entity.getImageID(): returns null");
		return getAnimation().getImageID();
	}

	protected Animation getAnimation()
	{
		Debug.warnIf(animation == null, "Entity.getAnimation(): returns null");
		return animation;
	}

	public abstract MinimizedEntity toMinimizedEntity();
}
