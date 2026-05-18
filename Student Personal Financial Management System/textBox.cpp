#include "textBox.h"

textBox::textBox(int x, int y, int w, int h, bool isPassword) : BasicWidget(x, y, w, h), isPassword(isPassword) {}

void textBox::show() {
	::setfillcolor(m_currentColor);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	std::wstring displayText = isPassword ? std::wstring(m_text.size(), L'*') : m_text;

	::settextcolor(BLACK);
	int tx = m_x + 5;
	int ty = m_y + (m_h - ::textheight(displayText.c_str())) / 2;
	outtextxy(tx, ty, displayText.c_str());
}

void textBox::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	if (m_msg.message == WM_LBUTTONDOWN) {
		if (isHover()) {
			isActive = true;
			m_currentColor = m_clickColor;
		}
		else {
			isActive = false;
			m_currentColor = m_defaultColor;
		}
	}

	if (!isActive) return;

	if (msg.message == WM_CHAR) {
		wchar_t ch = (wchar_t)msg.ch;
		if (ch >= 32 && ch != 127) {
			m_text.push_back(ch);
		}
	}
	if (msg.message == WM_KEYDOWN) {
		if (msg.vkcode == VK_BACK && !m_text.empty()) {
			m_text.pop_back();
		}
	}
}

