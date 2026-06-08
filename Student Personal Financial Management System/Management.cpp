#include "Management.h"
#include <iomanip>
#include <ctime>
#include <sstream>
#include <locale>

Management::Management() {
	
	m_currentUser = nullptr;
	::loadimage(&m_background, _T("./images/background.png"), Window::width(), Window::height());

	//概况MENU界面 - 初始化本月每日支出折线图（右下角）
	m_expenseChart = new LineChart(200, 200, 740, 400);
	m_expenseChart->setTitle(L"本月支出趋势");

	//概况MENU界面 - 初始化三个统计卡片
	m_moneyCards.push_back(new MoneyCard(L"本月收入", 0, 200, 80, 230, 90));
	m_moneyCards.push_back(new MoneyCard(L"本月支出", 0, 455, 80, 230, 90));
	m_moneyCards.push_back(new MoneyCard(L"结余", 0, 710, 80, 230, 90));
	m_moneyCards[0]->setAmountColor(RGB(124, 179, 66));
	m_moneyCards[1]->setAmountColor(RGB(255, 107, 107));
	m_moneyCards[2]->setAmountColor(RGB(46, 125, 255));

	//表单TABLE界面
    m_transactionsTable = Table(270, 180);
    m_transactionsTable.SetRowCol(10, 3);
    m_transactionsTable.SetColumnWidths({220 , 150, 220});
    m_transactionsTable.SetHeaders({L"日期", L"支付渠道", L"金额"});
    m_transactionsTable.SetRowHeight(35);
    m_transactionsTable.SetHeaderHeight(35);
    m_transactionsTable.SetPaginationHeight(50);
    m_transactionsTable.UpdateVisibleRows(Window::height() - 110 - 50 - 100);
    m_transactionsTable.SetColorTheme(
        RGB(224, 224, 224), 
        RGB(248, 249, 250), 
        RGB(102, 102, 102), 
        WHITE, 
        BLACK
    );
	// 初始化表单筛选控件
	m_filterAccountSelect = new Select(200, 110, 150, 30);
	m_filterAccountSelect->addOption(L"全部账户");
	m_filterAccountSelect->addOption(L"微信");
	m_filterAccountSelect->addOption(L"支付宝");
	m_filterAccountSelect->addOption(L"银行卡");
	m_filterAccountSelect->addOption(L"现金");

	m_filterTypeSelect = new Select(360, 110, 150, 30);
	m_filterTypeSelect->addOption(L"全部");
	m_filterTypeSelect->addOption(L"收入");
	m_filterTypeSelect->addOption(L"支出");

	// 日期区间控件
	m_filterDateLabel = new Text(L"日期区间：");
	m_filterDateLabel->setPosition(565, 118);
	m_filterDateLabel->setFixedSize(20);

	m_filterStartDateTextBox = new TextBox(650, 110, 120, 30);
	m_filterEndDateTextBox = new TextBox(800, 110, 120, 30);
    
	// 初始化记账页面组件
	
	m_expenseButton = new Button(L"支出", Window::width() / 2 - 80, 100, 150, 40);
	m_expenseButton->setTextColor(WHITE);
	m_expenseButton->setHoverColor(RGB(76, 175, 80));

	
	

	m_incomeButton = new Button(L"收入", Window::width() / 2 + 130, 100, 150, 40);
	m_incomeButton->setTextColor(WHITE);
	m_incomeButton->setHoverColor(RGB(244, 67, 54));

	

	m_accountSelect = new Select(Window::width() / 2 - 100, 200, 400, 35);
	m_accountSelect->addOption(L"微信");
	m_accountSelect->addOption(L"支付宝");
	m_accountSelect->addOption(L"银行卡");
	m_accountSelect->addOption(L"现金");

	m_amountTextBox = new TextBox(Window::width() / 2 - 100, 300, 400, 35);

	m_ydateTextBox = new TextBox(Window::width() / 2 - 100, 400, 80, 35);
	m_mdateTextBox = new TextBox(Window::width() / 2 +30, 400, 80, 35);
	m_rdateTextBox = new TextBox(Window::width() / 2 +170, 400, 80, 35);

	m_saveTransactionButton = new Button(L"保存", Window::width() / 2-10 , 500, 200, 40);
	m_saveTransactionButton->setTextColor(WHITE);
	m_saveTransactionButton->setDefaultColor(RGB(46, 125, 255));
	m_saveTransactionButton->setHoverColor(RGB(30, 100, 220));

	// 初始化记账页面状态
	m_selectedTransactionType = 1;  // 默认选中支出
	m_errorType = 0;                //错误类型
	// 设置日期默认值为当前日期
	time_t now = time(nullptr);
	tm t_info;
	localtime_s(&t_info, &now);
	wchar_t yearBuf[5], monthBuf[3], dayBuf[3];
	swprintf(yearBuf, 5, L"%d", t_info.tm_year + 1900);
	swprintf(monthBuf, 3, L"%d", t_info.tm_mon + 1);
	swprintf(dayBuf, 3, L"%d", t_info.tm_mday);
	m_ydateTextBox->setText(yearBuf);
	m_mdateTextBox->setText(monthBuf);
	m_rdateTextBox->setText(dayBuf);

	//设置界面
	m_gotologinButton = new Button(L"返回登录", Window::width() / 2 - 10, 300, 200, 40);
	m_saveTransactionButton->setTextColor(WHITE);
	m_saveTransactionButton->setDefaultColor(RGB(46, 125, 255));
	m_saveTransactionButton->setHoverColor(RGB(30, 100, 220));

	m_exitButton = new Button(L"退出", Window::width() / 2 - 10, 500, 200, 40);
	m_saveTransactionButton->setTextColor(WHITE);
	m_saveTransactionButton->setDefaultColor(RGB(46, 125, 255));
	m_saveTransactionButton->setHoverColor(RGB(30, 100, 220));
}

