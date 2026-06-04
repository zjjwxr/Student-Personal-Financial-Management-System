#include "Management.h"

Management::Management() {
	::loadimage(&m_background, _T("./images/background.png"), Window::width(), Window::height());


	//login_TextBoxes.push_back(new TextBox);
	//login_TextBoxes.push_back(new TextBox);
	//::settextstyle(60, 0, _T("微软雅黑"));
	//for(int i=0;i<login_TextBoxes.size();i++){
	//	login_TextBoxes[i]->setFixedSize(400, 60);
	//	int login_tbx = (Window::width() - login_TextBoxes[i]->getWidth())/ 2;
	//	int login_tby = (Window::height() - 4 * 60) / 2 + (2 * i + 1) * 60;
	//	login_TextBoxes[i]->setPosition(login_tbx,login_tby);
	//}
	////加载数据
	//m_user.loadFromFile();

	////登录和注册按钮
	//int btnW = 180, btnH = 60;
	//int btnY = login_TextBoxes[1]->getY() + login_TextBoxes[1]->getHeight() + 40;
	//int cx = Window::width() / 2;

	//Button* loginBtn = new Button(_T("登录"), cx - btnW - 20, btnY, btnW, btnH);
	//Button* regBtn = new Button(_T("注册"), cx + 20, btnY, btnW, btnH);

	//loginBtn->setDefaultColor(RGB(77, 77, 77));
	//loginBtn->setHoverColor(RGB(0, 180, 0));
	//regBtn->setDefaultColor(RGB(77, 77, 77));
	//regBtn->setHoverColor(RGB(0, 120, 255));

	//login_Buttons.push_back(loginBtn);
	//login_Buttons.push_back(regBtn);

	//ui要改一下，不要再用我之前写的了
}

void Management::run() {
	currentState = MENU;
	Window::beginDraw();
	while (true) {
		Window::clear();
		Window::drawBackground(m_background);
		if (Window::hasMessage()) {
			m_msg = Window::getMessage();
		}
		else m_msg.message = 0;//没有消息时，重置消息，防止上次的消息影响当前界面
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
	std::wstring text1 = _T("用户名");
	std::wstring text2 = _T("密码");
	::settextstyle(60, 0, _T("微软雅黑"));
	int login_tx = (Window::width() - login_TextBoxes[0]->getWidth()) / 2;
	int login_ty = (Window::height() - 4 * 60) / 2;
	::outtextxy(login_tx, login_ty, text1.c_str());
	::outtextxy(login_tx, login_ty + 2 * 60, text2.c_str());
	//for (auto& btn : login_Buttons) {
	//	btn->show();
	//	btn->eventLoop(m_msg);
	//}
	for (auto& btx : login_TextBoxes) {
		btx->eventLoop(m_msg);
		btx->show();
	}



	

	for (auto& btn : login_Buttons) {
		btn->eventLoop(m_msg);
		btn->show();
	}


	




	//登录和注册逻辑
	

	// 错误提示
	::settextstyle(26, 0, _T("微软雅黑"));
	int msgY = login_TextBoxes[1]->getY() + login_TextBoxes[1]->getHeight() + 110;
	if (m_loginError == 1) {
		settextcolor(RGB(255, 100, 100));
		::outtextxy(Window::width() / 2 - 80, msgY, _T("密码错误！"));
	}
	else if (m_loginError == 2) {
		settextcolor(RGB(255, 100, 100));
		::outtextxy(Window::width() / 2 - 200, msgY,
		_T("注册失败！用户名3-20位，密码至少6位"));
	}
	////登录
	//if (login_Buttons[0]->isClicked()) {
	//	std::wstring uname = login_TextBoxes[0]->getText();
	//	std::wstring pwd = login_TextBoxes[1]->getText();
	//	if (m_user.login(uname, pwd)) {
	//		m_loginError = 0;
	//		currentState = MENU;
	//	}
	//	else {
	//		m_loginError = 1;
	//	}
	//}
	////注册
	//if (login_Buttons[1]->isClicked()) {
	//	std::wstring uname = login_TextBoxes[0]->getText();
	//	std::wstring pwd = login_TextBoxes[1]->getText();
	//	if (m_user.registerUser(uname, pwd)) {
	//		m_user.saveToFile();
	//		m_user.login(uname, pwd);
	//		
	//		m_loginError = 0;
	//		currentState = MENU;
	//	}
	//	else {
	//		m_loginError = 2;
	//	}
	//}

	//重新自己好好写一下吧哥。一次肯定只有一个User啊，你用map是何意呢？你甚至把这样逻辑都写出来了，每次都创建一个
	//tempUser对象用TextBox里的输入来初始化就行了。
	//再用一个全局变量或者成员记录一下登录的currentUser就ok了
}

void Management::registerUser() {
	currentState = EXIT;
}



void Management::menu() {
	if (m_topBar == nullptr) {
		m_topBar = new TopBar(L"概况");
	}
	User temp(L"张三");
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(&temp);
	}
	m_topBar->show();
	m_sideBar->eventLoop(m_msg);
	m_sideBar->show();
}

void Management::account() {
	currentState = EXIT;
}

void Management::transaction() {
	currentState = EXIT;
}

void Management::table() {
	currentState = EXIT;
}

void Management::setting() {
	currentState = EXIT;
}
