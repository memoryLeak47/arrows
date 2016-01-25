package misc.math.collision;

import misc.math.game.GameVector;

public class RotatedRect
{
	private float x, y, w, h;
	private float rotation;

	public RotatedRect(float x, float y, float w, float h, float rotation)
	{
		this.x = x;
		this.y = y;
		this.w = w;
		this.h = h;
		this.rotation = rotation;
	}

	public RotatedRect(GameVector pos, GameVector size, float rotation)
	{
		this.x = pos.getX();
		this.y = pos.getY();
		this.w = size.getX();
		this.h = size.getY();
		this.rotation = rotation;
	}

	public boolean contains(GameVector vec)
	{
		GameVector rotvec = GameVector.getFromTo(this.x, this.y, vec.getX(), vec.getY());
		rotvec = rotvec.rotate(-this.rotation);
		return (Math.abs(rotvec.getX()) < this.w/2) && (Math.abs(rotvec.getY()) < this.h/2);
	}
}
