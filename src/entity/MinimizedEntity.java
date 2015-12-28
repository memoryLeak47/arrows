package entity;

import static core.Main.getGame;
import static core.Main.TILESIZE;
import core.Screen;
import graphics.ImageID;
import graphics.ImageFile;
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
}
