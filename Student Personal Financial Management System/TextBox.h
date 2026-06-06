#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
#include <string>
#include <ctime>
#include <algorithm>
class TextBox :
    public BasicWidget {
private:
    Text m_text;
    bool isPassword;
    bool isActive = false;
    
    COLORREF m_defaultColor = WHITE;
	COLORREF m_clickColor = RGB(255, 0, 0);
    COLORREF m_currentColor = WHITE;

	bool m_showCaret = false; // 是否显示插入符
	clock_t m_lastCaretBlinkTime = 0; // 上次插入符闪烁的时间
	int m_caretPosition = 0; // 字符索引前，即0表示在第一个字符前,可以取值到文本长度，即指向末尾
public:
    TextBox(int x=0, int y=0, int w=0, int h=0, bool isPassword = false);
    void show()override;
    void eventLoop(const ExMessage& msg);
    void setText(const std::wstring& text);
    void setTextColor(COLORREF color);
    void setTextFont(const std::wstring& fontName);
    void setTextSize(int height, int width = 0);
    std::wstring getText() {
        return m_text.getText();
    }

private:
    void drawCaret();  // 绘制插入符
	int getCaretPositionX(int pos); // 获取插入符在指定位置的x坐标
    void updateCaretPosition(int newPos);  // 更新插入符位置
    void moveCaretLeft();   // 插入符左移
    void moveCaretRight();  // 插入符右移
    void insertCharacter(wchar_t ch);  // 插入字符
    void deleteCharacter();  // 删除字符
   
};

