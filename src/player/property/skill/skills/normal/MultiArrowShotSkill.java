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
	private static final int INTERVAL = 3;
	private static final int NUMBER = 4;
	private static final float ARROWSPEED = 0.6f;
	
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
		if ((counter % INTERVAL == 0) && (counter > 0))
		{
			if (getPlayer().getVelocity().getX() > 0)
			{
				addBullet(new Arrow(getPlayer(), getPlayer().getPosition(), new GameVector(ARROWSPEED, 0.f)));
			}
			else
			{
				addBullet(new Arrow(getPlayer(), getPlayer().getPosition(), new GameVector(-ARROWSPEED, 0.f)));
			}
		}
		counter--;
	}

	@Override protected void trigger()
	{
		counter = INTERVAL * NUMBER;
	}
}
