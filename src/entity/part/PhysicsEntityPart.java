package entity.part;

import entity.Entity;
import entity.EntityPart;
import misc.Debug;
import misc.math.Position;
import misc.math.Size;

public abstract class PhysicsEntityPart extends EntityPart
{
	private Position position;
	private Size size;

	public PhysicsEntityPart(Entity parent)
	{
		super(parent);
	}

	public void init(Position pos, Size size)
	{
		this.position = new Position(pos);
		this.size = new Size(size);
	}

	// Getter
	public Position getPosition()
	{
		Debug.warnIf(position == null, "PhysicsEntityPart.getPosition(): returns null");
		return position;
	}

	public Size getSize()
	{
		Debug.warnIf(size == null, "PhysicsEntityPart.getSize(): returns null");
		return size;
	}
}
