package player.property.skill.skills.normal;

import entity.entities.dynamic.spinnable.bullet.bullets.Arrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.NormalSkill;

public class MultiArrowShotSkill extends NormalSkill
{
	private static final int INTERVAL = 5;
	private static final int NUMBER = 4;
	
	private int counter;

	public MultiArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.MULTIARROWSHOT_ICON.getImageID(); }
	@Override public String getDescription() { return "shoots a big arrow"; }
	@Override public float getRecharge() { return 0.3f; }

	@Override public void tick()
	{
		super.tick();
		if (counter % INTERVAL == 0)
		{
			addBullet(new Arrow(getPlayer(), getPlayer().getPosition(), getVelocityToMouse().times(0.6f)));
		}
	}

	@Override protected void trigger()
	{
		counter = INTERVAL * NUMBER;
	}
}
