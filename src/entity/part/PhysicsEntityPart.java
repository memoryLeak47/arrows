package entity.part;

import entity.Entity;
import entity.EntityPart;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public abstract class PhysicsEntityPart extends EntityPart
{
	private GamePosition position;
	private GameSize size;

	public PhysicsEntityPart(Entity parent)
	{
		super(parent);
	}

	public void init(GamePosition pos, GameSize size)
	{
		this.position = new GamePosition(pos);
		this.size = new GameSize(size);
	}

	// Getter
	public GamePosition getPosition()
	{
		Debug.warnIf(position == null, "PhysicsEntityPart.getPosition(): returns null");
		return position;
	}

	public GameSize getSize()
	{
		Debug.warnIf(size == null, "PhysicsEntityPart.getSize(): returns null");
		return size;
	}
}
