package player.property.skill.skills.normal;

import damage.Damage;
import graphics.ImageFile;
import graphics.ImageID;
import player.property.skill.skills.NormalSkill;

public class DaggerStingSkill extends NormalSkill
{
	public DaggerStingSkill(byte id)
	{
		super(id);
	}

	@Override public ImageID getIconImageID() { return ImageFile.DAGGERSTING_ICON.getImageID(); }
	@Override public String getDescription() { return "stings ... "; }
	@Override public float getRecharge() { return 0.9f; }

	@Override public void trigger()
	{
		getOwner().accelerate(getVelocityToMouse());
		damageCircle(new Damage(2, 12, 1), getOwner().getPosition().plus(getOwner().getVelocity()), 2);
	}
}
