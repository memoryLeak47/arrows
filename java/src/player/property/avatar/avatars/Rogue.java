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

	@Override public String getDescription() { return "the best."; }

	@Override public ServerGamePlayer createServerGamePlayer(LobbyPlayer player)
	{
		return new RoguePlayer(player);
	}
}
