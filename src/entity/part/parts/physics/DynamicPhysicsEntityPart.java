package entity.part.parts.physics;

import entity.Entity;
import entity.part.PhysicsEntityPart;
import entity.part.property.properties.physics.MassivePhysicsEntityPartProperty;

public class DynamicPhysicsEntityPart extends PhysicsEntityPart implements MassivePhysicsEntityPartProperty
{
	private int mass;

	public DynamicPhysicsEntityPart(Entity parent)
	{
		super(parent);
	}

	public void init(int mass)
	{
		this.mass = mass;
	}

	public int getMass() { return mass; }
}
