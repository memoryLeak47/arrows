package player.players;

import player.LobbyPlayer;
import player.ServerGamePlayer;
import misc.math.game.GamePosition;

public class ArcherPlayer extends ServerGamePlayer
{
	public ArcherPlayer(LobbyPlayer player, GamePosition position)
	{
		super(player, position);
	}
}
