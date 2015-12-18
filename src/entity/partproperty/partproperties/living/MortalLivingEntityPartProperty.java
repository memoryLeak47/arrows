package entity.partproperty.partproperties.living;

import entity.partproperty.LivingEntityPartProperty;

public interface MortalLivingEntityPartProperty extends LivingEntityPartProperty
{
	public void die();
	public int getHealth();
}
