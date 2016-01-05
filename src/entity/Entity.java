package entity;

import core.Main;
import entity.MinimizedEntity;
import graphics.Animation;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.math.pixel.PixelSize;
import misc.game.Camera;

public abstract class Entity
{
	private GamePosition position;
	private Animation animation;

	public Entity(GamePosition position, Animation animation)
	{
		this.position = new GamePosition(position);
		this.animation = animation;
	}

	public void tick()
	{
		getAnimation().tick();
	}

	// getter

	public boolean isCircular() { return false; }

	public GamePosition getPosition()
	{
		Debug.warnIf(position == null, "Entity.getPosition(): returns null");
		return position;
	}

	public GameSize getSize()
	{
		Debug.warnIf(getImageID() == null, "Entity.getSize(): getImageID is null");
		return Camera.get().pixelSizeToGameSize(new PixelSize(getImageID()));
	}

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

	public float getLeft() { return getPosition().getX() - getSize().getX() * 0.5f; }
	public float getRight() { return getPosition().getX() + getSize().getX() * 0.5f; }
	public float getTop() { return getPosition().getY() - getSize().getY() * 0.5f; }
	public float getBot() { return getPosition().getY() + getSize().getY() * 0.5f; }

	public abstract MinimizedEntity toMinimizedEntity();
}
