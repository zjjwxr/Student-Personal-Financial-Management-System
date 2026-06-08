#include "MoneyCard.h"
#include <sstream>
#include <iomanip>
#include <locale>
#include <string>

static std::wstring FormatDouble(double val) {
	std::wostringstream woss;
	woss.imbue(std::locale(""));       // 系统本地化，自动千分位
	woss << std::fixed << std::setprecision(2) << val;
	return woss.str();
}

MoneyCard::MoneyCard(const std::wstring& title, double amount, int x, int y, int w, int h)
	: BasicWidget(x, y, w, h), m_title(new Text(title)), m_titleColor(RGB(102, 102, 102)), m_amountColor(RGB(51, 51, 51)) {
	std::wstring amountStr = FormatDouble(amount);
	m_amount = new Text(L"¥" + amountStr);
	m_title->setPosition(m_x + 20, m_y + 20);
	m_amount->setPosition(m_x + 20, m_y + 50);
	m_title->setFixedSize(14);
	m_amount->setFixedSize(28);
	m_title->setColor(m_titleColor);
	m_amount->setColor(m_amountColor);
}

void MoneyCard::setAmount(double amount) {
	std::wstring amountStr = FormatDouble(amount);
	m_amount->setText(L"¥" + amountStr);
}

void MoneyCard::setTitle(const std::wstring& title) {
	m_title->setText(title);
}

void MoneyCard::show() {
	setfillcolor(WHITE);
	setlinecolor(RGB(240, 240, 240));
	::solidroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 12, 12);
	::roundrect(m_x, m_y, m_x + m_w, m_y + m_h, 12, 12);
	m_title->setColor(m_titleColor);
	m_amount->setColor(m_amountColor);
	m_title->show();
	m_amount->show();
}
