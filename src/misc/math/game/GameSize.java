package misc.math.game;

import misc.math.game.GamePoint;

public class GameSize extends GamePoint
{
	public GameSize()
	{
		super();
	}

	public GameSize(float x, float y)
	{
		super(x, y);
	}

	public GameSize(GamePoint pofloat)
	{
		this(pofloat.getX(), pofloat.getY());
	}
}
