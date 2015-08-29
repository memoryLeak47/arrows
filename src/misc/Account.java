package misc;

import java.io.File;
import java.io.Serializable;
import java.util.LinkedList;

import core.Main;
import misc.Debug;
import static misc.Serializer.*;

public final class Account implements Serializable
{
	public static final String accounts_filename = ".accounts";

	private String name, password;
	private int rank, budget;
	// TODO add bought stuff

	public Account(String name, String password)
	{
		this.name = name;
		this.password = password;
		this.rank = 0;
		this.budget = 0;
	}

	public static boolean add(String name, String password) // called when new user is created, returns false if name already used
	{
		LinkedList<Account> accounts = getAccounts();
		if (nameFree(name, accounts))
		{
			Account account = new Account(name, password);
			accounts.add(account);
			writeAccountsFile(accounts);
			Main.setAccount(account);
			return true;
		}
		return false;
	}

	public static void updateAccount(Account account) // called when user quits arrows
	{
		LinkedList<Account> accounts = getAccounts();
		if (!nameFree(account.getName(), accounts))
		{
			accounts.remove(getByName(account.getName(), accounts));
			accounts.add(account);
			writeAccountsFile(accounts);
		}
		else
		{
			Debug.quit("account-name not chosen yet");
		}
	}

	public static Account get(String name, String password) // needed for normal login
	{
		LinkedList<Account> accounts = getAccounts();
		Account account = getByName(name, accounts);
		if (account == null)
		{
			return null;
		}
		if (account.getPassword().equals(password))
		{
			return account;
		}
		return null;
	}

	private static Account getByName(String name, LinkedList<Account> accounts)
	{
		for (Account account : accounts)
		{
			if (account.getName().equals(name))
			{
				return account;
			}
		}
		return null;
	}

	private static LinkedList<Account> getAccounts()
	{
		if (!new File(accounts_filename).isFile())
		{
			return new LinkedList<Account>();
		}
		LinkedList<Account> accounts = (LinkedList<Account>) fileToObject(new File(accounts_filename));
		if (accounts != null)
		{
			return accounts;
		}
		return new LinkedList<Account>();
	}

	private static void writeAccountsFile(LinkedList<Account> accounts)
	{
		objectToFile(accounts, new File(accounts_filename));
	}

	private static boolean nameFree(String name, LinkedList<Account> accounts)
	{
		return (getByName(name, accounts) == null);
	}

	public String getName() { return name; }
	public String getPassword() { return password; }
	public int getRank() { return rank; }
}
