package player.property.skill.skills.special;

import bullet.bullets.TeleportArrow;
import graphics.ImageFile;
import graphics.ImageID;
import misc.Debug;
import player.property.skill.skills.SpecialSkill;

public class TeleportArrowShotSkill extends SpecialSkill
{
	private TeleportArrow arrow;

	public TeleportArrowShotSkill(byte avatarID)
	{
		super(avatarID);
	}

	@Override public ImageID getIconImageID() { return ImageFile.TELEPORTARROWSHOT_ICON.getImageID(); }
	@Override public float getRecharge() { return 0.3f; }
	@Override public String getDescription() { return "shoots a teleport-arrow"; }

	@Override public void onActivate()
	{
		trigger();
	}

	@Override public void trigger()
	{
		if (arrow == null)
		{
			if (getCharge() == MAX_CHARGE)
			{
				arrow = new TeleportArrow(getOwner(), getOwner().getPosition(), getVelocityToMouse().times(0.3f));
				addBullet(arrow);
				resetCharge();
			}
		}
		else
		{
			if (arrow.hasToBeRemoved())
			{
				arrow = null;
				trigger();
				return;
			}
			if (getOwner().isFlashPossible(arrow.getPosition()))
			{
				getOwner().flash(arrow.getPosition());
				arrow.die();
				arrow = null;
			}
		}
	}

	@Override public void onTrigger() {}

	@Override protected boolean isRecharging() // Solange man nicht komplett aufgeladen ist, weiter aufladen
	{
		return (getCharge() < MAX_CHARGE);
	}

}
