#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
class Button :public BasicWidget{
private:
	int m_elipseWidth;
	int m_elipseHeight;
	Text m_text;
	COLORREF m_defaultColor=WHITE;
	COLORREF m_hoverColor=RED;
	COLORREF m_currentColor=WHITE;
	
public:
	Button(const std::wstring& text, int x=0, int y=0, int w=0, int h=0,int elipseWidth=10,int elipseHeight=10);//初始化
	void show() override;//显示按钮
	void eventLoop(const ExMessage& msg);//事件循环，处理按钮的事件

	void setDefaultColor(COLORREF color);
	void setHoverColor(COLORREF color);

	void setTextColor(COLORREF color);
	void setTextFont(const std::wstring& fontName);
	void setTextSize(int height, int width = 0);
};

