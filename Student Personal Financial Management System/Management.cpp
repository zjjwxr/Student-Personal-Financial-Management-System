#include "Management.h"

Management::Management() {
	

	::loadimage(&m_background, _T("./images/background.png"), Window::width(), Window::height());
	login_TextBoxes.push_back(new TextBox);
	login_TextBoxes.push_back(new TextBox);
	login_TextBoxes.push_back(new TextBox);
	login_TextBoxes.push_back(new TextBox);
	login_TextBoxes.push_back(new TextBox);
	login_TextBoxes.push_back(new TextBox);
	::settextstyle(60, 0, _T("微软雅黑"));
	
	//登录文本框
	login_TextBoxes[0]->setFixedSize(400, 50);
	login_TextBoxes[0]->setPosition((Window::width() - login_TextBoxes[0]->getWidth() )/2, Window::height() /2-100);
	login_TextBoxes[1]->setFixedSize(400, 50);
	login_TextBoxes[1]->setPosition((Window::width() - login_TextBoxes[1]->getWidth()) / 2, Window::height() /2-20);
	login_TextBoxes[2]->setFixedSize(400, 50);
	login_TextBoxes[2]->setPosition((Window::width() - login_TextBoxes[2]->getWidth() )/2, Window::height() /2-140);
	login_TextBoxes[3]->setFixedSize(400, 50);
	login_TextBoxes[3]->setPosition((Window::width() - login_TextBoxes[3]->getWidth()) / 2, Window::height() /2-60);
	login_TextBoxes[4]->setFixedSize(400, 50);
	login_TextBoxes[4]->setPosition((Window::width() - login_TextBoxes[4]->getWidth()) / 2, Window::height() / 2 +20);
	login_TextBoxes[5]->setFixedSize(400, 50);
	login_TextBoxes[5]->setPosition((Window::width() - login_TextBoxes[5]->getWidth()) / 2, Window::height() / 2 +100);
	//

	//登录按钮
	int lbtnW = 500, lbtnH = 60;
	int lbtnY = login_TextBoxes[1]->getY() + login_TextBoxes[1]->getHeight() + 40;
	int lcx = Window::width() / 2;
	Button* loginBtn = new Button(_T("立即登录"), lcx - lbtnW/2 , lbtnY, lbtnW, lbtnH);

	loginBtn->setTextColor(RGB(255, 255, 255));
	loginBtn->setDefaultColor(RGB(100, 150, 255));
	loginBtn->setHoverColor(RGB(0, 180, 0));


	login_Buttons.push_back(loginBtn);

	//退出按钮
	Button* exitBtn = new Button(_T("退出"), 50, Window::height()-150, 70, 30,0);
	
	
	exitBtn->setHoverColor(RGB(255, 0, 0));
	
	login_Buttons.push_back(exitBtn);
	//去注册按钮
	Button* gotoregiBtn = new Button(_T("去注册"), (Window::width() -40 ) / 2 , login_TextBoxes[1]->getY() + login_TextBoxes[1]->getHeight() + 120, 70, 28, 0);


	gotoregiBtn->setHoverColor(RGB(255, 0, 0));

	login_Buttons.push_back(gotoregiBtn);
	//注册按钮
	int rbtnW = 500, rbtnH = 60;
	int rbtnY = login_TextBoxes[5]->getY() + login_TextBoxes[5]->getHeight() + 40;
	int rcx = Window::width() / 2;
	Button* regiBtn = new Button(_T("立即注册"), rcx - rbtnW / 2, rbtnY, rbtnW, rbtnH);

	regiBtn->setTextColor(RGB(255, 255, 255));
	regiBtn->setDefaultColor(RGB(100, 150, 255));
	regiBtn->setHoverColor(RGB(0, 180, 0));
	login_Buttons.push_back(regiBtn);
	//去登录
	Button* gotologinBtn = new Button(_T("去注册"), (Window::width() - 40) / 2, login_TextBoxes[5]->getY() + login_TextBoxes[5]->getHeight() + 120, 70, 28, 0);


	gotologinBtn->setHoverColor(RGB(255, 0, 0));

	login_Buttons.push_back(gotologinBtn);
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
	
	settextstyle(60, 0, _T("黑体"));
	settextcolor(RGB(51, 51, 51));
	int titleW = textwidth(_T("用户登录"));
	outtextxy((Window::width() - titleW) / 2, 120, _T("用户登录"));

	settextstyle(20, 0, _T("宋体"));
	settextcolor(RGB(51, 51, 51));
	int W1 = textwidth(_T("宋体"));
	outtextxy((Window::width() - W1) / 2-100, login_TextBoxes[1]->getY() + login_TextBoxes[1]->getHeight() + 120, _T("没有账户？"));

	std::wstring text1 = _T("用户名");
	std::wstring text2 = _T("密码");
	::settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(RGB(80, 80, 80));
	::outtextxy((Window::width() - login_TextBoxes[0]->getWidth()) / 2 - 80, Window::height() / 2 - 100, text1.c_str());
	::outtextxy((Window::width() - login_TextBoxes[0]->getWidth()) / 2 - 80, Window::height() / 2 - 20, text2.c_str());


	//显示运行文本框和按钮
	for (int i = 0; i < 3; i++) {
		login_Buttons[i]->show();
		login_Buttons[i]->eventLoop(m_msg);
	}
	for (int i = 0; i < 2; i++) {
		login_TextBoxes[i]->eventLoop(m_msg);
		login_TextBoxes[i]->show();
	}
	//未输入文字提示
	settextstyle(18, 0, _T("微软雅黑"));
	std::wstring pa1 = L"请输入用户名";
	std::wstring  acc1= L"请输入密码";
	if (login_TextBoxes[0]->getText().empty()) {
		settextcolor(RGB(150, 150, 150));  
		int x = login_TextBoxes[0]->getX() + 10;
		int y = login_TextBoxes[0]->getY() + (login_TextBoxes[0]->getHeight() - textheight(pa1.c_str())) / 2;
		outtextxy(x, y, pa1.c_str());
	}


	if (login_TextBoxes[1]->getText().empty()) {
		settextcolor(RGB(150, 150, 150)); 
		int x = login_TextBoxes[1]->getX() + 10;
		int y = login_TextBoxes[1]->getY() + (login_TextBoxes[1]->getHeight() - textheight(pa1.c_str())) / 2;
		outtextxy(x, y,acc1.c_str());
	}

	//登录和注册逻辑


	// 错误提示
	::settextstyle(26, 0, _T("微软雅黑"));
	int msgY = login_TextBoxes[1]->getY() + login_TextBoxes[1]->getHeight() +10;
	if (m_loginError == 1) {
		settextcolor(RGB(255, 100, 100));
		::outtextxy(Window::width() / 2 - 50, msgY, _T("密码错误！"));
	}
	else if (m_loginError == 2) {
		settextcolor(RGB(255, 100, 100));
		::outtextxy(Window::width() / 2 - 200, msgY,
			_T("注册失败！用户名3-20位，密码至少6位"));
	}
	////登录
	if (login_Buttons[0]->isClicked()) {
		std::wstring uname = login_TextBoxes[0]->getText();
		std::wstring pwd = login_TextBoxes[1]->getText();
		User user(L"", uname, pwd);
		if (user.loginUser()) {
			m_loginError = 0;
			currentState = MENU;
		}
		else {
			m_loginError = 1;
		}
	}
	//退出
	if (login_Buttons[1]->isClicked()) {
		currentState = EXIT;
	}
	//进入注册
	if (login_Buttons[2]->isClicked()) {
		currentState = REGISTERUSER;
	}
}

