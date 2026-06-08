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
#include "Table.h"
#include "Transaction.h"
#include "Account.h"
#include "Select.h"
#include "LineChart.h"
#include"FileManager.h"
#include "AccountCard.h"

#include <vector>
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
	
	// 辅助函数：获取指定日期范围内的统计
	static bool isDateInRange(const std::wstring& date, const std::wstring& startDate, const std::wstring& endDate);
	// 辅助函数：解析日期字符串为年月日
	static void parseDate(const std::wstring& date, int& year, int& month, int& day);
	// 辅助函数：获取当前月的第一天和最后一天
	static void getCurrentMonthRange(std::wstring& firstDay, std::wstring& lastDay);
	// 辅助函数：获取当前月的天数
	static int getDaysInCurrentMonth();
private:
	State currentState=LOGIN;
	IMAGE m_background;
	inline static ExMessage m_msg;


	//用于用户登录
	LoginRegister m_loginRegister;
    User* m_currentUser;

	//任务栏和顶部栏
	SideBar* m_sideBar;
	TopBar* m_topBar;

	//用于概况MENU界面
	std::vector<MoneyCard*> m_moneyCards;
	LineChart* m_expenseChart;

	//用于表单TABLE界面
    Table m_transactionsTable;

	//表单界面的筛选控件
	std::vector<Text*> m_filterLabels;
	std::vector<TextBox*> m_filterTextBoxes;
	Button* m_filterButton;
	Select* m_filterAccountSelect;      // 账户筛选
	Select* m_filterTypeSelect;          // 类型筛选（收入/支出/全部）
	TextBox* m_filterStartDateTextBox;   // 开始日期（格式：2026-6-24）
	TextBox* m_filterEndDateTextBox;     // 结束日期（格式：2026-6-24）
	Text* m_filterDateLabel;             // 日期区间标签
    
	// 记账页面组件
	
	Select* m_categorySelect;
	Select* m_accountSelect;
	TextBox* m_amountTextBox;
	TextBox* m_ydateTextBox;
	TextBox* m_mdateTextBox;
	TextBox* m_rdateTextBox;
	TextBox* m_descriptionTextBox;
	Button* m_saveTransactionButton;
	Button* m_expenseButton;
	Button* m_incomeButton;

	//设置页面
	Button* m_gotologinButton;
	Button* m_exitButton;
	


	//用于账户ACCOUNT界面
	std::vector<AccountCard*> m_accountCards;
	Text* m_totalBalanceLabel;
	Text* m_totalBalanceValue;

	//记账页面状态
	int m_selectedTransactionType;
	int m_errorType;
};

