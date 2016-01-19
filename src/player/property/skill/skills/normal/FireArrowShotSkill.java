package player.property.skill.skills.normal;

import effect.Effect;
import effect.effects.BurnEffect;
import entity.entities.dynamic.spinnable.bullet.bullets.Arrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class FireArrowShotSkill extends NormalSkill
{
	public FireArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.FIREARROWSHOT_ICON.getImageID(); }
	@Override public String getDescription() { return "shoots a burning arrow"; }
	@Override public float getRecharge() { return 1.f; }

	@Override protected void trigger()
	{
		Arrow a = new Arrow(getOwner(), getOwner().getPosition(), getVelocityToMouse().times(0.4f));
		a.applyEffect(new BurnEffect((short)10, (short)1));
		addBullet(a);
	}
}
