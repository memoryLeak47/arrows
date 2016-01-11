package player.property.skill.skills.normal;

import entity.entities.dynamic.spinnable.bullet.bullets.SmokeCloud;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class SmokeCloudSkill extends NormalSkill
{
	@Override public ImageID getIconImageID() { return ImageFile.SMOKECLOUD_ICON.getImageID(); }

	@Override public String getDescription() { return "spawns a damage-cloud"; }

	@Override protected void trigger()
	{
		addBullet(new SmokeCloud(getPlayer(), new GamePosition(getPlayer().getMousePosition()), new GameVector(0.f, 0.f)));
	}
}
