/*
	Stellt Funktionen zur Verfügung, die für das Rendern benutzt werden
*/

package player;

import java.util.LinkedList;

import graphics.ImageID;
import misc.math.game.GamePosition;
import misc.math.game.GameSize;
import player.property.skill.Skill;
import player.property.Team;

public interface GamePlayer
{
	public String getName();
	public Team getTeam();
	public float getHealth();
	public GamePosition getPosition();
	public GameSize getSize();
	public ImageID getImageID();
	public boolean[] getEffectIDs(); // gibt die EffectIDs zurück, die für das Rendern gebraucht werden
	public Skill[] getSkills();
}
