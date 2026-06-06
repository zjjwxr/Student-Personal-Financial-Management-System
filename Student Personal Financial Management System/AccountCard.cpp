#include "AccountCard.h"
#include <sstream>
#include <iomanip>
#include <string>
AccountCard::AccountCard(const std::wstring& accountName, double balance,
                         const std::wstring& iconText, COLORREF iconColor,
                         int x, int y, int w, int h)
    : BasicWidget(x, y, w, h), m_accountName(accountName), m_balance(balance),
      m_iconColor(iconColor), m_iconText(iconText) {

    // 创建文本组件
    m_nameText = new Text(m_accountName, x + 70, y + 15, 200, 20);
    m_nameText->setTextSize(16);
    m_nameText->setColor(m_textColor);

    m_balanceText = new Text(formatBalance(m_balance), x + 70, y + 40, 200, 20);
    m_balanceText->setTextSize(20);
    m_balanceText->setColor(m_balanceColor);

    // 创建编辑和删除按钮
    int btnWidth = 60;
    int btnHeight = 30;
    int btnY = y + (h - btnHeight) / 2;

    m_editButton = new Button(L"编辑", x + w - btnWidth * 2 - 20, btnY, btnWidth, btnHeight);
    m_editButton->setTextSize(14);
    m_editButton->setDefaultColor(WHITE);
    m_editButton->setHoverColor(RGB(240, 240, 240));
    m_editButton->setTextColor(RGB(46, 125, 255));

    m_deleteButton = new Button(L"删除", x + w - btnWidth - 10, btnY, btnWidth, btnHeight);
    m_deleteButton->setTextSize(14);
    m_deleteButton->setDefaultColor(WHITE);
    m_deleteButton->setHoverColor(RGB(240, 240, 240));
    m_deleteButton->setTextColor(RGB(255, 107, 107));
}

AccountCard::~AccountCard() {
    delete m_nameText;
    delete m_balanceText;
    delete m_editButton;
    delete m_deleteButton;
}

void AccountCard::show() {
    // 绘制卡片背景
    setfillcolor(m_bgColor);
    solidrectangle(m_x, m_y, m_x + m_w, m_y + m_h);

    // 绘制边框
    setlinestyle(PS_SOLID, 1);
    setlinecolor(m_borderColor);
    rectangle(m_x, m_y, m_x + m_w, m_y + m_h);

    // 绘制图标背景
    int iconSize = 50;
    int iconX = m_x + 15;
    int iconY = m_y + (m_h - iconSize) / 2;

    setfillcolor(m_iconColor);
    solidrectangle(iconX, iconY, iconX + iconSize, iconY + iconSize);

    // 绘制图标文字
    setbkmode(TRANSPARENT);
    settextcolor(WHITE);
    settextstyle(24, 0, L"微软雅黑");
    outtextxy(iconX + (iconSize - textwidth(m_iconText.c_str())) / 2,
              iconY + (iconSize - textheight(m_iconText.c_str())) / 2,
              m_iconText.c_str());

    // 显示文本和按钮
    m_nameText->show();
    m_balanceText->show();
    m_editButton->show();
    m_deleteButton->show();
}

void AccountCard::eventLoop(const ExMessage& msg) {
    m_editButton->eventLoop(msg);
    m_deleteButton->eventLoop(msg);

    // 悬停效果
    if (isHover()) {
        setfillcolor(RGB(250, 250, 250));
        solidrectangle(m_x, m_y, m_x + m_w, m_y + m_h);
    }
}

void AccountCard::setAccountName(const std::wstring& name) {
    m_accountName = name;
    updateText();
}

void AccountCard::setBalance(double balance) {
    m_balance = balance;
    updateText();
}

void AccountCard::setIconText(const std::wstring& iconText) {
    m_iconText = iconText;
}

void AccountCard::setIconColor(COLORREF color) {
    m_iconColor = color;
}

std::wstring AccountCard::getAccountName() const {
    return m_accountName;
}

double AccountCard::getBalance() const {
    return m_balance;
}

bool AccountCard::isEditClicked() const {
    return m_editButton->isClicked();
}

bool AccountCard::isDeleteClicked() const {
    return m_deleteButton->isClicked();
}

void AccountCard::resetClicks() {
    // 按钮的isClicked()会在下一次调用时自动重置
}

void AccountCard::setBgColor(COLORREF color) {
    m_bgColor = color;
}

void AccountCard::setColor(COLORREF color) {
    m_textColor = color;
    m_nameText->setTextColor(color);
}

void AccountCard::setBalanceColor(COLORREF color) {
    m_balanceColor = color;
    m_balanceText->setColor(color);
}

void AccountCard::setBorderColor(COLORREF color) {
    m_borderColor = color;
}

void AccountCard::updateText() {
    m_nameText->setText(m_accountName);
    m_balanceText->setText(formatBalance(m_balance));
}

std::wstring AccountCard::formatBalance(double balance) const {
    std::wstringstream ss;
    ss << L"¥" << std::fixed << std::setprecision(2) << balance;
    return ss.str();
}