void Management::registerUser() {
	
	
	//显示注册文本
	settextstyle(60, 0, _T("黑体"));
	settextcolor(RGB(51, 51, 51));
	int titleW = textwidth(_T("用户注册"));
	outtextxy((Window::width() - titleW) / 2, 80, _T("用户注册"));

	settextstyle(20, 0, _T("宋体"));
	settextcolor(RGB(51, 51, 51));
	int W1 = textwidth(_T("宋体"));
	outtextxy((Window::width() - W1) / 2 - 100, login_TextBoxes[5]->getY() + login_TextBoxes[5]->getHeight() + 120, _T("已有账号？"));
	std::wstring text3 = _T("姓名");
	std::wstring text4 = _T("用户名");
	std::wstring text5 = _T("密码");
	std::wstring text6 = _T("确认密码");
	::settextstyle(30, 0, _T("微软雅黑"));
	settextcolor(RGB(80, 80, 80));
	::outtextxy((Window::width() - login_TextBoxes[2]->getWidth()) / 2 - 100, Window::height() / 2 - 140, text3.c_str());
	::outtextxy((Window::width() - login_TextBoxes[3]->getWidth()) / 2 - 100, Window::height() / 2 - 60, text4.c_str());
	::outtextxy((Window::width() - login_TextBoxes[4]->getWidth()) / 2 - 100, Window::height() / 2 + 20, text5.c_str());
	::outtextxy((Window::width() - login_TextBoxes[5]->getWidth()) / 2 - 100, Window::height() / 2 + 100, text6.c_str());


	//显示和运行
	for (int i = 2; i < 6; i++) {
		login_TextBoxes[i]->eventLoop(m_msg);
		login_TextBoxes[i]->show();
	}
	for (int i = 3; i < 5; i++) {
		login_Buttons[i]->show();
		login_Buttons[i]->eventLoop(m_msg);
	}

	//未输入提示
	settextstyle(18, 0, _T("微软雅黑"));
	std::wstring r1 = L"请输入姓名";
	std::wstring r2 = L"请输入用户名";
	std::wstring r3 = L"请输入密码";
	std::wstring r4 = L"请再次输入密码";
	if (login_TextBoxes[2]->getText().empty()) {
		settextcolor(RGB(150, 150, 150));
		int x = login_TextBoxes[2]->getX() + 10;
		int y = login_TextBoxes[2]->getY() + (login_TextBoxes[2]->getHeight() - textheight(r1.c_str())) / 2;
		outtextxy(x, y, r1.c_str());
	}
	if (login_TextBoxes[3]->getText().empty()) {
		settextcolor(RGB(150, 150, 150));
		int x = login_TextBoxes[3]->getX() + 10;
		int y = login_TextBoxes[3]->getY() + (login_TextBoxes[3]->getHeight() - textheight(r2.c_str())) / 2;
		outtextxy(x, y, r2.c_str());
	}
	if (login_TextBoxes[4]->getText().empty()) {
		settextcolor(RGB(150, 150, 150));
		int x = login_TextBoxes[4]->getX() + 10;
		int y = login_TextBoxes[4]->getY() + (login_TextBoxes[4]->getHeight() - textheight(r3.c_str())) / 2;
		outtextxy(x, y, r3.c_str());
	}
	if (login_TextBoxes[5]->getText().empty()) {
		settextcolor(RGB(150, 150, 150));
		int x = login_TextBoxes[5]->getX() + 10;
		int y = login_TextBoxes[5]->getY() + (login_TextBoxes[5]->getHeight() - textheight(r4.c_str())) / 2;
		outtextxy(x, y, r4.c_str());
	}
	//显示错误
	::settextstyle(26, 0, _T("微软雅黑"));
	int msgY = login_TextBoxes[5]->getY() + login_TextBoxes[5]->getHeight() + 10;
	if (m_loginError == 2) {
		settextcolor(RGB(255, 100, 100));
		::outtextxy(Window::width() / 2 - 50, msgY, _T("密码输入不相同！"));
	}
	//注册逻辑
	if (login_Buttons[3]->isClicked()) {
		if (login_TextBoxes[4]->getText() ==login_TextBoxes[5]->getText()) {
			std::wstring name = login_TextBoxes[2]->getText();
			std::wstring uname = login_TextBoxes[3]->getText();
			std::wstring pwd = login_TextBoxes[4]->getText();
			m_loginError = 0;
			User user(name, uname, pwd);
			user.addUser();
			currentState = MENU;
		}
		else {
			m_loginError = 2;
		}
		
	}
	//进入登录
	if (login_Buttons[4]->isClicked()) {
		currentState = LOGIN;
	}





}



void Management::menu() {
	User temp(L"张三");
	if (m_sideBar == nullptr) {
		m_sideBar = new SideBar(&temp);
	}
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
