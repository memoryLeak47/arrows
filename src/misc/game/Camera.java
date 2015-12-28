package misc.game;

import core.Main;
import entity.Entity;
import misc.math.game.GamePoint;
import misc.Debug;

public class Camera
{
	// the middle of the camera
	private Entity aim;
	private int localPlayerID;

	public Camera(int localPlayerID)
	{
		this.localPlayerID = localPlayerID;
	}

	public void setAim(Entity aim)
	{
		this.aim = aim;
	}

	public GamePoint getOffset()
	{
		return Main.getGame().getUncastedPlayers().get(localPlayerID).getPosition(); // TODO correct?
	}
}
