package entity;

import misc.Debug;
import graphics.Animation;
import graphics.ImageID;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class Entity
{
	private GamePosition position;
	private GameSize size;
	private Animation animation;

	public Entity()
	{

	}

	public GamePosition getPosition()
	{
		Debug.warnIf(position == null, "Entity.getPosition(): returns null");
		return position;
	}

	public void render()
	{
		Debug.warn("Entity.render(): TODO nudel");
		// TODO
	}

	protected ImageID getImageID()
	{
		Debug.warnIf(getAnimation().getImageID() == null, "Entity.getImageID(): returns null");
		return getAnimation().getImageID();
	}

	protected Animation getAnimation()
	{
		Debug.warnIf(animation == null, "Entity.getAnimation(): returns null");
		return animation;
	}

}
