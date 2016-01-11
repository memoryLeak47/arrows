package player.players;

import damage.Damage;
import graphics.ImageFile;
import graphics.animations.StaticAnimation;
import player.LobbyPlayer;
import player.ServerGamePlayer;
import misc.math.game.GamePosition;

public class ArcherPlayer extends ServerGamePlayer
{
	public ArcherPlayer(LobbyPlayer player, GamePosition position)
	{
		super(player, position, new StaticAnimation(ImageFile.ARCHER.getImageID()));
	}

	@Override public String getAvatarName() { return "Legolas ^^"; }
	@Override public Damage getDamageStat() { return new Damage(1, 1, 1); }
	@Override public Damage getResistanceStat() { return new Damage(1, 1, 1); }
	@Override public int getAccelerationStat() { return 1; }
	@Override public int getRegenerationStat() { return 1; }
	@Override public int getMaxHealthStat() { return 100; }
	@Override public int getMassStat() { return 1; }

}
