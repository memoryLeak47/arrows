package misc.game;

import entity.Entity;
import misc.math.game.GamePoint;
import misc.Debug;

public class Camera
{
	// the middle of the camera
	private Entity aim;

	public Camera()
	{
		// TODO
	}

	public void setAim(Entity aim)
	{
		this.aim = aim;
	}

	public GamePoint getOffset()
	{
		Debug.warn("Camera.getOffset(): TODO");
		// TODO
		return null;
	}
}
