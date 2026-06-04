#include "TopBar.h"

TopBar::TopBar(const std::wstring& title, int x, int y, int w, int h):BasicWidget(x,y,w,h),m_title(new Text(title)),m_time(new Text()) {
	m_time->setFixedSize(20);
	int tx = m_x + m_w - ::textwidth(L"0000年00月00日") - 20;
	int ty = m_y + (m_h - ::textheight(L"0000年00月00日")) / 2;
	m_time->setPosition(tx, ty);
	updateTime();
	m_title->setColor(BLACK);
	m_title->setFixedSize(m_h - 20);
	m_title->setPosition(m_x + 40, m_y + (m_h - ::textheight(m_title->getText().c_str())) / 2);
}

void TopBar::show() {
	setfillcolor(RGB(248, 249, 250));
	solidrectangle(m_x, m_y, m_x + m_w, m_y + m_h);
	m_title->show();
	m_time->show();
	setlinecolor(RGB(224, 224, 224));
	setlinestyle(PS_SOLID, 3);
	line(m_x, m_y + m_h - 1, m_x + m_w, m_y + m_h - 1);
}

void TopBar::setTitle(const std::wstring& title) {
	m_title->setText(title);
}

void TopBar::updateTime() {
	time_t now = time(nullptr);
	tm t_info;
	localtime_s(&t_info, &now);
	wchar_t buffer[64]; 
	wcsftime(buffer, sizeof(buffer) / sizeof(wchar_t), L"%Y年%m月%d日",&t_info);
	std::wstring timeStr(buffer);
	for (size_t i = 0; i < timeStr.size() - 1; ) {
		if (timeStr[i] == L'年' && timeStr[i + 1] == L'0')
			timeStr.erase(i + 1, 1);
		else if (timeStr[i] == L'月' && timeStr[i + 1] == L'0')
			timeStr.erase(i + 1, 1);
		else
			i++;
	}
	m_time->setText(timeStr);
}

TopBar::~TopBar() {
	delete m_title;
	delete m_time;
}
