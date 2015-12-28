package misc.game;

import static core.Main.INGAME_SCREENSIZE_X;
import static core.Main.INGAME_SCREENSIZE_Y;
import static core.Main.PLAYERSIZE_X;
import static core.Main.PLAYERSIZE_Y;
import core.Main;
import entity.Entity;
import misc.math.game.GamePoint;
import misc.math.game.GamePosition;
import misc.Debug;

public class Camera
{
	// the middle of the camera
	private int localPlayerID;

	public Camera(int localPlayerID)
	{
		this.localPlayerID = localPlayerID;
	}

	public GamePoint getOffset()
	{
		return Main.getGame().getUncastedPlayers().get(localPlayerID).getPosition() // player-pos
			.plus(new GamePosition(PLAYERSIZE_X/2, PLAYERSIZE_Y/2)) // player-center
			.minus(new GamePosition(INGAME_SCREENSIZE_X/2, INGAME_SCREENSIZE_Y/2)); // offset
	}
}
