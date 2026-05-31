#include "SideBar.h"

SideBar::SideBar(User* user, int x, int y, int w, int h):m_user(user),BasicWidget(x,y,w,h) {
	m_buttons.push_back(new Button(L"概况", 0, 100, 180, 45, 0, 0));
	m_buttons.push_back(new Button(L"记账", 0, 145, 180, 45, 0, 0));
	m_buttons.push_back(new Button(L"表单", 0, 190, 180, 45, 0, 0));
	m_buttons.push_back(new Button(L"账户", 0, 235, 180, 45, 0, 0));
	m_buttons.push_back(new Button(L"设置", 0, 280, 180, 45, 0, 0));
	for (auto button : m_buttons) {
		button->setHoverColor(RGB(46, 125, 255));
	}
	m_usernameText = new Text(m_user->getNickname());
	m_usernameText->setFixedSize(40);
	int tx = (m_w - ::textwidth(m_usernameText->getText().c_str())) / 2;
	int ty = (100 - ::textheight(m_usernameText->getText().c_str())) / 2;
	m_usernameText->setPosition(tx, ty);
}

void SideBar::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	for (auto button : m_buttons) {
		button->eventLoop(m_msg);
	}
}

void SideBar::show() {
	setfillcolor(WHITE);
	//setcolor(BLACK);
	solidrectangle(m_x, m_y, m_w, m_y + m_h);
	m_usernameText->show();
	for (auto button : m_buttons) {
		button->show();
	}
}

SideBar::~SideBar() {
	for (auto button : m_buttons) {
		delete button;
	}
	delete m_usernameText;
	delete m_user;
}
