package entity.entitypart.entityparts.living;

import entity.Entity;
import entity.entitypart.LivingEntityPart;
import entity.partproperty.partproperties.living.MortalLivingEntityPartProperty;

public class PlayerLivingEntityPart extends LivingEntityPart implements MortalLivingEntityPartProperty
{
	int health;

	public PlayerLivingEntityPart(Entity parent)
	{
		super(parent);
	}

	@Override public int getHealth() { return health; }
	@Override public void die() { /*TODO*/ }
}
