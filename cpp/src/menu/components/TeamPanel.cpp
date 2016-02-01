#include "TeamPanel.hpp"

#include "PlayerPanel.hpp"

TeamPanel::TeamPanel(TeamListPanel* c, const PixelRect& r, Team* team) : Panel(c, r), team(team)
{}

void TeamPanel::update(const std::vector<LobbyPlayer*>& players)
{
	bool buttonWasEnabled;
	if (teamButton == NULL)
		buttonWasEnabled = true;
	else
		buttonWasEnabled = teamButton->isEnabled();

	getComponents().clear();
	class TeamButton : public Button
	{
		public:
			TeamButton(TeamPanel* c, const PixelRect& r, const std::string& h) : Button(c, r, h) {}
			void onClick(int mouseButton) override
			{
				if (isEnabled())
					((TeamPanel*) getParent())->getLobbyMenu()->teamPressed(((TeamPanel*)getParent())->getTeam()); // Übergabe an LobbyMenu, dass wir Team wechseln
			}
	};
	addComponent(teamButton = new TeamButton(this, PixelRect(20, 20, 100, 30), "Team " + team->getName()));

	teamButton->setEnabled(buttonWasEnabled);

	for (int i = 0; i < players.size(); i++)
	{
		if (players[i]->getTeamUserPacket()->getTeam() == team)
		{
			addComponent(new PlayerPanel(this, PixelRect(getRect().getPosition().getX() + 5 + i*65, 55, 60, 60), players[i]));
		}
	}
}

LobbyMenu* TeamPanel::getLobbyMenu() const
{
	return ((TeamListPanel*) getParent())->getLobbyMenu();
}

Team* TeamPanel::getTeam() const
{
	return team;
}