void Management::run() {
	currentState = LOGIN;
	Window::beginDraw();
	while (true) {
		Window::clear();
		Window::drawBackground(m_background);
		if (Window::hasMessage()) {
			m_msg = Window::getMessage();
		}
		else m_msg.message = 0;//没有消息时，重置消息，防止上次的消息影响当前界面
		m_loginRegister.setMessage(m_msg);
		switch (currentState) {
		case LOGIN:
			
			login();
			break;
		case REGISTERUSER:
			registerUser();
			break;
		case MENU:
			menu();
			break;
		case ACCOUNT:
			account();
			break;
		case TRANSACTION:
			transaction();
			break;
		case TABLE:
			table();
			break;
		case SETTING:
			setting();
			break;
		default:
			exit(0);
			break;
		}
		Window::flushDraw();
	}
	Window::endDraw();
}

void Management::login() {
	
	m_loginRegister.drawLogin();           // 绘制界面
	m_loginRegister.handleLogin(reinterpret_cast<int&>(currentState));  // 处理逻辑
	if (currentState == MENU && m_loginRegister.getCurrentUser() != nullptr) {
		m_currentUser = m_loginRegister.getCurrentUser();
		// ===== 检查并创建用户数据文件 =====
		std::wstring username = m_currentUser->getUsername();
		std::wstring userDataDir = FileManager::getUserDataDirectory(username);

		// 检查用户数据目录是否存在
		if (!FileManager::fileExists(userDataDir)) {
			// 目录不存在，创建目录
			FileManager::createDirectory(userDataDir);
		}

		// 检查账户文件是否存在
		std::wstring accountsFile = FileManager::getUserAccountsFilePath(username);
		if (!FileManager::fileExists(accountsFile)) {
			// 账户文件不存在，创建默认账户
			// 默认创建四个账户：微信、支付宝、银行卡、现金，余额都为0
			std::wstring defaultAccounts = L"1|0\n2|0\n3|0\n4|0\n";  // 格式：账户类型,余额
			FileManager::writeTextToFile(accountsFile, defaultAccounts);
		}

		// 检查交易记录文件是否存在
		std::wstring transactionsFile = FileManager::getUserTransactionsFilePath(username);
		if (!FileManager::fileExists(transactionsFile)) {
			// 交易文件不存在，创建空文件（只写表头或为空）
			FileManager::writeTextToFile(transactionsFile, L"");
		}
		// 加载用户数据
		m_currentUser->loadAccounts();
		m_currentUser->loadTransactions();
	}
}

