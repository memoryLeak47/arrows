package player.property.avatar.avatars;

import damage.Damage;
import graphics.ImageID;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import player.LobbyPlayer;
import player.ServerGamePlayer;
import player.players.RoguePlayer;
import player.property.avatar.Avatar;

public class Rogue extends Avatar
{
	@Override public ImageID getIconImageID() // works
	{
		return ImageFile.ROGUE_ICON.getImageID();
	}

	@Override public String getName() { return "unknown..."; }
	@Override public String getDescription() { return "the best."; }
	@Override public Damage getDamageStat() { return new Damage(1, 1, 1); }
	@Override public Damage getResistanceStat() { return new Damage(1, 1, 1); }
	@Override public int getAccelerationStat() { return 1; }
	@Override public int getRegenerationStat() { return 1; }
	@Override public int getMaxHealthStat() { return 1; }
	@Override public int getMassStat() { return 1; }

	@Override public ServerGamePlayer createServerGamePlayer(LobbyPlayer player, GamePosition position)
	{
		return new RoguePlayer(player, position);
	}
}
