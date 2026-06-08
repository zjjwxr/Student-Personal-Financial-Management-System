#pragma once
#include "BasicWidget.h"
#include "Text.h"
#include "Configure.h"

class MoneyCard :
    public BasicWidget {
private:
    Text* m_title;
    Text* m_amount;
    COLORREF m_titleColor;
    COLORREF m_amountColor;
public:
    MoneyCard(const std::wstring& title = L"", double amount = 0.0, int x = 0, int y = 0, int w = 293, int h = 80);
    void show() override;

    void setAmount(double amount);
    void setAmountColor(COLORREF color) { m_amountColor = color; m_amount->setColor(color); }
    void setTitleColor(COLORREF color) { m_titleColor = color; m_title->setColor(color); }
    void setTitle(const std::wstring& title);
};

