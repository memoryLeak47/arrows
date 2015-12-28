package misc.math.game;

import misc.math.game.GamePoint;

public class GamePosition extends GamePoint
{
	public GamePosition()
	{
		super();
	}

	public GamePosition(float x, float y)
	{
		super(x, y);
	}

	public GamePosition(GamePoint pofloat)
	{
		this(pofloat.getX(), pofloat.getY());
	}

	public boolean equals(GamePosition position)
	{
		return (getX() == position.getX() && getY() == position.getY());
	}

	public GamePosition add(GamePosition position)
	{
		setX(getX() + position.getX());
		setY(getY() + position.getY());
		return this;
	}

	public GamePosition subtract(GamePosition position)
	{
		setX(getX() - position.getX());
		setY(getY() - position.getY());
		return this;
	}

	public GamePosition plus(GamePosition position)
	{
		return new GamePosition(getX() + position.getX(), getY() + position.getY());
	}

	public GamePosition minus(GamePosition position)
	{
		return new GamePosition(getX() - position.getX(), getY() - position.getY());
	}

	public boolean inGameRect(GamePosition pos, GameSize size)
	{
		return getX() >= pos.getX()
			&& getX() <= pos.getX() + size.getX()
			&& getY() >= pos.getY()
			&& getY() <= pos.getY() + size.getY();
	}

	public boolean inGameRect(GameRect rect)
	{
		return inGameRect(rect.getGamePosition(), rect.getGameSize());
	}
}
