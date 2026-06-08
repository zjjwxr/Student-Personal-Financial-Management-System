#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
#include <vector>
#include <string>

class Select : public BasicWidget {
private:
    std::vector<std::wstring> m_options;
    int m_selectedIndex;
    bool m_isOpen;
    Text m_displayText;
    COLORREF m_defaultColor = WHITE;
    COLORREF m_hoverColor = RGB(240, 240, 240);
    COLORREF m_currentColor = WHITE;
    COLORREF m_borderColor = RGB(200, 200, 200);
    COLORREF m_textColor = BLACK;

public:
    Select(int x = 0, int y = 0, int w = 200, int h = 35);
    void show() override;
    void eventLoop(const ExMessage& msg);
    bool isOpen() const { return m_isOpen; }

    void addOption(const std::wstring& option);
    void clearOptions();
    void setSelectedIndex(int index);
    int getSelectedIndex() const;
    std::wstring getSelectedText() const;

    void setTextColor(COLORREF color);
    void setBorderColor(COLORREF color);
    void setTextFont(const std::wstring& fontName);
    void setTextSize(int height, int width = 0);

private:
    void drawDropdown();
    void drawArrow();
    int getOptionHeight() const;
    int getDropdownHeight() const;
}; 
