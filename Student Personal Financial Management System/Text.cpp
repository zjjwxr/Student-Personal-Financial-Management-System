#include "Text.h"

Text::Text(const std::wstring& text, int x, int y, int w, int h) : BasicWidget(x, y, w, h), m_text(text) {}

void Text::show() {
	::outtextxy(m_x, m_y, m_text.c_str());
}

void Text::setColor(COLORREF color) {
	m_color = color;
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
