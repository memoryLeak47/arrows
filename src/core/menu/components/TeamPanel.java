package core.menu.components;

import core.menu.Menu;
import core.menu.ComponentContainer;
import core.menu.components.Button;
import core.menu.components.Panel;
import game.Team;
import misc.math.Rect;

public class TeamPanel extends Panel
{
	private Team team;

	public TeamPanel(ComponentContainer parent, Rect rect, Team team)
	{
		super(parent, rect);
		this.team = team;
		getComponents().add(new Button(this, new Rect(20, 20, 100, 30), "Team " + team.getName()));
	}
}
