#include "TextBox.h"

TextBox::TextBox(int x, int y, int w, int h, bool isPassword) : BasicWidget(x, y, w, h), isPassword(isPassword) {}

void TextBox::show() {
	::setfillcolor(m_currentColor);
	::fillroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 10, 10);

	// 处理插入符闪烁
	clock_t currentTime = clock();
	if (currentTime - m_lastCaretBlinkTime > 500) { // 每500ms闪烁一次
		m_lastCaretBlinkTime = currentTime;
		m_showCaret = !m_showCaret;
	}

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
	drawCaret();
}

void TextBox::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	if (m_msg.message == WM_LBUTTONDOWN) {
		if (isHover()) {
			isActive = true;
			m_currentColor = m_clickColor;
			m_showCaret = true;
			m_lastCaretBlinkTime = clock();// 重置闪烁计时器
			
			// 取点击位置
			int clickX = m_msg.x;
			if (clickX >= getCaretPositionX(m_text.getText().size())) {
				updateCaretPosition(m_text.getText().size());
			}
			else {
				int posBefore = 0;
				while (posBefore < m_text.getText().size()) {
					int caretTempX = getCaretPositionX(posBefore+1);
					if (caretTempX >= clickX)break;
					posBefore++;
				}
				int posAfter = posBefore + 1;
				if (isPassword) {
					if ((clickX - getCaretPositionX(posBefore)) < (::textwidth(_T('*')) / 2)) {
						updateCaretPosition(posBefore);
					}
					else updateCaretPosition(posAfter);
				}
				else {
					if ((clickX - getCaretPositionX(posBefore)) < (::textwidth(m_text.getText()[posBefore]) / 2)) {
						updateCaretPosition(posBefore);
					}
					else updateCaretPosition(posAfter);
				}
			}
			
		}
		else {
			isActive = false;
			m_currentColor = m_defaultColor;
			m_showCaret = false;
		}
	}

	if (!isActive) return;

	if (msg.message == WM_CHAR) {
		wchar_t ch = (wchar_t)msg.ch;
		if (ch >= 32 && ch != 127) {
			insertCharacter(ch);
		}
	}
	if (msg.message == WM_KEYDOWN) {
		switch (msg.vkcode) {
		case VK_BACK:
			deleteCharacter();
			break;
		case VK_LEFT:
			moveCaretLeft();
			break;
		case VK_RIGHT:
			moveCaretRight();
			break;
		case VK_DELETE:
			if (m_caretPosition < (int)m_text.getText().size()) {
				moveCaretRight();
				deleteCharacter();
			}
			break;
		case VK_HOME:
			updateCaretPosition(0);
			break;
		case VK_END:
			updateCaretPosition(m_text.getText().size());
			break;
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

void TextBox::drawCaret() {
	if (!isActive || !m_showCaret)return;

	int caretX = getCaretPositionX(m_caretPosition);
	int caretY = m_y + (m_h - ::textheight(_T("A"))) / 2; // 使用"A"的高度作为基准

	::setlinecolor(WHITE);
	::setlinestyle(PS_SOLID);
	::line(caretX, caretY, caretX, caretY + ::textheight(_T("A")));
}

int TextBox::getCaretPositionX(int pos) {
	std::wstring fullText = m_text.getText();
	std::wstring textBeforeCaret = fullText.substr(0, pos);
	if (isPassword) {
		textBeforeCaret = std::wstring(textBeforeCaret.size(), _T('*'));
	}
	int caretX = m_x + 5 + ::textwidth(textBeforeCaret.c_str());
	return caretX;
}

void TextBox::updateCaretPosition(int newPos) {
	if (newPos < 0)m_caretPosition = 0;
	if (newPos > m_text.getText().size())m_caretPosition = m_text.getText().size();
	else m_caretPosition = newPos;
}

void TextBox::moveCaretLeft() {
	updateCaretPosition(m_caretPosition - 1);
}

void TextBox::moveCaretRight() {
	updateCaretPosition(m_caretPosition + 1);
}

void TextBox::insertCharacter(wchar_t ch) {
	std::wstring temp = m_text.getText();
	temp.insert(m_caretPosition, 1, ch);
	m_text.setText(temp);
	updateCaretPosition(m_caretPosition + 1);
}

void TextBox::deleteCharacter() {
	if (m_caretPosition > 0) {
		std::wstring temp = m_text.getText();
		temp.erase(m_caretPosition - 1, 1);
		m_text.setText(temp);
		updateCaretPosition(m_caretPosition - 1);
	}
}
