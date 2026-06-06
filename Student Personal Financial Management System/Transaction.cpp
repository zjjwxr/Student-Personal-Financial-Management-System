#include "Transaction.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

Transaction::Transaction()
    : id(0), type(TransactionType::EXPENSE), category(L""), subCategory(L""),
    amount(0.0), description(L""), accountName(L""), date(0) {
}

Transaction::Transaction(int tid, TransactionType t, const std::wstring& cat,
    const std::wstring& subCat, double amt, const std::wstring& desc,
    const std::wstring& accName, time_t dt)
    : id(tid), type(t), category(cat), subCategory(subCat), amount(amt),
    description(desc), accountName(accName), date(dt) {
}

int Transaction::getId() const {
    return id;
}

TransactionType Transaction::getType() const {
    return type;
}

std::wstring Transaction::getCategory() const {
    return category;
}

std::wstring Transaction::getSubCategory() const {
    return subCategory;
}

double Transaction::getAmount() const {
    return amount;
}

std::wstring Transaction::getDescription() const {
    return description;
}

std::wstring Transaction::getAccountName() const {
    return accountName;
}

time_t Transaction::getDate() const {
    return date;
}

void Transaction::setId(int tid) {
    id = tid;
}

void Transaction::display() const {                       //待完善
    
}

std::wstring Transaction::getDateString() const {
    struct tm timeinfo;
    localtime_s(&timeinfo, &date);
    wchar_t buffer[80];
    wcsftime(buffer, sizeof(buffer), L"%Y-%m-%d %H:%M:%S", &timeinfo);
    return std::wstring(buffer);
}

// TransactionManager 实现
TransactionManager::TransactionManager() : nextId(1) {}

bool TransactionManager::addTransaction(TransactionType type, const std::wstring& category,
    const std::wstring& subCategory, double amount,
    const std::wstring& description, const std::wstring& accountName) {
    time_t now = time(nullptr);
    Transaction trans(nextId, type, category, subCategory, amount, description, accountName, now);
    transactions.push_back(trans);
    nextId++;
    return true;
}

bool TransactionManager::deleteTransaction(int id) {
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        if (it->getId() == id) {
            transactions.erase(it);
            return true;
        }
    }
    return false;
}

Transaction* TransactionManager::findTransaction(int id) {
    for (auto& trans : transactions) {
        if (trans.getId() == id) {
            return &trans;
        }
    }
    return nullptr;
}

std::vector<Transaction>& TransactionManager::getAllTransactions() {
    return transactions;
}

std::vector<Transaction> TransactionManager::getTransactionsByCategory(const std::wstring& category) {
    std::vector<Transaction> result;
    for (const auto& trans : transactions) {
        if (trans.getCategory() == category) {
            result.push_back(trans);
        }
    }
    return result;
}

std::vector<Transaction> TransactionManager::getTransactionsByDateRange(time_t startDate, time_t endDate) {
    std::vector<Transaction> result;
    for (const auto& trans : transactions) {
        if (trans.getDate() >= startDate && trans.getDate() <= endDate) {
            result.push_back(trans);
        }
    }
    return result;
}

std::vector<Transaction> TransactionManager::getTransactionsByMonth(int year, int month) {
    std::vector<Transaction> result;
    for (const auto& trans : transactions) {
        time_t date = trans.getDate();
        struct tm timeinfo;
        localtime_s(&timeinfo, &date);
        if (timeinfo.tm_year + 1900 == year && timeinfo.tm_mon + 1 == month) {
            result.push_back(trans);
        }
    }
    return result;
}

double TransactionManager::getTotalExpenseByCategory(const std::wstring& category) const {
    double total = 0.0;
    for (const auto& trans : transactions) {
        if (trans.getType() == TransactionType::EXPENSE && trans.getCategory() == category) {
            total += trans.getAmount();
        }
    }
    return total;
}

double TransactionManager::getTotalIncomeByCategory(const std::wstring& category) const {
    double total = 0.0;
    for (const auto& trans : transactions) {
        if (trans.getType() == TransactionType::INCOME && trans.getCategory() == category) {
            total += trans.getAmount();
        }
    }
    return total;
}

double TransactionManager::getTotalExpenseByDateRange(time_t startDate, time_t endDate) const {
    double total = 0.0;
    for (const auto& trans : transactions) {
        if (trans.getType() == TransactionType::EXPENSE &&
            trans.getDate() >= startDate && trans.getDate() <= endDate) {
            total += trans.getAmount();
        }
    }
    return total;
}

double TransactionManager::getTotalIncomeByDateRange(time_t startDate, time_t endDate) const {
    double total = 0.0;
    for (const auto& trans : transactions) {
        if (trans.getType() == TransactionType::INCOME &&
            trans.getDate() >= startDate && trans.getDate() <= endDate) {
            total += trans.getAmount();
        }
    }
    return total;
}

void TransactionManager::displayAllTransactions() const {
}

bool TransactionManager::saveToFile(const std::wstring& filepath) const {
    std::wstring content;

    // 写入数量
    content += std::to_wstring(transactions.size()) + L"\n";

    for (const auto& trans : transactions) {
        content += std::to_wstring(trans.getId()) + L"|"
            + std::to_wstring(static_cast<int>(trans.getType())) + L"|"
            + trans.getCategory() + L"|"
            + trans.getSubCategory() + L"|"
            + std::to_wstring(trans.getAmount()) + L"|"
            + trans.getDescription() + L"|"
            + trans.getAccountName() + L"|"
            + std::to_wstring(trans.getDate()) + L"\n";
    }

    return FileManager::writeTextToFile(filepath, content);
}

bool TransactionManager::loadFromFile(const std::wstring& filepath) {
    if (!FileManager::fileExists(filepath)) return false;

    std::wstring content = FileManager::readTextFromFile(filepath);
    std::wstringstream ss(content);
    std::wstring line;

    transactions.clear();
    nextId = 1;

    // 读取数量
    if (!std::getline(ss, line)) return false;
    int count = std::stoi(line);

    for (int i = 0; i < count; ++i) {
        if (!std::getline(ss, line)) break;
        if (line.empty()) continue;

        std::vector<std::wstring> tokens;
        size_t start = 0;
        size_t pos;
        while ((pos = line.find(L'|', start)) != std::wstring::npos) {
            tokens.push_back(line.substr(start, pos - start));
            start = pos + 1;
        }
        tokens.push_back(line.substr(start));

        if (tokens.size() < 8) continue;

        int id = std::stoi(tokens[0]);
        int typeInt = std::stoi(tokens[1]);
        std::wstring category = tokens[2];
        std::wstring subCategory = tokens[3];
        double amount = std::stod(tokens[4]);
        std::wstring description = tokens[5];
        std::wstring accountName = tokens[6];
        time_t date = std::stoll(tokens[7]);

        Transaction trans(id, static_cast<TransactionType>(typeInt),
            category, subCategory, amount,
            description, accountName, date);
        transactions.push_back(trans);

        if (id >= nextId) {
            nextId = id + 1;
        }
    }

    return !transactions.empty();
}