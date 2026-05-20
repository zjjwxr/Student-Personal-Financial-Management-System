#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include <string>
#include <ctime>
class TextBox :
    public BasicWidget {
private:
    std::wstring m_text;
    bool isPassword;
    bool isActive = false;
    
    COLORREF m_defaultColor = WHITE;
	COLORREF m_clickColor = RGB(255, 0, 0);
    COLORREF m_currentColor = WHITE;
public:
    TextBox(int x=0, int y=0, int w=0, int h=0, bool isPassword = false);
    void show()override;
    void eventLoop(const ExMessage& msg);
};

