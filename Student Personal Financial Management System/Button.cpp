#include "Button.h"

Button::Button(const std::wstring& text,int x, int y, int w, int h) :BasicWidget(x,y,w,h),m_text(text){}

void Button::show() {
	::setfillcolor(m_currentColor);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);//最后两个参数是圆角的宽和高，可以根据需要调整

	::settextcolor(BLACK);
	int tx = m_x + (m_w - ::textwidth(m_text.data())) / 2;
	int ty = m_y + (m_h - ::textheight(m_text.data())) / 2;
	::outtextxy(tx, ty, m_text.data());
}


void Button::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	if (isHover()) {
		m_currentColor = m_hoverColor;
		return;
	}
	if (isClicked()) {
		m_currentColor = m_normalColor;
		return;
	}
	return;
}

void Button::setNormalColor(COLORREF color) {
	m_normalColor = color;
}

void Button::setHoverColor(COLORREF color) {
	m_hoverColor = color;
}
