#include "TeamPanel.hpp"

#include "PlayerPanel.hpp"
#include "../../misc/Debug.hpp"

TeamPanel::TeamPanel(TeamListPanel* c, const PixelRect& r, Team* team) : Panel(c, r), team(team)
{
	teamButton = NULL; // otherwise the program crashes
}

void TeamPanel::update(const std::vector<LobbyPlayer*>& players)
{
	bool buttonWasEnabled = (teamButton == NULL || teamButton->isEnabled());

	getComponents().clear();
	class TeamButton : public Button
	{
		public:
			TeamButton(TeamPanel* c, const PixelRect& r, const std::string& h) : Button(c, r, h) {}
			void onClick(int mouseButton) override
			{
				Debug::test("hello, you pressed mr. " + getText());
				if (isEnabled())
				{
					((TeamPanel*) getParent())->getLobbyMenu()->teamPressed(((TeamPanel*)getParent())->getTeam()); // Übergabe an LobbyMenu, dass wir Team wechseln
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
			addComponent(new PlayerPanel(this, PixelRect(getRelativeRect().getPosition().getX() + 5 + c*65, 55, 60, 60), players[i]));
			c++;
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
