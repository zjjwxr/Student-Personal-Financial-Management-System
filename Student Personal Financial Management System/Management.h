#pragma once
#include "Configure.h"
#include "Button.h"
#include "TextBox.h"
#include "Window.h"
#include "User.h"
#include "SideBar.h"
#include "TopBar.h"
#include "Login_Register.h"
#include "MoneyCard.h"
#include "Chart.h"
#include "Tab.h"
#include "Select.h"
#include "Table.h"
#include "AccountCard.h"
#include "Transaction.h"
#include "Account.h"
#include <vector>
class TransactionManager;
class Management {
	enum State {
		LOGIN,
		REGISTERUSER,
		MENU,
		ACCOUNT,
		TRANSACTION,
		TABLE,
		SETTING,
		EXIT
	};
public:
	Management();
	void run();// 运行系统
	void login(); // 登录系统
	void registerUser();// 注册账号
	void menu(); //首页
	void account();
	void transaction();
	void table();
	void setting();
private:
	State currentState=LOGIN;
	IMAGE m_background;
	inline static ExMessage m_msg;

	

	//用于用户登录
	LoginRegister m_loginRegister;

	User m_user;
	

	SideBar* m_sideBar;
	TopBar* m_topBar;

	// 概况页面组件
	MoneyCard* m_incomeCard;
	MoneyCard* m_expenseCard;
	MoneyCard* m_balanceCard;
	Chart* m_pieChart;
	Chart* m_lineChart;

	// 记账页面组件
	Tab* m_transactionTab;
	Select* m_categorySelect;
	Select* m_accountSelect;
	TextBox* m_amountTextBox;
	TextBox* m_dateTextBox;
	TextBox* m_descriptionTextBox;
	Button* m_saveTransactionButton;

	// 表单页面组件
	TextBox* m_startDateTextBox;
	TextBox* m_endDateTextBox;
	Select* m_filterCategorySelect;
	Select* m_filterAccountSelect;
	Button* m_filterButton;
	Table* m_transactionTable;

	// 账户管理页面组件
	MoneyCard* m_totalBalanceCard;
	std::vector<AccountCard*> m_accountCards;
	Button* m_addAccountButton;
	TextBox* m_addAccountNameTextBox;
	TextBox* m_addAccountBalanceTextBox;
	Button* m_confirmAddAccountButton;
	Button* m_cancelAddAccountButton;
	bool m_showAddAccountDialog;
};

