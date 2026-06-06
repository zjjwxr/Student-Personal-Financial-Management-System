#pragma once
#include "BasicWidget.h"
#include "Configure.h"
#include "Text.h"
#include "Button.h"
#include <string>

class AccountCard : public BasicWidget {
private:
    std::wstring m_accountName;
    double m_balance;
    COLORREF m_iconColor;
    std::wstring m_iconText;

    Text* m_nameText;
    Text* m_balanceText;
    Button* m_editButton;
    Button* m_deleteButton;

    COLORREF m_bgColor = WHITE;
    COLORREF m_textColor = RGB(51, 51, 51);
    COLORREF m_balanceColor = RGB(51, 51, 51);
    COLORREF m_borderColor = RGB(230, 230, 230);

public:
    AccountCard(const std::wstring& accountName = L"", double balance = 0.0,
                const std::wstring& iconText = L"💰", COLORREF iconColor = RGB(238, 180, 34),
                int x = 0, int y = 0, int w = 700, int h = 80);
    ~AccountCard();

    void show() override;
    void eventLoop(const ExMessage& msg);

    void setAccountName(const std::wstring& name);
    void setBalance(double balance);
    void setIconText(const std::wstring& iconText);
    void setIconColor(COLORREF color);

    std::wstring getAccountName() const;
    double getBalance() const;

    bool isEditClicked() const;
    bool isDeleteClicked() const;
    void resetClicks();

    void setBgColor(COLORREF color);
    void setTextColor(COLORREF color);
    void setBalanceColor(COLORREF color);
    void setBorderColor(COLORREF color);

private:
    void updateText();
    std::wstring formatBalance(double balance) const;
};