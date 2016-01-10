package player.players;

import damage.Damage;
import player.LobbyPlayer;
import player.ServerGamePlayer;
import misc.math.game.GamePosition;

public class RoguePlayer extends ServerGamePlayer
{
	public RoguePlayer(LobbyPlayer player, GamePosition position)
	{
		super(player, position);
	}

	@Override public String getAvatarName() { return "unknown..."; }
	@Override public Damage getDamageStat() { return new Damage(1, 1, 1); }
	@Override public Damage getResistanceStat() { return new Damage(1, 1, 1); }
	@Override public int getAccelerationStat() { return 1; }
	@Override public int getRegenerationStat() { return 1; }
	@Override public int getMaxHealthStat() { return 100; }
	@Override public int getMassStat() { return 1; }

}
