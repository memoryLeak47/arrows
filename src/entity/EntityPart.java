package entity;

import entity.Entity;

public class EntityPart
{
	private Entity parent;

	public EntityPart(Entity parent)
	{
		this.parent = parent;
	}

	public final Entity getParent()
	{
		return parent;
	}
}
