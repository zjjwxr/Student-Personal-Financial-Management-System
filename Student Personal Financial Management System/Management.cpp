#include "Management.h"
#include "MoneyCard.h"
#include "Chart.h"
#include "Tab.h"
#include "Select.h"
#include "Table.h"
#include "AccountCard.h"
#include <ctime>
#include <iomanip>
#include <sstream>

Management::Management() {
	::loadimage(&m_background, _T("./images/background.png"), Window::width(), Window::height());

	// 初始化概况页面组件
	m_incomeCard = new MoneyCard(L"本月收入", L"¥0.00", 200, 80, 200, 100);
	m_incomeCard->setTextColor(RGB(124, 179, 66));

	m_expenseCard = new MoneyCard(L"本月支出", L"¥0.00", 420, 80, 200, 100);
	m_expenseCard->setTextColor(RGB(255, 107, 107));

	m_balanceCard = new MoneyCard(L"结余", L"¥0.00", 640, 80, 200, 100);
	m_balanceCard->setTextColor(RGB(46, 125, 255));

	// 初始化图表组件（暂时只创建，不实现）
	m_pieChart = new Chart(ChartType::PIE, L"支出分类", 200, 200, 350, 250);
	m_lineChart = new Chart(ChartType::LINE, L"每日支出趋势", 580, 200, 350, 250);

	// 初始化记账页面组件
	m_transactionTab = new Tab(200, 80, 400, 40);
	m_transactionTab->addTab(L"支出");
	m_transactionTab->addTab(L"收入");

	m_categorySelect = new Select(200, 140, 400, 35);
	m_categorySelect->addOption(L"餐饮");
	m_categorySelect->addOption(L"交通");
	m_categorySelect->addOption(L"购物");
	m_categorySelect->addOption(L"学习");
	m_categorySelect->addOption(L"娱乐");
	m_categorySelect->addOption(L"其他");

	m_accountSelect = new Select(200, 190, 400, 35);
	m_accountSelect->addOption(L"微信");
	m_accountSelect->addOption(L"支付宝");
	m_accountSelect->addOption(L"银行卡");
	m_accountSelect->addOption(L"现金");

	m_amountTextBox = new TextBox(200, 240, 400, 35);
	m_dateTextBox = new TextBox(200, 290, 400, 35);
	m_descriptionTextBox = new TextBox(200, 340, 400, 35);

	m_saveTransactionButton = new Button(L"保存", 300, 400, 200, 40);
	m_saveTransactionButton->setTextColor(WHITE);
	m_saveTransactionButton->setDefaultColor(RGB(46, 125, 255));
	m_saveTransactionButton->setHoverColor(RGB(30, 100, 220));

	// 初始化表单页面组件
	m_startDateTextBox = new TextBox(200, 80, 130, 32);
	m_endDateTextBox = new TextBox(350, 80, 130, 32);

	m_filterCategorySelect = new Select(500, 80, 100, 32);
	m_filterCategorySelect->addOption(L"全部");
	m_filterCategorySelect->addOption(L"餐饮");
	m_filterCategorySelect->addOption(L"交通");
	m_filterCategorySelect->addOption(L"购物");
	m_filterCategorySelect->addOption(L"学习");
	m_filterCategorySelect->addOption(L"娱乐");
	m_filterCategorySelect->addOption(L"其他");

	m_filterAccountSelect = new Select(620, 80, 100, 32);
	m_filterAccountSelect->addOption(L"全部");
	m_filterAccountSelect->addOption(L"微信");
	m_filterAccountSelect->addOption(L"支付宝");
	m_filterAccountSelect->addOption(L"银行卡");
	m_filterAccountSelect->addOption(L"现金");

	m_filterButton = new Button(L"筛选", 740, 80, 80, 32);
	m_filterButton->setTextColor(WHITE);
	m_filterButton->setDefaultColor(RGB(46, 125, 255));
	m_filterButton->setHoverColor(RGB(30, 100, 220));

	m_transactionTable = new Table(200, 130, 620, 400);
	m_transactionTable->addHeader(L"日期", 150);
	m_transactionTable->addHeader(L"类别", 100);
	m_transactionTable->addHeader(L"支付渠道", 100);
	m_transactionTable->addHeader(L"金额", 120);
	m_transactionTable->addHeader(L"备注", 150);

	// 初始化账户管理页面组件
	m_totalBalanceCard = new MoneyCard(L"总资产", L"¥0.00", 200, 80, 300, 100);
	m_totalBalanceCard->setTextColor(RGB(46, 125, 255));

	m_addAccountButton = new Button(L"+ 添加账户", 750, 90, 150, 40);
	m_addAccountButton->setTextColor(WHITE);
	m_addAccountButton->setDefaultColor(RGB(46, 125, 255));
	m_addAccountButton->setHoverColor(RGB(30, 100, 220));

	m_addAccountNameTextBox = new TextBox(300, 200, 200, 35);
	m_addAccountBalanceTextBox = new TextBox(300, 250, 200, 35);

	m_confirmAddAccountButton = new Button(L"确认", 300, 300, 90, 35);
	m_confirmAddAccountButton->setTextColor(WHITE);
	m_confirmAddAccountButton->setDefaultColor(RGB(46, 125, 255));
	m_confirmAddAccountButton->setHoverColor(RGB(30, 100, 220));

	m_cancelAddAccountButton = new Button(L"取消", 410, 300, 90, 35);
	m_cancelAddAccountButton->setTextColor(WHITE);
	m_cancelAddAccountButton->setDefaultColor(RGB(150, 150, 150));
	m_cancelAddAccountButton->setHoverColor(RGB(120, 120, 120));

	m_showAddAccountDialog = false;
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
}