void Management::registerUser() {
	
	
	m_loginRegister.drawRegister();
	m_loginRegister.handleRegister(reinterpret_cast<int&>(currentState));
	if (currentState == MENU && m_loginRegister.getCurrentUser() != nullptr) {
		m_currentUser = m_loginRegister.getCurrentUser();
		// ===== 检查并创建用户数据文件 =====
		std::wstring username = m_currentUser->getUsername();
		std::wstring userDataDir = FileManager::getUserDataDirectory(username);

		// 检查用户数据目录是否存在
		if (!FileManager::fileExists(userDataDir)) {
			// 目录不存在，创建目录
			FileManager::createDirectory(userDataDir);
		}

		// 检查账户文件是否存在
		std::wstring accountsFile = FileManager::getUserAccountsFilePath(username);
		if (!FileManager::fileExists(accountsFile)) {
			// 账户文件不存在，创建默认账户
			
			std::wstring defaultAccounts = L"1|0\n2|0\n3|0\n4|0\n";  // 格式：账户类型,余额
			FileManager::writeTextToFile(accountsFile, defaultAccounts);
		}

		// 检查交易记录文件是否存在
		std::wstring transactionsFile = FileManager::getUserTransactionsFilePath(username);
		if (!FileManager::fileExists(transactionsFile)) {
			// 交易文件不存在，创建空文件（只写表头或为空）
			FileManager::writeTextToFile(transactionsFile, L"");
		}
		// 加载用户数据
		m_currentUser->loadAccounts();
		m_currentUser->loadTransactions();
	}
}



void Management::menu() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"概况");
	}
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(m_currentUser);
	}
	// 更新顶部栏标题
	m_topBar->setTitle(L"概况");
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	// 获取本月范围
	std::wstring currentMonthFirst, currentMonthLast;
	getCurrentMonthRange(currentMonthFirst, currentMonthLast);

	// 计算本月收入、支出和结余
	double income = 0, expense = 0;
	auto transactions = m_currentUser->getTransactions();

	// 初始化每日支出数据
	int daysInMonth = getDaysInCurrentMonth();
	std::vector<double> dailyExpenses(daysInMonth, 0);
	std::vector<std::wstring> dayLabels;
	for (int i = 1; i <= daysInMonth; i++) {
		dayLabels.push_back(std::to_wstring(i) + L"日");
	}

	for (Transaction* trans : transactions) {
		if (isDateInRange(trans->getDateString(), currentMonthFirst, currentMonthLast)) {
			if (trans->getType() == 2) {
				income += trans->getAmount();
			}
			else {
				expense += trans->getAmount();
				// 获取日期中的天数并加到对应日
				int y, m, d;
				parseDate(trans->getDateString(), y, m, d);
				if (d >= 1 && d <= daysInMonth) {
					dailyExpenses[d - 1] += trans->getAmount();
				}
			}
		}
	}

	// 更新卡片数据
	m_moneyCards[0]->setAmount(income);
	m_moneyCards[1]->setAmount(expense);
	m_moneyCards[2]->setAmount(income - expense);

	// 显示统计卡片
	for (auto card : m_moneyCards) {
		card->show();
	}

	// 更新并显示本月每日支出折线图
	m_expenseChart->setData(dailyExpenses, dayLabels);
	m_expenseChart->show();

	// 检查侧边栏是否切换了页面
	if (m_sideBar->getCurrentPage() == 1) {
		currentState = TRANSACTION;
	} else if (m_sideBar->getCurrentPage() == 2) {
		currentState = TABLE;
	} else if (m_sideBar->getCurrentPage() == 3) {
		currentState = ACCOUNT;
	} else if (m_sideBar->getCurrentPage() == 4) {
		currentState = SETTING;
	}
}

