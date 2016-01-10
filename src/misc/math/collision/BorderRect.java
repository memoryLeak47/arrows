package misc.math.collision;

import misc.Debug;
import misc.math.game.GameVector;

public class BorderRect
{
	private float left, right, top, bot;

	public BorderRect(float left, float right, float top, float bot)
	{
		this.left = left;
		this.right = right;
		this.top = top;
		this.bot = bot;
		Debug.warnIf(!isValid(), "BorderRect.<init>(float, float, float, float): invalid BorderRect");
	}

	public BorderRect(BorderRect rect)
	{
		left = rect.getLeft();
		right = rect.getRight();
		top = rect.getTop();
		bot = rect.getBot();
		Debug.warnIf(!isValid(), "BorderRect.<init>(BorderRect): invalid BorderRect");
	}

	public boolean isValid()
	{
		return (getLeft() < getRight() && getTop() < getBot());
	}

	public boolean contains(GameVector vec)
	{
		return (vec.getX() < right && vec.getX() > left && vec.getY() < bot && vec.getY() > top);
	}

	public static BorderRect getIntersection(BorderRect rect1, BorderRect rect2)
	{
		return new BorderRect(
			Math.max(rect1.getLeft(), rect2.getLeft()),
			Math.min(rect1.getRight(), rect2.getRight()),
			Math.max(rect1.getTop(), rect2.getTop()),
			Math.min(rect1.getBot(), rect2.getBot()));
	}

	public float getLeft() { return left; }
	public float getRight() { return right; }
	public float getTop() { return top; }
	public float getBot() { return bot; }
}
