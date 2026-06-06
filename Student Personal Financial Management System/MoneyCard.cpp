#include "MoneyCard.h"

MoneyCard::MoneyCard(const std::wstring& title, const std::wstring& amount, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_title(new Text(title)),m_amount(new Text(amount)){}
MoneyCard::~MoneyCard() {
	delete m_title;
	delete m_amount;
}
void MoneyCard::show() {
	if (m_title != nullptr) {
		m_title->show();
	}
	if (m_amount != nullptr) {
		m_amount->show();
	}
}

void MoneyCard::setTitleColor(COLORREF color) {
	if (m_title != nullptr) {
		m_title->setColor(color);
	}
}

void MoneyCard::setAmountColor(COLORREF color) {
	if (m_amount != nullptr) {
		m_amount->setColor(color);
	}
}

void MoneyCard::setAmount(const std::wstring& amount) {
	if (m_amount != nullptr) {
		m_amount->setText(amount);
	}
}

void MoneyCard::setTitle(const std::wstring& title) {
	if (m_title != nullptr) {
		m_title->setText(title);
	}
}
void MoneyCard::setTextColor(COLORREF color) {
	if (m_title != nullptr) {
		m_title->setColor(color);
	}
	if (m_amount != nullptr) {
		m_amount->setColor(color);
	}
}
