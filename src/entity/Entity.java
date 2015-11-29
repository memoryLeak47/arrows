package entity;

import misc.Debug;
import misc.math.Rect;
import graphics.ImageID;
import misc.math.Position;

public abstract class Entity
{
	public Entity()
	{

	}

	public int getHealth() { Debug.warn("Entity: TODO"); return 0; } // TODO set
	public ImageID getImageID() { Debug.warn("Entity: TODO"); return new ImageID(0, 0); } // TODO set
	public Position getPosition() { Debug.warn("Entity: TODO"); return new Position(0, 0); } // TODO set
}
