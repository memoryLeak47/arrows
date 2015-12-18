package entity.entitypart;

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
		this.position = new Position();
		this.size = new Size();
	}

	// Getter
	public abstract int getMass();

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
