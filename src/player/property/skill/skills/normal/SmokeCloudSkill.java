package player.property.skill.skills.normal;

import effect.effects.BurnEffect;
import entity.entities.dynamic.spinnable.bullet.bullets.SmokeCloud;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class SmokeCloudSkill extends NormalSkill
{
	public SmokeCloudSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.SMOKECLOUD_ICON.getImageID(); }

	@Override public String getDescription() { return "spawns a damage-cloud"; }

	@Override public float getRecharge() { return 1.f; }

	@Override protected void trigger()
	{
		addBullet(new SmokeCloud(getOwner(), new GamePosition(getOwner().getMousePosition()), new GameVector(0.f, 0.f)));
	}
}
