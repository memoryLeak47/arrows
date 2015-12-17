package entity.entityparts;

import entity.Entity;
import entity.EntityPart;
import misc.Debug;
import misc.math.Position;
import misc.math.Size;

public abstract class PhysicEntityPart extends EntityPart
{
	private Position position;
	private Size size;

	public PhysicEntityPart(Entity parent)
	{
		super(parent);
		this.position = new Position();
		this.size = new Size();
	}

	// Getter
	public abstract int getMass();

	public Position getPosition()
	{
		Debug.warnIf(position == null, "PhyiscEntityPart.getPosition(): returns null");
		return position;
	}
}
