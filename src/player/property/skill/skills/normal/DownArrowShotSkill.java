package player.property.skill.skills.normal;

import entity.Entity;
import entity.entities.dynamic.spinnable.bullet.bullets.StunningArrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class DownArrowShotSkill extends NormalSkill
{
	public DownArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.DOWNARROWSHOT_ICON.getImageID(); }
	@Override public String getDescription() { return "shoots an arrow in movement direction"; }

	@Override public float getRecharge() { return 0.3f; }

	@Override protected void trigger()
	{
		StunningArrow arrow = new StunningArrow(getOwner(), getOwner().getPosition(), new GameVector(0.f, 0.5f));
		addBullet(arrow);
		getOwner().airJump();
	}
}
