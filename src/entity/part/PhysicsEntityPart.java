package entity.part;

import entity.Entity;
import entity.EntityPart;
import misc.Debug;
import misc.math.Position;
import misc.math.Size;

public abstract class PhysicsEntityPart extends EntityPart
{
	private Position position; // TODO maybe put into EntityPartProperty
	private Size size; // TODO maybe put into EntityPartProperty

	public PhysicsEntityPart(Entity parent)
	{
		super(parent);
		this.position = new Position();
		this.size = new Size();
	}

	// Getter
	public Position getPosition() // TODO maybe put into EntityPartProperty
	{
		Debug.warnIf(position == null, "PhysicsEntityPart.getPosition(): returns null");
		return position;
	}

	public Size getSize() // TODO maybe put into EntityPartProperty
	{
		Debug.warnIf(size == null, "PhysicsEntityPart.getSize(): returns null");
		return size;
	}
}
