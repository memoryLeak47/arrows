package entity;

import static core.Main.getGame;
import static core.Main.TILESIZE;
import core.Screen;
import graphics.ImageID;
import graphics.ImageFile;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

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

	public GameSize getSize()
	{
		Debug.warnIf(getImageID() == null, "MinimizedEntity.getSize(): getImageID is null");
		GameSize gs = new GameSize(getImageID());
		gs.scale(1.0f/TILESIZE);
		return gs;
	}

	public void render()
	{
		if (inScreen())
		{
			int x, y;
			x = (int) (TILESIZE*(getPosition().getX() - getSize().getX()/2 - getGame().getCamera().getOffset().getX()));
			y = (int) (TILESIZE*(getPosition().getY() - getSize().getY()/2 - getGame().getCamera().getOffset().getY())); 
			Debug.test("RenderPosition: (" + x/TILESIZE + "|" + y/TILESIZE + "), Offset: " + getGame().getCamera().getOffset() + ", Position: " + getPosition() + ", Size: " + getSize());
			Screen.g().drawImage(ImageFile.getImageByImageID(getImageID()), x, y, null);
		}
	}

	private boolean inScreen()
	{
		// TODO
		return true;
	}
}
