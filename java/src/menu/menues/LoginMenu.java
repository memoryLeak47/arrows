package menu.menues;

import core.Main;
import menu.Menu;
import menu.components.*;
import misc.Account;
import misc.math.pixel.PixelRect;

public class LoginMenu extends Menu
{
	private EditField usernameField, passwordField;

	public LoginMenu()
	{
		getComponents().add(new Label(this, new PixelRect(350, 20, 100, 20), "Login"));
		getComponents().add(usernameField = new EditField(this, new PixelRect(350, 200, 100, 20)));
		getComponents().add(passwordField = new PasswordField(this, new PixelRect(350, 230, 100, 20)));
		getComponents().add(new Button(this, new PixelRect(350, 260, 40, 20), "Login")
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
		getComponents().add(new Button(this, new PixelRect(410, 260, 40, 20), "Sign in")
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
		getComponents().add(new QuitButton(this, new PixelRect(20, 500, 100, 30)));
	}
}
