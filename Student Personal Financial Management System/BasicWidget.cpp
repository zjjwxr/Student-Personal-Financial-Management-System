#include "BasicWidget.h"

BasicWidget::BasicWidget(int x, int y, int w, int h):m_x(x),m_y(y),m_w(w),m_h(h) {
}

int BasicWidget::getWidth() const {
	return m_w;
}

int BasicWidget::getHeight() const {
    return m_h;
}

void BasicWidget::setFixedSize(int w, int h) {
    m_w = w;
    m_h = h;
}

int BasicWidget::getX() const {
    return m_x;
}

int BasicWidget::getY() const {
    return m_y;
}

void BasicWidget::setPosition(int x, int y) {
	m_x = x;
	m_y = y;
}


bool BasicWidget::isHover() {
	if (m_msg.x >= m_x && m_msg.x <= m_x + m_w && m_msg.y >= m_y && m_msg.y <= m_y + m_h) {//鼠标位置在按钮范围内
		return true;
	}
	return false;
}

bool BasicWidget::isClicked() {
	if (isHover()) {
		if (m_msg.message == WM_LBUTTONDOWN) {//左键按下事件
			return true;
		}
	}
	return false;
}