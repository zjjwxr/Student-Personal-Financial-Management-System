#pragma once
#include "Configure.h"
#include "BasicWidget.h"
class Text :
    public BasicWidget {
private:
    std::wstring m_text;
    COLORREF m_color = BLACK;
    COLORREF m_defaultColor = BLACK;
	COLORREF m_hoverColor = RGB(77, 77, 77); 
    LOGFONT m_lf{};
public:
    Text(const std::wstring& text=_T(""),int x = 0, int y = 0, int w = 0, int h = 20);
    void show()override;
    bool isHover();
    void eventLoop(const ExMessage& msg);
    
	std::wstring getText() const { return m_text; }
    int getTextHeight() const { return m_h; }
	void setText(const std::wstring& text) { m_text = text; }

    void setColor(COLORREF color);
    void setFont(const std::wstring& fontName);
    void setFixedSize(int height , int width = 0);
};

