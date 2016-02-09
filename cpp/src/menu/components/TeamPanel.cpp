#include "TeamPanel.hpp"

#include "PlayerPanel.hpp"
#include "../../misc/Debug.hpp"

TeamPanel::TeamPanel(LobbyMenu* m, TeamListPanel* c, const PixelRect& r, Team* team) : Panel(c, r), team(team), lobby(m)
{
	teamButton = NULL; // otherwise the program crashes
}

void TeamPanel::update(const std::vector<LobbyPlayer*>& players)
{
	bool buttonWasEnabled = (teamButton == NULL || teamButton->isEnabled());

	clearComponents();
	class TeamButton : public Button
	{
		public:
			TeamButton(TeamPanel* c, const PixelRect& r, const std::string& h) : Button(c, r, h) {}
			virtual void onPress() override
			{
				if (isEnabled())
				{
					((TeamPanel*) getParent())->getLobbyMenu()->teamPressed(((TeamPanel*) getParent())->getTeam()); // Übergabe an LobbyMenu, dass wir Team wechseln
				}
			}
	};
	addComponent(teamButton = new TeamButton(this, PixelRect(20, 20, 100, 30), "Team " + team->getName()));

	teamButton->setEnabled(buttonWasEnabled);

	int c = 0;
	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->getTeamUserPacket()->getTeam() == team)
		{
			addComponent(new PlayerPanel(players[i], getLobbyMenu(), this, PixelRect(getRelativeRect().getPosition().getX() + 5 + c*65, 55, 60, 60)));
			c++;
		}
	}
}

LobbyMenu* TeamPanel::getLobbyMenu() const
{
	return lobby;
}

Team* TeamPanel::getTeam() const
{
	return team;
}

void TeamPanel::disableTeamButton()
{
	teamButton->setEnabled(false);
}