void Management::registerUser() {
	
	
	m_loginRegister.drawRegister();
	m_loginRegister.handleRegister(reinterpret_cast<int&>(currentState));




}



void Management::menu() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"概况");
	}
	User temp(L"张三");
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(&temp);
	}

	// 获取当前时间
	time_t now = time(nullptr);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	int currentYear = timeinfo.tm_year + 1900;
	int currentMonth = timeinfo.tm_mon + 1;

	// 计算本月收入和支出
	double totalIncome = 0.0;
	double totalExpense = 0.0;

	// 如果用户有交易数据，计算本月统计
	if (temp.getTransactionManager()) {
		time_t monthStart, monthEnd;
		struct tm startInfo = timeinfo;
		startInfo.tm_mday = 1;
		startInfo.tm_hour = 0;
		startInfo.tm_min = 0;
		startInfo.tm_sec = 0;
		monthStart = mktime(&startInfo);

		struct tm endInfo = timeinfo;
		endInfo.tm_mday = 1;
		endInfo.tm_mon += 1;
		endInfo.tm_hour = 0;
		endInfo.tm_min = 0;
		endInfo.tm_sec = 0;
		monthEnd = mktime(&endInfo);

		totalIncome = temp.getTransactionManager()->getTotalIncomeByDateRange(monthStart, monthEnd);
		totalExpense = temp.getTransactionManager()->getTotalExpenseByDateRange(monthStart, monthEnd);
	}

	// 更新统计卡片
	std::wstringstream ss;
	ss << L"¥" << std::fixed << std::setprecision(2) << totalIncome;
	m_incomeCard->setAmount(ss.str());
	ss.str(L"");

	ss << L"¥" << std::fixed << std::setprecision(2) << totalExpense;
	m_expenseCard->setAmount(ss.str());
	ss.str(L"");

	double balance = totalIncome - totalExpense;
	ss << L"¥" << std::fixed << std::setprecision(2) << balance;
	m_balanceCard->setAmount(ss.str());

	// 显示组件
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	// 显示统计卡片
	m_incomeCard->show();
	m_expenseCard->show();
	m_balanceCard->show();

	// 显示图表（暂时不实现具体绘制）
	// m_pieChart->show();
	// m_lineChart->show();
}

