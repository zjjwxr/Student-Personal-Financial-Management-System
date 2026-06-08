#include "AccountCard.h"
#include "Transaction.h"
#include "User.h"
#include <sstream>
#include <iomanip>
#include <locale>

static std::wstring FormatDouble(double val) {
    std::wostringstream woss;
    woss.imbue(std::locale(""));
    woss << std::fixed << std::setprecision(2) << val;
    return woss.str();
}

AccountCard::AccountCard(Account* account, int x, int y, int w, int h)
    : BasicWidget(x, y, w, h), m_account(account), m_isEditing(false),
    m_editBtn(nullptr), m_editBox(nullptr), m_wasEditing(false) {

    m_name = new Text(account->getAccountName());
    m_balance = new Text(L"¥" + FormatDouble(account->getBalance()));

    m_editBtn = new Button(L"编辑", m_x + m_w - 100, m_y + 25, 70, 30, 10, 10);
    m_editBtn->setDefaultColor(RGB(46, 125, 255));
    m_editBtn->setHoverColor(RGB(36, 105, 255));
    m_editBtn->setTextColor(WHITE);

    m_name->setPosition(m_x + 80, m_y + 20);
    m_balance->setPosition(m_x + 80, m_y + 48);
    m_name->setFixedSize(16);
    m_balance->setFixedSize(20);
    m_name->setColor(RGB(51, 51, 51));
    m_balance->setColor(RGB(51, 51, 51));

    switch (account->getAccountType()) {
    case 1: m_icon = L"💚"; m_iconColor = RGB(7, 193, 96); break;
    case 2: m_icon = L"💙"; m_iconColor = RGB(22, 119, 255); break;
    case 3: m_icon = L"🏦"; m_iconColor = RGB(25, 25, 112); break;
    case 4: m_icon = L"💰"; m_iconColor = RGB(238, 180, 34); break;
    default: m_icon = L"💳"; m_iconColor = RGB(102, 102, 102);
    }
}

AccountCard::~AccountCard() {
    delete m_name;
    delete m_balance;
    delete m_editBtn;
    delete m_editBox;
}

void AccountCard::updateBalanceText() {
    m_balance->setText(L"¥" + FormatDouble(m_account->getBalance()));
}

void AccountCard::setBalance(double balance) {
    m_account->setBalance(balance);
    updateBalanceText();
}

void AccountCard::show() {
    if (m_account != nullptr) {
        updateBalanceText();
    }

    setfillcolor(WHITE);
    setlinecolor(RGB(240, 240, 240));
    ::solidroundrect(m_x, m_y, m_x + m_w, m_y + m_h, 12, 12);
    ::roundrect(m_x, m_y, m_x + m_w, m_y + m_h, 12, 12);

    setfillcolor(m_iconColor);
    ::solidroundrect(m_x + 15, m_y + 15, m_x + 65, m_y + 65, 12, 12);

    settextcolor(WHITE);
    settextstyle(24, 0, L"Microsoft YaHei");
    ::outtextxy(m_x + 30, m_y + 22, m_icon.c_str());

    m_name->show();
    m_balance->show();

    if (!m_isEditing) {
        m_editBtn->show();
    }
    else {
        if (!m_editBox) {
            m_editBox = new TextBox(m_x + m_w - 100, m_y + 22, 70, 30, false);
        }
        m_editBox->show();
    }

    m_wasEditing = m_isEditing;
}

void AccountCard::eventLoop(ExMessage& msg) {
    m_localMsg = msg;

    if (!m_isEditing) {
        m_editBtn->eventLoop(msg);
        if (m_editBtn->isClicked()) {
            m_isEditing = true;
            delete m_editBox;
            m_editBox = new TextBox(m_x + m_w - 100, m_y + 22, 70, 30, false);
        }
    }
    else {
        if (m_editBox) {
            m_editBox->eventLoop(msg);

            if (msg.message == WM_KEYDOWN && msg.vkcode == VK_RETURN) {
                std::wstring input = m_editBox->getText();
                if (!input.empty() && m_account != nullptr) {
                    try {
                        double newBalance = std::stod(input);
                        double oldBalance = m_account->getBalance();
                        double diff = newBalance - oldBalance;

                        m_account->setBalance(newBalance);
                        updateBalanceText();

                        if (diff != 0 && m_account->getUser() != nullptr) {
                            Transaction* trans = new Transaction(
                                m_account->getUser(),
                                diff > 0 ? 2 : 1,
                                L"",
                                m_account->getAccountType(),
                                abs(diff)
                            );
                            trans->addTransaction();
                            m_account->getUser()->saveAccounts();
                        }
                    }
                    catch (...) {}
                }
                finishEditing();
            }

            if (msg.message == WM_LBUTTONDOWN) {
                int boxX = m_x + m_w - 100;
                int boxY = m_y + 22;
                int boxW = 70;
                int boxH = 30;
                if (!(msg.x >= boxX && msg.x <= boxX + boxW && msg.y >= boxY && msg.y <= boxY + boxH)) {
                    finishEditing();
                }
            }
        }
    }
}

void AccountCard::finishEditing() {
    m_isEditing = false;
    if(m_editBox!=nullptr){
        delete m_editBox;
        m_editBox = nullptr;
    }
}
