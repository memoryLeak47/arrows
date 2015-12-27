package entity;

import static core.Main.getGame;
import static core.Main.TILESIZE;
import core.Screen;
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

	public void render()
	{
		if (inScreen())
		{
			int x, y;
			x = (int) (TILESIZE*(getPosition().getX() - getGame().getCamera().getOffset().getX()));
			y = (int) (TILESIZE*(getPosition().getY() - getGame().getCamera().getOffset().getY())); 
			Screen.g().drawImage(ImageFile.getImageByImageID(getImageID()), x, y, null);
		}
	}

	private boolean inScreen()
	{
		// TODO
		return true;
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