void Management::account() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"账户管理");
	}
	User temp(L"张三");
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(&temp);
	}

	// 显示顶部栏和侧边栏
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	// 计算总资产
	double totalBalance = 0.0;
	std::vector<Account*> accounts = temp.getAccounts();
	for (auto* account : accounts) {
		totalBalance += account->getBalance();
	}

	// 更新总资产显示
	std::wstringstream ss;
	ss << L"¥" << std::fixed << std::setprecision(2) << totalBalance;
	m_totalBalanceCard->setAmount(ss.str());

	// 显示总资产卡片
	m_totalBalanceCard->show();

	// 显示添加账户按钮
	m_addAccountButton->show();
	m_addAccountButton->eventLoop(m_msg);

	// 处理添加账户按钮点击
	if (m_addAccountButton->isClicked()) {
		m_showAddAccountDialog = true;
	}

	// 显示添加账户对话框
	if (m_showAddAccountDialog) {
		// 绘制对话框背景
		setfillcolor(WHITE);
		solidrectangle(250, 180, 550, 360);

		// 绘制对话框边框
		setlinestyle(PS_SOLID, 2);
		setlinecolor(RGB(200, 200, 200));
		rectangle(250, 180, 550, 360);

		// 显示对话框标题
		settextstyle(20, 0, L"微软雅黑");
		settextcolor(RGB(51, 51, 51));
		outtextxy(350, 190, L"添加账户");

		// 显示输入框标签
		settextstyle(16, 0, L"微软雅黑");
		settextcolor(RGB(102, 102, 102));
		outtextxy(260, 210, L"账户名称：");
		outtextxy(260, 260, L"初始余额：");

		// 显示输入框和按钮
		m_addAccountNameTextBox->show();
		m_addAccountNameTextBox->eventLoop(m_msg);

		m_addAccountBalanceTextBox->show();
		m_addAccountBalanceTextBox->eventLoop(m_msg);

		m_confirmAddAccountButton->show();
		m_confirmAddAccountButton->eventLoop(m_msg);

		m_cancelAddAccountButton->show();
		m_cancelAddAccountButton->eventLoop(m_msg);

		// 处理确认添加账户按钮点击
		if (m_confirmAddAccountButton->isClicked()) {
			std::wstring accountName = m_addAccountNameTextBox->getText();
			std::wstring balanceStr = m_addAccountBalanceTextBox->getText();

			// 验证输入
			if (accountName.empty()) {
				settextstyle(16, 0, L"微软雅黑");
				settextcolor(RGB(255, 100, 100));
				outtextxy(260, 340, L"请输入账户名称！");
				return;
			}

			// 解析余额
			double balance = 0.0;
			if (!balanceStr.empty()) {
				try {
					balance = std::stod(balanceStr);
				} catch (...) {
					settextstyle(16, 0, L"微软雅黑");
					settextcolor(RGB(255, 100, 100));
					outtextxy(260, 340, L"余额格式错误！");
					return;
				}
			}

			// 创建新账户
			Account* newAccount = new Account(&temp, accountName, balance);
			if (newAccount->addAccount()) {
				// 重新加载账户数据
				temp.loadAccounts();

				// 清空输入框
				m_addAccountNameTextBox->setText(L"");
				m_addAccountBalanceTextBox->setText(L"");

				// 关闭对话框
				m_showAddAccountDialog = false;

				// 显示成功提示
				settextstyle(16, 0, L"微软雅黑");
				settextcolor(RGB(76, 175, 80));
				outtextxy(260, 340, L"账户添加成功！");
			}
		}

		// 处理取消添加账户按钮点击
		if (m_cancelAddAccountButton->isClicked()) {
			m_showAddAccountDialog = false;
			m_addAccountNameTextBox->setText(L"");
			m_addAccountBalanceTextBox->setText(L"");
		}
	}

	// 显示账户列表
	int cardY = 200;
	for (auto* account : accounts) {
		AccountCard* card = new AccountCard(
			account->getAccountName(),
			account->getBalance(),
			L"💰",
			RGB(238, 180, 34),
			200, cardY, 620, 80
		);

		card->show();
		card->eventLoop(m_msg);

		// 处理编辑按钮点击
		if (card->isEditClicked()) {
			// 编辑账户功能（暂时只显示提示）
			settextstyle(16, 0, L"微软雅黑");
			settextcolor(RGB(102, 102, 102));
			outtextxy(200, 580, L"编辑账户功能待实现");
		}

		// 处理删除按钮点击
		if (card->isDeleteClicked()) {
			// 删除账户功能（暂时只显示提示）
			settextstyle(16, 0, L"微软雅黑");
			settextcolor(RGB(102, 102, 102));
			outtextxy(200, 580, L"删除账户功能待实现");
		}

		cardY += 90;
	}
}

