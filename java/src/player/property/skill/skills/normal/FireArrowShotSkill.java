package player.property.skill.skills.normal;

import effect.Effect;
import effect.effects.BurnEffect;
import bullet.bullets.Arrow;
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
	@Override public float getRecharge() { return 1.4f; }

	@Override protected void trigger()
	{
		Arrow a = new Arrow(getOwner(), getOwner().getPosition(), getVelocityToMouse().times(0.6f));
		a.applyEffect(new BurnEffect((short)10, (short)100));
		addBullet(a);
	}
}
