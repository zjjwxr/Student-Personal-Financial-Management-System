#include "Button.h"

Button::Button(const std::wstring& text,int x, int y, int w, int h,int elipseWidth,int elipseHeight) 
	:BasicWidget(x,y,w,h),m_text(text),m_elipseWidth(elipseWidth),m_elipseHeight(elipseHeight){}

void Button::show() {
	::setfillcolor(m_currentColor);
	::solidroundrect(m_x, m_y, m_x + m_w, m_y + m_h, m_elipseWidth, m_elipseHeight);//最后两个参数是圆角的宽和高，可以根据需要调整

	m_text.setFixedSize(m_text.getTextHeight());
	int tx = m_x + (m_w - ::textwidth(m_text.getText().c_str())) / 2; 
	int ty = m_y + (m_h - ::textheight(m_text.getText().c_str())) / 2;

	m_text.setPosition(tx, ty);
	m_text.show();
}


void Button::eventLoop(const ExMessage& msg) {
	m_msg = msg;
	if (isHover()) {
		m_currentColor = m_hoverColor;
		
	}
	else {
		m_currentColor = m_defaultColor;  //离开变回原色
	}
	if (isClicked()) {
		m_currentColor = m_defaultColor;
		return;
	}
	return;
}

void Button::setDefaultColor(COLORREF color) {
	m_defaultColor = color;
}

void Button::setHoverColor(COLORREF color) {
	m_hoverColor = color;
}

void Button::setTextColor(COLORREF color) {
	m_text.setColor(color);
}

void Button::setTextFont(const std::wstring& fontName) {
	m_text.setFont(fontName);
}

void Button::setTextSize(int height, int width) {
	m_text.setFixedSize(height, width);
}
