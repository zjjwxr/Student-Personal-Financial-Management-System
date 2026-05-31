#include "Text.h"

Text::Text(const std::wstring& text, int x, int y, int w, int h) : BasicWidget(x, y, w, h), m_text(text) {}

void Text::show() {
	::settextstyle(m_h, m_w, m_fontName);
	::settextcolor(m_color);
	::outtextxy(m_x, m_y, m_text.c_str());
}

void Text::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	if (isHover()) {
		m_color = m_hoverColor;
		return;
	}
	if (isClicked()) {
		m_color = m_defaultColor;
		return;
	}
	return;
}

void Text::setColor(COLORREF color) {
	m_color = color;
	m_defaultColor = color;
	::settextcolor(m_color);
}

void Text::setFont(const std::wstring& fontName) {
	m_fontName = fontName.c_str();
	::settextstyle(m_h, m_w, m_fontName);
}

void Text::setFixedSize(int height, int width) {
	m_h = height;
	m_w = width;
	::settextstyle(m_h, m_w, m_fontName);
}
