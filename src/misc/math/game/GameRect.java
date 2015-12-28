package misc.math.game;

import misc.Debug;
import misc.math.game.GamePoint;
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
		this(rect.getGamePosition(), rect.getGameSize());
	}

	public GameRect(float x, float y, float w, float h)
	{
		this(new GamePosition(x, y), new GameSize(w, h));
	}

	public GameRect(GamePoint p1, GamePoint p2)
	{
		position = new GamePosition(p1);
		size = new GameSize(p1.minus(p2));
	}

	public GameRect()
	{
		this(new GamePosition(0,0), new GameSize(0,0));
	}

	public float distanceTo(GamePoint point)
	{
		Debug.error("GameRect.distanceTo(GamePoint) not coded yet");
		// TODO
		return 2;
	}

	public void centerX(float width)
	{
		float left;
		left = (float)((width - this.getWidth()) / 2);
		setLeft(left);
	}

	public void centerY(float height)
	{
		float top;
		top = (float)((height - this.getHeight()) / 2);
		setTop(top);
	}

	// zentriert die Komponente im übergebenen GameRectangle
	public void center(GameRect rect)
	{
		centerX(rect);
		centerY(rect);
	}

	// zentriert die Komponente im übergebenen GameRectangle in X-Richtung
	public void centerX(GameRect rect)
	{
		float left;
		left = (float)((rect.getWidth() - this.getWidth()) / 2);
		setLeft(rect.getLeft() + left);
	}

	// zentriert die Komponente im übergebenen GameRectangle in Y-Richtung
	public void centerY(GameRect rect)
	{
		float top;
		top = (float)((rect.getHeight() - this.getHeight()) / 2);
		setTop(rect.getTop() + top);
	}

	public boolean equals(GameRect rect)
	{
		return (getGamePosition().equals(rect.getGamePosition()) && getGameSize().equals(rect.getGameSize()));
	}

	public void setGamePosition(GamePoint point) { position = new GamePosition(point); }
	public void setGamePosition(float x, float y) { position = new GamePosition(x, y); }
	public void setGameSize(GamePoint point) { size = new GameSize(point); }
	public void setGameSize(float x, float y) { size = new GameSize(x, y); }
	public void setLeft(float left) { getGamePosition().setX(left); }
	public void setTop(float top) { getGamePosition().setX(top); }
	public void setWidth(float width) { getGameSize().setX(width); }
	public void setHeight(float height) { getGameSize().setY(height); }

	public final float getBot() { return (getY() + getHeight()); }
	public final float getLeft() { return getX(); }
	public final float getRight() { return (getX() + getWidth()); }
	public final float getTop() { return getY(); }
	public float getX() { return getGamePosition().getX(); }
	public float getY() { return getGamePosition().getY(); }
	public float getWidth() { return getGameSize().getX(); }
	public float getHeight() { return getGameSize().getY(); }
	public GameSize getGameSize() { return size; }
	public GamePosition getGamePosition() { return position; }
}
