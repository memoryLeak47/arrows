package core.menu.menues;

import core.Main;
import core.menu.Menu;
import core.menu.components.*;
import misc.Account;
import misc.math.Rect;

public class LoginMenu extends Menu
{
	private EditField usernameField, passwordField;

	public LoginMenu()
	{
		getComponents().add(new Label(this, new Rect(350, 20, 100, 20), "Login"));
		getComponents().add(usernameField = new EditField(this, new Rect(350, 200, 100, 20)));
		getComponents().add(passwordField = new PasswordField(this, new Rect(350, 230, 100, 20)));
		getComponents().add(new Button(this, new Rect(350, 260, 40, 20), "Login")
		{
			@Override public void onClick(int mouseButton)
			{
				Account account = Account.get(usernameField.getText(), passwordField.getText());
				if (account != null)
				{
					Main.setAccount(account);
					Main.getMenues().add(new MainMenu());
				}
				else
				{
					popup("wrong username password combination");
				}
			}
		});
		getComponents().add(new Button(this, new Rect(410, 260, 40, 20), "Sign in")
		{
			@Override public void onClick(int mouseButton)
			{
				if (Account.add(usernameField.getText(), passwordField.getText()))
				{
					Main.getMenues().add(new MainMenu());
				}
				else
				{
					popup("Username already used.");
				}
			}
		});
		getComponents().add(new QuitButton(this, new Rect(20, 500, 100, 30)));
	}
}