void Management::account() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"账户");
	}
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(m_currentUser);
	}
	m_topBar->setTitle(L"账户");
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	std::vector<Account*> accounts;
	if (m_accountCards.empty()) {
		m_currentUser->loadAccounts();
		accounts = m_currentUser->getAccounts();

		for (int i = 1; i <= 4; i++) {
			Account* acc = nullptr;
			for (auto a : accounts) {
				if (a->getAccountType() == i) {
					acc = a;
					break;
				}
			}
			m_accountCards.push_back(new AccountCard(acc, 200, 100 + i * 95, 740, 80));
		}
	}
	else {
		m_currentUser->loadAccounts();
		accounts = m_currentUser->getAccounts();

		for (int i = 0; i < m_accountCards.size(); i++) {
			AccountCard* card = m_accountCards[i];
			for (auto acc : accounts) {
				if (acc != nullptr && card != nullptr && acc->getAccountType() == (i + 1)) {
					card->setAccount(acc);
					break;
				}
			}
		}
	}

	if (!m_totalBalanceLabel) {
		m_totalBalanceLabel = new Text(L"总资产");
		m_totalBalanceLabel->setPosition(200, 85);
		m_totalBalanceLabel->setFixedSize(25);
		m_totalBalanceLabel->setColor(RGB(102, 102, 102));

		m_totalBalanceValue = new Text(L"¥0.00");
		m_totalBalanceValue->setPosition(200, 120);
		m_totalBalanceValue->setFixedSize(50);
		m_totalBalanceValue->setColor(RGB(46, 125, 255));
	}

	double totalBalance = 0;
	for (auto acc : accounts) {
		totalBalance += acc->getBalance();
	}
	std::wostringstream woss;
	woss.imbue(std::locale(""));
	woss << std::fixed << std::setprecision(2) << totalBalance;
	m_totalBalanceValue->setText(L"¥" + woss.str());

	m_totalBalanceLabel->show();
	m_totalBalanceValue->show();

	for (auto card : m_accountCards) {
		card->eventLoop(m_msg);
		card->show();
	}

	// 检查侧边栏是否切换了页面
	if (m_sideBar->getCurrentPage() == 0) {
		currentState = MENU;
	} else if (m_sideBar->getCurrentPage() == 1) {
		currentState = TRANSACTION;
	} else if (m_sideBar->getCurrentPage() == 2) {
		currentState = TABLE;
	} else if (m_sideBar->getCurrentPage() == 4) {
		currentState = SETTING;
	}
}

