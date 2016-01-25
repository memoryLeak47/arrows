package entity.entities.dynamic.spinnable.bullet.bullets;

import entity.entities.dynamic.spinnable.bullet.ExtendedBullet;
import graphics.ImageFile;
import graphics.animations.StaticAnimation;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.property.skill.skills.SpecialSkill;
import player.ServerGamePlayer;

public class TeleportArrow extends ExtendedBullet
{
	private boolean alive = true;

	public TeleportArrow(ServerGamePlayer player, GamePosition position, GameVector velocity)
	{
		super(player, position, new StaticAnimation(ImageFile.TELEPORTARROW.getImageID()), velocity);
	}

	@Override public void tick()
	{
		super.tick();
		updateRotationByVelocity();
	}

	public void die()
	{
		alive = false;
	}

	@Override public boolean isDead() { return !alive; }
}
