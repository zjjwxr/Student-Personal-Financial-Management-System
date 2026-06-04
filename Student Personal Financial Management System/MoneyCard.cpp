#include "MoneyCard.h"

MoneyCard::MoneyCard(const std::wstring& title, const std::wstring& amount, int x, int y, int w, int h)
	:BasicWidget(x,y,w,h),m_title(new Text(title)),m_amount(new Text(amount)){}

void MoneyCard::show() {
}
