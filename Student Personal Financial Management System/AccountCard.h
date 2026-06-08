#pragma once
#include "BasicWidget.h"
#include "Text.h"
#include "Button.h"
#include "TextBox.h"
#include "Account.h"
#include <string>

class AccountCard : public BasicWidget {
private:
	Account* m_account;
	Text* m_name;
	Text* m_balance;
	Button* m_editBtn;
	TextBox* m_editBox;
	bool m_isEditing;
	COLORREF m_iconColor;
	std::wstring m_icon;
	ExMessage m_localMsg;
	bool m_wasEditing;

	void updateBalanceText();

public:
	AccountCard(Account* account, int x = 0, int y = 0, int w = 700, int h = 80);
	~AccountCard();

	void show() override;
	void eventLoop(ExMessage& msg);

	Account* getAccount() const { return m_account; }
	void setAccount(Account* account) { m_account = account; }
	void setBalance(double balance);
	bool isEditing() const { return m_isEditing; }
	void finishEditing();
};
