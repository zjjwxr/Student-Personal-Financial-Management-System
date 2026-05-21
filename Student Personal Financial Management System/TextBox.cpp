#include "TextBox.h"

TextBox::TextBox(int x, int y, int w, int h, bool isPassword) : BasicWidget(x, y, w, h), isPassword(isPassword) {}

void TextBox::show() {
	::setfillcolor(m_currentColor);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	Text displayText = m_text;
	if (isPassword) {
		std::wstring temp(m_text.getText().size() - 1, L'*');
		temp += m_text.getText().back(); // 显示最后一个字符
		displayText.setText(temp);
	}

	int tx = m_x + 5;
	int ty = m_y + (m_h - ::textheight(displayText.getText().c_str())) / 2;
	
	displayText.setPosition(tx, ty);
	displayText.show();
}

void TextBox::eventLoop(const ExMessage& msg) {
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
			std::wstring temp = m_text.getText();
			temp += ch;
			m_text.setText(temp);
		}
	}
	if (msg.message == WM_KEYDOWN) {
		if (msg.vkcode == VK_BACK && !m_text.getText().empty()) {
			std::wstring temp = m_text.getText();
			temp.pop_back();
			m_text.setText(temp);
		}
	}
}

void TextBox::setTextColor(COLORREF color) {
	m_text.setColor(color);
}

void TextBox::setTextFont(const std::wstring& fontName) {
	m_text.setFont(fontName);
}

void TextBox::setTextSize(int height, int width) {
	m_text.setFixedSize(height, width);
}