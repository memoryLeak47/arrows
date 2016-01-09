package player.players;

import player.LobbyPlayer;
import player.ServerGamePlayer;
import misc.math.game.GamePosition;

public class RoguePlayer extends ServerGamePlayer
{
	public RoguePlayer(LobbyPlayer player, GamePosition position)
	{
		super(player, position);
	}
}