void Management::transaction() {

	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"记账");
	}
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(m_currentUser);
	}
	m_topBar->setTitle(L"记账");
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();
	setfillcolor(WHITE);
	solidrectangle(Window::width() / 2 - 130, 55, 800, 640);

	settextstyle(20, 0, _T("Microsoft YaHei"));
	settextcolor(RGB(51, 51, 51));
	outtextxy(Window::width() / 2 - 100, 170, _T("支付渠道"));

	settextstyle(20, 0, _T("Microsoft YaHei"));
	settextcolor(RGB(51, 51, 51));
	outtextxy(Window::width() / 2 - 100, 270, _T("金额"));

	settextstyle(20, 0, _T("Microsoft YaHei"));
	settextcolor(RGB(51, 51, 51));
	outtextxy(Window::width() / 2 - 100, 370, _T("日期"));

	settextstyle(30, 0, _T("Microsoft YaHei"));
	settextcolor(RGB(51, 51, 51));
	outtextxy(Window::width() / 2 - 10, 400, _T("年"));

	settextstyle(30, 0, _T("Microsoft YaHei"));
	settextcolor(RGB(51, 51, 51));
	outtextxy(Window::width() / 2 + 120, 400, _T("月"));

	settextstyle(30, 0, _T("Microsoft YaHei"));
	settextcolor(RGB(51, 51, 51));
	outtextxy(Window::width() / 2 + 260, 400, _T("日"));

	::settextstyle(26, 0, _T("微软雅黑"));
	int msgY = m_saveTransactionButton->getY() + m_saveTransactionButton->getHeight() - textheight(_T("保存失败，金额不能为空！")-150);
	if (m_errorType == 1) {
		settextcolor(RGB(255, 100, 100));
		int titleW = textwidth(_T("保存失败，金额不能为空！"));
		::outtextxy((Window::width() - titleW) / 2+110, msgY, _T("保存失败，金额不能为空！"));
	}
	else if (m_errorType == 2) {
		settextcolor(RGB(255, 100, 100));
		int titleW = textwidth(_T("保存失败，日期不能为空！"));
		::outtextxy((Window::width() - titleW) / 2+110, msgY, _T("保存失败，日期不能为空！"));
	}
	else if (m_errorType == 3) {
		settextcolor(RGB(255, 100, 100));
		int titleW = textwidth(_T("保存失败，该账户余额不足！"));
		::outtextxy((Window::width() - titleW) / 2 + 110, msgY, _T("保存失败，该账户余额不足！"));
	}
	m_amountTextBox->show();
	m_amountTextBox->eventLoop(m_msg);

	m_ydateTextBox->show();
	m_ydateTextBox->eventLoop(m_msg);

	m_mdateTextBox->show();
	m_mdateTextBox->eventLoop(m_msg);

	m_rdateTextBox->show();
	m_rdateTextBox->eventLoop(m_msg);

	m_expenseButton->show();
	m_expenseButton->eventLoop(m_msg);

	m_incomeButton->show();
	m_incomeButton->eventLoop(m_msg);

	m_saveTransactionButton->show();
	m_saveTransactionButton->eventLoop(m_msg);

	settextstyle(18, 0, _T("微软雅黑"));
	std::wstring r1 = L"请输入金额";
	
	if (m_amountTextBox->getText().empty()) {
		settextcolor(RGB(150, 150, 150));
		int x = m_amountTextBox->getX() + 10;
		int y = m_amountTextBox->getY() + (m_amountTextBox->getHeight() - textheight(r1.c_str())) / 2;
		outtextxy(x, y, r1.c_str());
	}

	m_accountSelect->show();
	m_accountSelect->eventLoop(m_msg);

	// ===== 更新收入/支出按钮样式 =====
	if (m_selectedTransactionType == 1) {  // 支出选中
		m_expenseButton->setDefaultColor(RGB(76, 175, 80));
		m_expenseButton->setTextColor(WHITE);
		m_incomeButton->setDefaultColor(RGB(200, 200, 200));
		m_incomeButton->setTextColor(RGB(80, 80, 80));
	}
	else {  // 收入选中
		m_incomeButton->setDefaultColor(RGB(244, 67, 54));
		m_incomeButton->setTextColor(WHITE);
		m_expenseButton->setDefaultColor(RGB(200, 200, 200));
		m_expenseButton->setTextColor(RGB(80, 80, 80));
	}

	// ===== 处理支出按钮点击 =====
	if (m_expenseButton->isClicked()) {
		m_selectedTransactionType = 1;  // 支出
	}

	// ===== 处理收入按钮点击 =====
	if (m_incomeButton->isClicked()) {
		m_selectedTransactionType = 2;  // 收入
	}

	// ===== 处理保存按钮 =====
	if (m_saveTransactionButton->isClicked()) {
		// 1. 获取金额并验证
		std::wstring amountText = m_amountTextBox->getText();
		if (amountText.empty())
		{
			m_errorType = 1;
			return;
		}

		double amount = _wtof(amountText.c_str());
		if (amount <= 0) return;

		// 2. 获取账户类型（将Select的文本转成int）
		std::wstring accountText = m_accountSelect->getSelectedText();
		int accountType = 1;  // 默认微信
		if (accountText == L"微信") accountType = 1;
		else if (accountText == L"支付宝") accountType = 2;
		else if (accountText == L"银行卡") accountType = 3;
		else if (accountText == L"现金") accountType = 4;

		// 3. 获取日期并验证
		std::wstring year = m_ydateTextBox->getText();
		std::wstring month = m_mdateTextBox->getText();
		std::wstring day = m_rdateTextBox->getText();
		if (year.empty() || month.empty() || day.empty()) {
			m_errorType = 2;
			return;
		}


		std::wstring date = year + L"-" + month + L"-" + day;

		// 4. 创建交易记录
		Transaction* trans = nullptr;
		try {
			m_currentUser->loadAccounts();
			auto accounts = m_currentUser->getAccounts();
			Account* targetAccount = nullptr;
			for (auto acc : accounts) {
				if (acc != nullptr && acc->getAccountType() == accountType) {
					targetAccount = acc;
					break;
				}
			}
			if (m_selectedTransactionType == 1) {  
				if (targetAccount->getBalance() < amount) {
					m_errorType = 3;
					return;
				}
			}			
				trans = new Transaction(m_currentUser, m_selectedTransactionType, date, accountType, amount);
				// 5. 保存到文件

				if (trans->addTransaction()) {

					// 6. 更新账户余额

					m_currentUser->loadAccounts();

					auto accounts = m_currentUser->getAccounts();

					for (auto acc : accounts) {

						if (acc != nullptr && acc->getAccountType() == accountType) {

							if (m_selectedTransactionType == 1) {  // 支出

								acc->withdraw(amount);
								m_errorType = 0;
							}

							else {  // 收入

								acc->deposit(amount);
								m_errorType = 0;
							}

							break;

						}

					}
					m_currentUser->saveAccounts();
					// 7. 清空输入框

					m_amountTextBox->setText(L"");

					m_ydateTextBox->setText(L"");

					m_mdateTextBox->setText(L"");

					m_rdateTextBox->setText(L"");

					// 8. 刷新用户数据

					m_currentUser->loadTransactions();

				}

			}
			catch (...) {

				// 处理异常

			}

		}
					
	if (m_sideBar->getCurrentPage() == 0) {
		currentState = MENU;
	}
	else if (m_sideBar->getCurrentPage() == 2) {
		currentState = TABLE;
	}
	else if (m_sideBar->getCurrentPage() == 3) {
		currentState = ACCOUNT;
	}
	else if (m_sideBar->getCurrentPage() == 4) {
		currentState = SETTING;
	}
}

