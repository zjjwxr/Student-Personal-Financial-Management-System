#pragma once
#include "Configure.h"
#include "BasicWidget.h"
class Text :
    public BasicWidget {
private:
    std::wstring m_text;
    COLORREF m_color = BLACK;
	LPCTSTR m_fontName = _T("微软雅黑");
public:
    Text(const std::wstring& text=_T(""),int x = 0, int y = 0, int w = 0, int h = 20);
    void show()override;

	std::wstring getText() const { return m_text; }
	void setText(const std::wstring& text) { m_text = text; }

    void setColor(COLORREF color);
    void setFont(const std::wstring& fontName);
    void setFixedSize(int height , int width = 0);
};

