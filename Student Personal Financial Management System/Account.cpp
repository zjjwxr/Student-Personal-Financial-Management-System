#include "Account.h"
#include "FileManager.h"
#include "User.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

Account::Account(User* user, int accountType, double balance)
    :m_user(user),m_accountType(accountType),m_balance(balance) {}

void Account::loadAccountBalance() {
    std::vector<Account*> accounts = m_user->getAccounts();
    auto it = std::find_if(accounts.begin(), accounts.end(), [this](Account* p) {
        return p->m_accountType == this->m_accountType;
        });
    if (it != accounts.end()) {
        this->m_balance = (*it)->getBalance();
    }
	//可能需要添加错误处理逻辑，例如账户不存在的情况
}

std::wstring Account::getAccountName() const {
    switch (getAccountType()) {
    case 1:
        return L"微信";
    case 2:
        return L"支付宝";
    case 3:
        return L"银行卡";
    case 4:
        return L"现金";
    default:
        return L"未知账户";
    }
}

void Account::uploadAccountBalance() {
    std::vector<Account*> accounts = m_user->getAccounts();
    auto it = std::find_if(accounts.begin(), accounts.end(), [this](Account* p) {
        return p->m_accountType == this->m_accountType;
        });
    if (it != accounts.end()) {
        (*it)->setBalance(this->m_balance);
    }
}

bool Account::addAccount() {
    if (m_user == nullptr) return false;
    bool check=FileManager::appendTextToFile(FileManager::getUserAccountsFilePath(m_user->getUsername()),
		std::to_wstring(m_accountType) + L'|' + std::to_wstring(m_balance) + L'\n');
    if (check) {
        m_user->addAccountVector(this);
    }
    return check;

}

void Account::deposit(double amount) {
    if (amount > 0) {
        m_balance += amount;
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && m_balance >= amount) {
        m_balance -= amount;
        return true;
    }
    return false;
}

void Account::setBalance(double bal) {
    m_balance = bal;
}
