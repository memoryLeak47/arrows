package misc.math.game;

import misc.compress.*;
import misc.math.game.GameVector;

public class GamePosition extends GameVector
{
	public GamePosition()
	{
		super();
	}

	public GamePosition(float x, float y)
	{
		super(x, y);
	}

	public GamePosition(GameVector point)
	{
		this(point.getX(), point.getY());
	}

	public GamePosition(CompressBuffer buffer)
	{
		super(buffer);
	}

	@Override public byte getCID() { return Compressor.GAME_POSITION_CID; }

	public GamePosition timesX(float s)
	{
		return new GamePosition(super.timesX(s));
	}

	public GamePosition timesY(float s)
	{
		return new GamePosition(super.timesY(s));
	}

	public GamePosition plus(GameVector position)
	{
		return new GamePosition(super.plus(position));
	}

	public GamePosition plusX(float f)
	{
		return new GamePosition(super.plusX(f));
	}

	public GamePosition plusY(float f)
	{
		return new GamePosition(super.plusY(f));
	}

	public GamePosition minus(GameVector position)
	{
		return new GamePosition(super.minus(position));
	}

	public GamePosition times(float s)
	{
		return new GamePosition(super.times(s));
	}

	public GamePosition divide(float s)
	{
		return new GamePosition(super.divide(s));
	}
}
