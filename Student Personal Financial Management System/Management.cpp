#include "Management.h"

Management::Management() {
	

	::loadimage(&m_background, _T("./images/background.png"), Window::width(), Window::height());
	

	 
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
