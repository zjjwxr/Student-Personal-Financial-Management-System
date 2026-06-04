#include "Text.h"

Text::Text(const std::wstring& text, int x, int y, int w, int h) : BasicWidget(x, y, w, h), m_text(text) {
	ZeroMemory(&m_lf, sizeof(LOGFONT));
	// 默认：微软雅黑、开启抗锯齿、默认字号20
	wcscpy_s(m_lf.lfFaceName, _countof(m_lf.lfFaceName), _T("微软雅黑"));
	m_lf.lfQuality = ANTIALIASED_QUALITY; // 官方抗锯齿
	m_lf.lfHeight = m_h;
	m_lf.lfWidth = m_w;   // 0=自动等宽，字体不变形
	m_lf.lfWeight = FW_NORMAL;

}

void Text::show() {
	::settextstyle(&m_lf);
	::settextcolor(m_color);
	::outtextxy(m_x, m_y, m_text.c_str());
}

bool Text::isHover(){
	if(m_msg.x>=m_x&& m_msg.x <= m_x + ::textwidth(m_text.c_str()) && m_msg.y >= m_y && m_msg.y <= m_y + m_h) {//鼠标位置在按钮范围内
		return true;
	}
	return false;
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
	wcscpy_s(m_lf.lfFaceName, _countof(m_lf.lfFaceName), fontName.c_str());
}

void Text::setFixedSize(int height, int width) {
	m_h = height;
	m_w = width;
	m_lf.lfHeight = height;
	m_lf.lfWidth = width;
	::settextstyle(&m_lf);
}
