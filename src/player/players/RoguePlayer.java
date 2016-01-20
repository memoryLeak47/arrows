package player.players;

import damage.Damage;
import graphics.ImageFile;
import graphics.animations.StaticAnimation;
import player.LobbyPlayer;
import player.ServerGamePlayer;
import misc.math.game.GamePosition;

public class RoguePlayer extends ServerGamePlayer
{
	public RoguePlayer(LobbyPlayer player)
	{
		super(player, new StaticAnimation(ImageFile.ROGUE.getImageID()));
	}

	@Override public String getAvatarName() { return "unknown..."; }
	@Override public Damage getDamageStat() { return new Damage(20, 22, 20); }
	@Override public Damage getResistanceStat() { return new Damage(20, 20, 20); }
	@Override public int getAccelerationStat() { return 1; }
	@Override public float getRegenerationStat() { return 0.02f; }
	@Override public float getMaxHealthStat() { return 50.f; }
	@Override public int getMassStat() { return 1; }

}
