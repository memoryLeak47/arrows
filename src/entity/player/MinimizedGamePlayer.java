/*
	
*/
package entity.player;

import entity.Entity;
import misc.game.Team;
import misc.game.kill.KDCounter;
import playerproperty.avatar.Avatar;
import playerproperty.skill.Skill;
import playerproperty.item.Item;
import network.lobby.LobbyPlayer;

public class MinimizedGamePlayer extends Entity implements java.io.Serializable
{
	private String name;
	private int rank;
	private Avatar avatar;
	private Team team;
	private Skill[] skills;
	private Item[] items;

	private KDCounter kdCounter = new KDCounter();

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
