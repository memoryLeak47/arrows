/*
	
*/
package game.player;

import game.Entity;
import game.Team;
import game.avatar.Avatar;
import game.skill.Skill;
import game.item.Item;
import network.lobby.LobbyPlayer;

public class MinimizedGamePlayer extends Entity implements java.io.Serializable
{
	private String name;
	private int rank;
	private Avatar avatar;
	private Team team;
	private Skill[] skills;
	private Item[] items;

	public MinimizedGamePlayer(LobbyPlayer player)
	{
		name = player.getName();
		rank = player.getRank();
		avatar = player.getAvatar();
		team = player.getTeam();
		skills = player.getSkills();
		items = player.getItems();
	}
}
