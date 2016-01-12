package player.property.skill.skills.normal;

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

	@Override protected void trigger()
	{
		Arrow a = new Arrow(getPlayer(), getPlayer().getPosition());
		addBullet(a, getVelocityToMouse().times(0.4f));
		a.applyEffect(Effect.getByID(Effect.BURN_EFFECT));
	}
}
