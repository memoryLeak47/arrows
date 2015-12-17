package entity;

import entity.Entity;

public abstract class EntityPart
{
	private Entity parent;

	protected EntityPart(Entity parent)
	{
		this.parent = parent;
	}

	public final Entity getParent()
	{
		return parent;
	}
}
