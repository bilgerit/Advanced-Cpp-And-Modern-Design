// Proxy Pattern
// 
// We create an abstract base class Account, and derive RealAccount.
// We equally derive ProtectedAccount from Account, but
// also give it a RealAccount member.
// The ProtectedAccount herein forms a proxy through which we can
// access a RealAccount in a specific manner.
// 
// Tobias Bilgeri, 10.02.2024
#pragma once
#include <iostream>

#include "NoAccessException.h"
#include "NoFundsException.h"
#include "ProtectedAccount.h"


int main() {
	{
		// real account
		std::cout << "\nReal Account:\n";

		// create account, check balance
		RealAccount account(100.);
		std::cout << "Balance: " << account.GetBalance() << std::endl;

		// withdraw some money
		account.Withdraw(50.);
		std::cout << "Balance: " << account.GetBalance() << std::endl;
	}


	{
		// protected account
		std::cout << "\nProtected Account:\n";
		ProtectedAccount account(100.0, "password");

		try {
			// withdraw some money, check balance with valid password
			account.Withdraw(100.);
			std::cout << "Balance: " << account.GetBalance("password") << std::endl;

			// check balance with incorrect password
			std::cout << "Balance: " << account.GetBalance("wrong") << std::endl;
		}
		catch (const NoAccessException&) {
			std::cout << "No access to get the balance." << std::endl;
		}

		try
		{
			// try withdrawing more than available
			account.Withdraw(100.);
		}
		catch (const NoFundsException&) {
			std::cout << "Not enough funds to withdraw." << std::endl;
		}
	}

    return 0;
}
