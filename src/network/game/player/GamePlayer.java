/*
	Stellt Funktionen zur Verfügung, die für das Rendern benutzt werden
*/

package network.game.player;

import java.util.LinkedList;

import static core.Main.PLAYERSIZE_X;
import static core.Main.PLAYERSIZE_Y;
import graphics.ImageID;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import misc.game.Team;

public interface GamePlayer
{
	public String getName();
	public Team getTeam();
	public int getHealth();
	public GamePosition getPosition();
	public GameSize getSize();
	public ImageID getImageID();
	public LinkedList<Integer> getEffectIDs(); // gibt die EffectIDs zurück, die für das Rendern gebraucht werden
}