void Management::table() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"表单");
	}
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(m_currentUser);
	}
	m_topBar->setTitle(L"表单");
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	// 显示筛选控件
	
	m_filterDateLabel->show();
	m_filterStartDateTextBox->show();
	m_filterStartDateTextBox->eventLoop(m_msg);
	m_filterEndDateTextBox->show();
	m_filterEndDateTextBox->eventLoop(m_msg);
	m_filterAccountSelect->eventLoop(m_msg);
	
	m_filterTypeSelect->eventLoop(m_msg);
	
	

	// 绘制日期分隔符
	::setlinecolor(BLACK);
	::line(775, 125, 795, 125);

	// 获取交易数据
	auto allTransactions = m_currentUser->getTransactions();

	// 应用筛选条件
	std::vector<Transaction*> filteredTransactions;
	std::wstring selectedAccount = m_filterAccountSelect->getSelectedText();
	std::wstring selectedType = m_filterTypeSelect->getSelectedText();

	// 获取日期区间
	std::wstring startDate = m_filterStartDateTextBox->getText();
	std::wstring endDate = m_filterEndDateTextBox->getText();

	for (auto trans : allTransactions) {
		bool passAccount = true;
		bool passType = true;
		bool passDate = true;

		// 账户筛选
		if (selectedAccount != L"全部账户") {
			std::wstring accountName = trans->getAccountName();
			if (accountName != selectedAccount) {
				passAccount = false;
			}
		}

		// 类型筛选
		if (selectedType == L"支出" && trans->getType() != 1) {
			passType = false;
		}
		if (selectedType == L"收入" && trans->getType() != 2) {
			passType = false;
		}

		// 日期区间筛选（格式：2026-6-24）
		if (!startDate.empty() && !endDate.empty()) {
			std::wstring transDate = trans->getDateString();
			if (transDate < startDate || transDate > endDate) {
				passDate = false;
			}
		}

		if (passAccount && passType && passDate) {
			filteredTransactions.push_back(trans);
		}
	}

	// 更新表格行数
	int rowCount;
	if (filteredTransactions.empty()) rowCount = 9;
	else rowCount = ((filteredTransactions.size() + 8) / 9) * 9;
	m_transactionsTable.UpdatePages();
	m_transactionsTable.SetRowCol(rowCount, 3);
	m_transactionsTable.SetColumnWidths({ 220,150,220 });

	// 填充数据
	m_transactionsTable.SetHeaders({ L"日期", L"支付渠道", L"金额" });
	for (size_t i = 0; i < filteredTransactions.size(); i++) {
		Transaction* trans = filteredTransactions[i];
		std::wstring amountStr;
		COLORREF amountColor;

		if (trans->getType() == 1) {
			amountStr = L"-" + std::to_wstring(trans->getAmount());
			amountColor = RGB(255, 107, 107); // 红色
		}
		else {
			amountStr = L"+" + std::to_wstring(trans->getAmount());
			amountColor = RGB(124, 179, 66); // 绿色
		}

		m_transactionsTable.SetCellText(i, 0, trans->getDateString());
		m_transactionsTable.SetCellText(i, 1, trans->getAccountName());
		m_transactionsTable.SetCellText(i, 2, amountStr, amountColor);
	}

	// 显示表格
	m_transactionsTable.eventLoop(m_msg);
	m_transactionsTable.show();
	m_filterAccountSelect->show();
	m_filterTypeSelect->show();
	// 检查侧边栏是否切换了页面
	if (m_sideBar->getCurrentPage() == 0) {
		currentState = MENU;
	}
	else if (m_sideBar->getCurrentPage() == 1) {
		currentState = TRANSACTION;
	}
	else if (m_sideBar->getCurrentPage() == 3) {
		currentState = ACCOUNT;
	}
	else if (m_sideBar->getCurrentPage() == 4) {
		currentState = SETTING;
	}
}


