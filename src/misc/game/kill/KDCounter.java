package misc.game.kill;

public class KDCounter
{
	private int kills, deaths;

	public KDCounter()
	{
		kills = 0;
		deaths = 0;
	}


	public int getKills() { return kills; }
	public int getDeaths() { return deaths; }

	public void kill() { kills++; }
	public void death() { deaths++; }
}
