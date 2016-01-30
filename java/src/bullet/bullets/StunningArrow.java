package bullet.bullets;

import damage.Damage;
import effect.effects.StunEffect;
import entity.Entity;
import bullet.StickyBullet;
import graphics.animations.StaticAnimation;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import misc.math.game.GameVector;
import player.ServerGamePlayer;

public class StunningArrow extends StickyBullet
{
	public StunningArrow(ServerGamePlayer owner, GamePosition position, GameVector velocity)
	{
		super(owner, position, new StaticAnimation(ImageFile.STUNNINGARROW.getImageID()), velocity);
	}

	@Override public void onCollide(Entity e)
	{
		super.onCollide(e);
		e.applyEffect(new StunEffect((short) 20));

	}

	@Override public void tick()
	{
		super.tick();
		updateRotationByVelocity();
	}

	@Override protected Damage getDamageStat() { return new Damage(1,6,0); }
}