bool Management::isDateInRange(const std::wstring& date, const std::wstring& startDate, const std::wstring& endDate) {
	int y1, m1, d1, y2, m2, d2, y3, m3, d3;
	parseDate(date, y1, m1, d1);
	parseDate(startDate, y2, m2, d2);
	parseDate(endDate, y3, m3, d3);

	if (y1 < y2 || y1 > y3) return false;
	if (y1 == y2 && m1 < m2) return false;
	if (y1 == y3 && m1 > m3) return false;
	if (y1 == y2 && m1 == m2 && d1 < d2) return false;
	if (y1 == y3 && m1 == m3 && d1 > d3) return false;
	return true;
}

void Management::parseDate(const std::wstring& date, int& year, int& month, int& day) {
	size_t pos1 = date.find(L"-");
	size_t pos2 = date.find(L"-", pos1 + 1);

	year = std::stoi(date.substr(0, pos1));
	month = std::stoi(date.substr(pos1 + 1, pos2 - pos1 - 1));
	day = std::stoi(date.substr(pos2 + 1));
}

void Management::getCurrentMonthRange(std::wstring& firstDay, std::wstring& lastDay) {
	time_t now = time(nullptr);
	tm t_info;
	localtime_s(&t_info, &now);

	int year = t_info.tm_year + 1900;
	int month = t_info.tm_mon + 1;
	int day = t_info.tm_mday;

	firstDay = std::to_wstring(year) + L"-" + std::to_wstring(month) + L"-1";

	// 计算本月最后一天
	int lastDayNum = getDaysInCurrentMonth();
	lastDay = std::to_wstring(year) + L"-" + std::to_wstring(month) + L"-" + std::to_wstring(lastDayNum);
}

int Management::getDaysInCurrentMonth() {
	time_t now = time(nullptr);
	tm t_info;
	localtime_s(&t_info, &now);

	int year = t_info.tm_year + 1900;
	int month = t_info.tm_mon + 1;

	// 各月天数
	int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

	// 判断闰年
	if (month == 2) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			return 29;
		}
	}

	return daysInMonth[month - 1];
}
void Management::setting() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"设置");
	}
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(m_currentUser);
	}
	m_topBar->setTitle(L"设置");
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	m_gotologinButton->show();
	m_gotologinButton->eventLoop(m_msg);

	m_exitButton->show();
	m_exitButton->eventLoop(m_msg);

	if (m_exitButton->isClicked()) {
		currentState = EXIT;
		return;
	}


	if (m_gotologinButton->isClicked()) {
		currentState = LOGIN;
		if (m_currentUser != nullptr) {
			delete m_currentUser;
			m_currentUser = nullptr;
		}
		if (m_sideBar != nullptr) {
			delete m_sideBar;
			m_sideBar = nullptr;
		}
		if (m_topBar != nullptr) {
			delete m_topBar;
			m_topBar = nullptr;
		}
		m_loginRegister.reset();
		return;
	}

	// 检查侧边栏是否切换了页面
	if (m_sideBar->getCurrentPage() == 0) {
		currentState = MENU;
	}
	else if (m_sideBar->getCurrentPage() == 1) {
		currentState = TRANSACTION;
	}
	else if (m_sideBar->getCurrentPage() == 3) {
		currentState = ACCOUNT;
	}
	else if (m_sideBar->getCurrentPage() == 2) {
		currentState =TABLE;
	}
}
