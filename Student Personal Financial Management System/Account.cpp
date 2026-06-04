#include "Account.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

Account::Account(User* user, const std::wstring& accountName, double balance)
    :m_user(user),m_accountName(accountName),m_balance(balance) {}

void Account::loadAccountBalance() {
    std::vector<Account*> accounts = m_user->getAccounts();
    auto it = std::find_if(accounts.begin(), accounts.end(), [this](Account* p) {
        return p->m_accountName == this->m_accountName;
        });
    if (it != accounts.end()) {
        this->m_balance = (*it)->getBalance();
    }
	//可能需要添加错误处理逻辑，例如账户不存在的情况
}

void Account::uploadAccountBalance() {
    std::vector<Account*> accounts = m_user->getAccounts();
    auto it = std::find_if(accounts.begin(), accounts.end(), [this](Account* p) {
        return p->m_accountName == this->m_accountName;
        });
    if (it != accounts.end()) {
        (*it)->setBalance(this->m_balance);
    }
}

bool Account::addAccount() {
    bool check=FileManager::appendTextToFile(FileManager::getUserAccountsFilePath(m_user->getRealname()),
		m_accountName + L'|' + std::to_wstring(m_balance) + L'\n');
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
