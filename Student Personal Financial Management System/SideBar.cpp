#include "SideBar.h"

SideBar::SideBar(User* user, int x, int y, int w, int h):m_user(user),BasicWidget(x,y,w,h) {
	m_buttons.push_back(new Button(L"📈概况", 0, 100, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"💰记账", 0, 155, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"📋表单", 0, 210, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"💳账户", 0, 265, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"⚙️设置", 0, 320, 180, 55, 0, 0));
	for (auto button : m_buttons) {
		button->setHoverColor(RGB(46, 125, 255));
		button->setTextSize(25);
		button->setTextFont(L"楷体");
	}
	m_realnameText = new Text(m_user->getRealname()); 
	m_realnameText->setFixedSize(40);
	int tx = (m_w - ::textwidth(m_realnameText->getText().c_str())) / 2;
	int ty = (100 - ::textheight(m_realnameText->getText().c_str())) / 2;
	m_realnameText->setPosition(tx, ty);
}

void SideBar::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	for (auto button : m_buttons) {
		button->eventLoop(m_msg);
	}
}

void SideBar::show() {
	setfillcolor(WHITE);
	solidrectangle(m_x, m_y, m_x + m_w, m_y + m_h);
	m_realnameText->show();
	for (auto button : m_buttons) {
		button->show();
	}
	setlinecolor(RGB(224, 224, 224));
	setlinestyle(PS_SOLID, 3);
	line(m_x + m_w - 1, m_y, m_x + m_w - 1, m_y + m_h);
}

SideBar::~SideBar() {
	for (auto button : m_buttons) {
		delete button;
	}
	delete m_realnameText;
	delete m_user;
}
