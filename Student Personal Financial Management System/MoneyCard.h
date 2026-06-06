#pragma once
#include "BasicWidget.h"
#include "Text.h"
#include "Configure.h"

class MoneyCard :
    public BasicWidget {
private:
    Text* m_title;
    Text* m_amount;
public:
    MoneyCard(const std::wstring& title = L"", const std::wstring& amount = L"¥0.00", int x = 0, int y = 0, int w = 0, int h = 0);
    ~MoneyCard();
    void show() override;
    void setTitleColor(COLORREF color);
    void setAmountColor(COLORREF color);
    void setAmount(const std::wstring& amount);
    void setTitle(const std::wstring& title);
    void setTextColor(COLORREF color);
};

