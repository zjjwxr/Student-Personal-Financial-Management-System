#include "SideBar.h"

SideBar::SideBar(User* user, int x, int y, int w, int h):m_user(user),BasicWidget(x,y,w,h), m_currentPage(0) {
	m_buttons.push_back(new Button(L"📈概况", 0, 100, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"💰记账", 0, 155, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"📋表单", 0, 210, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"💳账户", 0, 265, 180, 55, 0, 0));
	m_buttons.push_back(new Button(L"⚙️设置", 0, 320, 180, 55, 0, 0));
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->setHoverColor(RGB(46, 125, 255));
		m_buttons[i]->setTextSize(25);
		m_buttons[i]->setTextFont(L"楷体");
		if (i == 0) {
			m_buttons[i]->setDefaultColor(RGB(46, 125, 255));
			m_buttons[i]->setTextColor(WHITE);
		}
	}
	m_realnameText = new Text(m_user->getRealname()); 
	m_realnameText->setFixedSize(40);
	int tx = (m_w - ::textwidth(m_realnameText->getText().c_str())) / 2;
	int ty = (100 - ::textheight(m_realnameText->getText().c_str())) / 2;
	m_realnameText->setPosition(tx, ty);
}

void SideBar::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->eventLoop(m_msg);
		if (m_buttons[i]->isClicked()) {
			m_currentPage = i;
			// 更新按钮状态
			for (int j = 0; j < m_buttons.size(); j++) {
				if (j == i) {
					m_buttons[j]->setDefaultColor(RGB(46, 125, 255));
					m_buttons[j]->setTextColor(WHITE);
				} else {
					m_buttons[j]->setDefaultColor(WHITE);
					m_buttons[j]->setTextColor(BLACK);
				}
			}
		}
	}
}

void SideBar::setCurrentPage(int page) {
	if (page >= 0 && page < m_buttons.size()) {
		m_currentPage = page;
		for (int j = 0; j < m_buttons.size(); j++) {
			if (j == page) {
				m_buttons[j]->setDefaultColor(RGB(46, 125, 255));
				m_buttons[j]->setTextColor(WHITE);
			} else {
				m_buttons[j]->setDefaultColor(WHITE);
				m_buttons[j]->setTextColor(BLACK);
			}
		}
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
	//delete m_user;
}
