package player.property.avatar.avatars;

import damage.Damage;
import graphics.ImageID;
import graphics.ImageFile;
import misc.math.game.GamePosition;
import player.LobbyPlayer;
import player.ServerGamePlayer;
import player.players.ArcherPlayer;
import player.property.avatar.Avatar;

public class Archer extends Avatar
{
	@Override public ImageID getIconImageID() // works
	{
		return ImageFile.ARCHER_ICON.getImageID();
	}

	@Override public String getDescription() { return "a funny fernkämpfer"; }

	@Override public ServerGamePlayer createServerGamePlayer(LobbyPlayer player, GamePosition position)
	{
		return new ArcherPlayer(player, position);
	}
}