void Management::transaction() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"记账");
	}
	User temp(L"张三");
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(&temp);
	}

	// 显示顶部栏和侧边栏
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	// 显示记账页面组件
	m_transactionTab->show();
	m_transactionTab->eventLoop(m_msg);

	m_categorySelect->show();
	m_categorySelect->eventLoop(m_msg);

	m_accountSelect->show();
	m_accountSelect->eventLoop(m_msg);

	m_amountTextBox->show();
	m_amountTextBox->eventLoop(m_msg);

	m_dateTextBox->show();
	m_dateTextBox->eventLoop(m_msg);

	m_descriptionTextBox->show();
	m_descriptionTextBox->eventLoop(m_msg);

	m_saveTransactionButton->show();
	m_saveTransactionButton->eventLoop(m_msg);

	// 处理保存交易按钮点击
	if (m_saveTransactionButton->isClicked()) {
		// 获取输入数据
		std::wstring amountStr = m_amountTextBox->getText();
		std::wstring dateStr = m_dateTextBox->getText();
		std::wstring description = m_descriptionTextBox->getText();

		// 验证金额输入
		if (amountStr.empty()) {
			// 显示错误提示
			settextstyle(20, 0, L"微软雅黑");
			settextcolor(RGB(255, 100, 100));
			outtextxy(200, 500, L"请输入金额！");
			return;
		}

		// 转换金额
		double amount = 0.0;
		try {
			amount = std::stod(amountStr);
		} catch (...) {
			settextstyle(20, 0, L"微软雅黑");
			settextcolor(RGB(255, 100, 100));
			outtextxy(200, 500, L"金额格式错误！");
			return;
		}

		// 获取交易类型
		TransactionType type = (m_transactionTab->getActiveIndex() == 0) ? TransactionType::EXPENSE : TransactionType::INCOME;

		// 获取类别和账户
		std::wstring category = m_categorySelect->getSelectedText();
		std::wstring accountName = m_accountSelect->getSelectedText();

		// 解析日期（如果为空则使用当前日期）
		time_t date = time(nullptr);
		if (!dateStr.empty()) {
			// 简单的日期解析，格式：YYYY-MM-DD
			struct tm timeinfo = {};
			int year, month, day;
			if (swscanf_s(dateStr.c_str(), L"%d-%d-%d", &year, &month, &day) == 3) {
				timeinfo.tm_year = year - 1900;
				timeinfo.tm_mon = month - 1;
				timeinfo.tm_mday = day;
				date = mktime(&timeinfo);
			}
		}

		// 添加交易记录
		if (temp.getTransactionManager()) {
			bool success = temp.getTransactionManager()->addTransaction(
				type, category, L"", amount, description, accountName);

			if (success) {
				// 更新账户余额
				std::vector<Account*> accounts = temp.getAccounts();
				for (auto* account : accounts) {
					if (account->getAccountName() == accountName) {
						if (type == TransactionType::INCOME) {
							account->deposit(amount);
						} else {
							account->withdraw(amount);
						}
						break;
					}
				}

				// 保存交易数据
				temp.saveTransactions();
				temp.saveAccounts();

				// 清空输入框
				m_amountTextBox->setText(L"");
				m_dateTextBox->setText(L"");
				m_descriptionTextBox->setText(L"");

				// 显示成功提示
				settextstyle(20, 0, L"微软雅黑");
				settextcolor(RGB(76, 175, 80));
				outtextxy(200, 500, L"交易记录保存成功！");
			}
		}
	}

	// 显示标签提示
	settextstyle(16, 0, L"微软雅黑");
	settextcolor(RGB(102, 102, 102));
	outtextxy(200, 120, L"类别：");
	outtextxy(200, 170, L"支付渠道：");
	outtextxy(200, 220, L"金额：");
	outtextxy(200, 270, L"日期：");
	outtextxy(200, 320, L"备注：");
}

