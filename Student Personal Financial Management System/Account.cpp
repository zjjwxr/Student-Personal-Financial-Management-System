#include "Account.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

Account::Account() :  accountName(L""), balance(0.0) {}

Account::Account( const std::wstring& name, double bal)
    :  accountName(name), balance(bal) {
}



std::wstring Account::getAccountName() const {
    return accountName;
}

double Account::getBalance() const {
    return balance;
}

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Account::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

void Account::setBalance(double bal) {
    balance = bal;
}

void Account::display() const {         //待完善
    
}



// AccountManager 实现
AccountManager::AccountManager() {}

bool AccountManager::addAccount( const std::wstring& name, double balance) {
    // 检查账户名称是否已存在
    for (const auto& acc : accounts) {
        if (acc.getAccountName() == name) {
            return false;
        }
    }

    accounts.emplace_back( name, balance);
    return true;
}

bool AccountManager::deleteAccount(const std::wstring& accountName) {
    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->getAccountName() == accountName) {
            accounts.erase(it);
            return true;
        }
    }
    return false;
}

Account* AccountManager::findAccount(const std::wstring& accountName) {
    for (auto& acc : accounts) {
        if (acc.getAccountName() == accountName) {
            return &acc;
        }
    }
    return nullptr;
}



std::vector<Account>& AccountManager::getAllAccounts() {
    return accounts;
}

double AccountManager::getTotalBalance() const {
    double total = 0.0;
    for (const auto& acc : accounts) {
        total += acc.getBalance();
    }
    return total;
}

void AccountManager::displayAllAccounts() const {                 //待完善
   
}


bool AccountManager::saveToFile() const {
    std::wstring filepath = FileManager::getDataDirectory() + L"accounts.dat";
    std::wstring content;

    // 写入数量
    content += std::to_wstring(accounts.size()) + L"\n";

    for (const auto& acc : accounts) {
        content += acc.getAccountName() + L"|"
            + std::to_wstring(acc.getBalance()) + L"\n";
    }

    return FileManager::writeTextToFile(filepath, content);
}

bool AccountManager::loadFromFile() {
    std::wstring filepath = FileManager::getDataDirectory() + L"accounts.dat";
    if (!FileManager::fileExists(filepath)) return false;

    std::wstring content = FileManager::readTextFromFile(filepath);
    std::wstringstream ss(content);
    std::wstring line;

    accounts.clear();

    // 读取数量
    if (!std::getline(ss, line)) return false;
    int count = std::stoi(line);

    for (int i = 0; i < count; ++i) {
        if (!std::getline(ss, line)) break;
        if (line.empty()) continue;

        size_t pos = line.find(L'|');
        if (pos != std::wstring::npos) {
            std::wstring name = line.substr(0, pos);
            double balance = std::stod(line.substr(pos + 1));
            accounts.emplace_back(name, balance);
        }
    }

    return !accounts.empty();
}