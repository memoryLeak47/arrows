package entity.entitypart.entityparts.physics;

import entity.Entity;
import entity.entitypart.PhysicsEntityPart;

public class DynamicPhysicsEntityPart extends PhysicsEntityPart
{
	private int mass;

	public DynamicPhysicsEntityPart(Entity parent, int mass)
	{
		super(parent);
		this.mass = mass;
	}
	
	public int getMass() { return mass; }
}