void Management::table() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"表单");
	}
	User temp(L"张三");
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(&temp);
	}

	// 显示顶部栏和侧边栏
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();

	// 显示筛选控件
	settextstyle(16, 0, L"微软雅黑");
	settextcolor(RGB(102, 102, 102));
	outtextxy(200, 60, L"开始日期：");
	outtextxy(350, 60, L"结束日期：");
	outtextxy(500, 60, L"分类：");
	outtextxy(620, 60, L"支付渠道：");

	m_startDateTextBox->show();
	m_startDateTextBox->eventLoop(m_msg);

	m_endDateTextBox->show();
	m_endDateTextBox->eventLoop(m_msg);

	m_filterCategorySelect->show();
	m_filterCategorySelect->eventLoop(m_msg);

	m_filterAccountSelect->show();
	m_filterAccountSelect->eventLoop(m_msg);

	m_filterButton->show();
	m_filterButton->eventLoop(m_msg);

	// 处理筛选按钮点击
	if (m_filterButton->isClicked()) {
		// 清空表格数据
		m_transactionTable->clearRows();

		// 获取筛选条件
		std::wstring startDateStr = m_startDateTextBox->getText();
		std::wstring endDateStr = m_endDateTextBox->getText();
		std::wstring category = m_filterCategorySelect->getSelectedText();
		std::wstring accountName = m_filterAccountSelect->getSelectedText();

		// 解析日期范围
		time_t startDate = 0;
		time_t endDate = time(nullptr);

		if (!startDateStr.empty()) {
			struct tm startInfo = {};
			int year, month, day;
			if (swscanf_s(startDateStr.c_str(), L"%d-%d-%d", &year, &month, &day) == 3) {
				startInfo.tm_year = year - 1900;
				startInfo.tm_mon = month - 1;
				startInfo.tm_mday = day;
				startDate = mktime(&startInfo);
			}
		}

		if (!endDateStr.empty()) {
			struct tm endInfo = {};
			int year, month, day;
			if (swscanf_s(endDateStr.c_str(), L"%d-%d-%d", &year, &month, &day) == 3) {
				endInfo.tm_year = year - 1900;
				endInfo.tm_mon = month - 1;
				endInfo.tm_mday = day;
				endDate = mktime(&endInfo);
			}
		}

		// 获取交易数据
		if (temp.getTransactionManager()) {
			std::vector<Transaction> transactions = temp.getTransactionManager()->getTransactionsByDateRange(startDate, endDate);

			// 筛选交易记录
			for (const auto& trans : transactions) {
				// 按分类筛选
				if (category != L"全部" && trans.getCategory() != category) {
					continue;
				}

				// 按账户筛选
				if (accountName != L"全部" && trans.getAccountName() != accountName) {
					continue;
				}

				// 创建表格行
				TableRow row;
				std::wstringstream ss;

				// 日期
				std::wstring dateStr = trans.getDateString();
				TableCell dateCell;
				dateCell.text = dateStr.substr(0, 10); // 只显示日期部分
				dateCell.textColor = BLACK;
				dateCell.isIncome = false;
				row.cells.push_back(dateCell);

				// 类别
				TableCell categoryCell;
				categoryCell.text = trans.getCategory();
				categoryCell.textColor = BLACK;
				categoryCell.isIncome = false;
				row.cells.push_back(categoryCell);

				// 支付渠道
				TableCell accountCell;
				accountCell.text = trans.getAccountName();
				accountCell.textColor = BLACK;
				accountCell.isIncome = false;
				row.cells.push_back(accountCell);

				// 金额
				TableCell amountCell;
				ss.str(L"");
				if (trans.getType() == TransactionType::INCOME) {
					ss << L"+";
					amountCell.isIncome = true;
				} else {
					ss << L"-";
					amountCell.isIncome = false;
				}
				ss << std::fixed << std::setprecision(2) << trans.getAmount();
				amountCell.text = ss.str();
				amountCell.textColor = BLACK;
				row.cells.push_back(amountCell);

				// 备注
				TableCell descCell;
				descCell.text = trans.getDescription();
				descCell.textColor = BLACK;
				descCell.isIncome = false;
				row.cells.push_back(descCell);

				m_transactionTable->addRow(row);
			}
		}
	}

	// 显示交易记录表格
	m_transactionTable->show();
	m_transactionTable->eventLoop(m_msg);
}

void Management::setting() {
	currentState = EXIT;
}
