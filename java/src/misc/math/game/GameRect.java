package misc.math.game;

import misc.Debug;
import misc.math.game.GameVector;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;

public class GameRect
{
	private GamePosition position;
	private GameSize size;

	public GameRect(GamePosition position, GameSize size)
	{
		this.position = new GamePosition(position);
		this.size = new GameSize(size);
	}

	public GameRect(GameRect rect)
	{
		this(rect.getPosition(), rect.getSize());
	}

	public GameRect(float x, float y, float w, float h)
	{
		this(new GamePosition(x, y), new GameSize(w, h));
	}

	public GameRect(GameVector p1, GameVector p2)
	{
		position = new GamePosition(p1);
		size = new GameSize(p1.minus(p2));
	}

	public GameRect()
	{
		this(new GamePosition(0,0), new GameSize(0,0));
	}

	public boolean equals(GameRect rect)
	{
		return (getPosition().equals(rect.getPosition()) && getSize().equals(rect.getSize()));
	}

	public void setPosition(GameVector point) { position = new GamePosition(point); }
	public void setPosition(float x, float y) { position = new GamePosition(x, y); }
	public void setSize(GameVector point) { size = new GameSize(point); }
	public void setSize(float x, float y) { size = new GameSize(x, y); }

	public final float getBot() { return (getY() + getHeight()/2); }
	public final float getLeft() { return getX() - getWidth()/2; }
	public final float getRight() { return (getX() + getWidth()/2); }
	public final float getTop() { return getY() - getHeight()/2; }

	public GamePosition getPosition() { return position; }
	public float getX() { return getPosition().getX(); }
	public float getY() { return getPosition().getY(); }

	public GameSize getSize() { return size; }
	public float getWidth() { return getSize().getX(); }
	public float getHeight() { return getSize().getY(); }
}
