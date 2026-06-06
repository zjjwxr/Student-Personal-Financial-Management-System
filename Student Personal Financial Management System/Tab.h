#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
#include <vector>
#include <string>
#include <functional>

class Tab : public BasicWidget {
private:
    std::vector<std::wstring> m_tabLabels;
    int m_activeIndex;
    std::vector<Button*> m_tabButtons;
    COLORREF m_activeColor = RGB(46, 125, 255);
    COLORREF m_inactiveColor = RGB(245, 245, 245);
    COLORREF m_activeTextColor = WHITE;
    COLORREF m_inactiveTextColor = RGB(51, 51, 51);

public:
    Tab(int x = 0, int y = 0, int w = 400, int h = 40);
    ~Tab();
    void show() override;
    void eventLoop(const ExMessage& msg);

    void addTab(const std::wstring& label);
    void clearTabs();
    void setActiveIndex(int index);
    int getActiveIndex() const;

    void setActiveColor(COLORREF color);
    void setInactiveColor(COLORREF color);
    void setActiveTextColor(COLORREF color);
    void setInactiveTextColor(COLORREF color);

private:
    void updateTabButtons();
};