package player.property.skill.skills.normal;

import entity.entities.dynamic.spinnable.bullet.bullets.Arrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class ArrowShotSkill extends NormalSkill
{
	public ArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.ARROWSHOT_ICON.getImageID(); }
	@Override public String getDescription() { return "shoots an arrow"; }

	@Override protected void trigger()
	{
		addBullet(new Arrow(getPlayer(), new GamePosition(getPlayer().getPosition()), new GameVector(0.4f, 0.f)));
	}
}
