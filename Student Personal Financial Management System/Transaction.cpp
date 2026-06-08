#include "Transaction.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <iostream>

int Transaction::generateUniqueId() {
	static int counter = 0;
	
	time_t now = time(nullptr);
	tm t_info;
	localtime_s(&t_info, &now);
	
	int id = ((int)now % 9000) + 1000;
	
	counter++;
	id = (id + counter) % 9000 + 1000;
	
	return id;
}

Transaction::Transaction(User* user , int type , const std::wstring date ,
	int accountType ,
	double amount , int id )
	: m_user(user), m_type(type), m_amount(amount), m_accountType(accountType), m_date(date) {
	if (id == -1) {
		m_id = generateUniqueId();
	} else {
		m_id = id;
	}
	if (date.empty()) {
		time_t now = time(nullptr);
		tm t_info;
		localtime_s(&t_info, &now);
		wchar_t buffer[64];
		wcsftime(buffer, sizeof(buffer) / sizeof(wchar_t), L"%Y-%m-%d", &t_info);
		std::wstring timeStr(buffer);
		size_t pos = 0;
		while ((pos = timeStr.find(L"-0", pos)) != std::wstring::npos) {
			timeStr.erase(pos + 1, 1);
			pos += 1; // 防止死循环，跳过当前 '-'
		}
		m_date = timeStr;
	}
}

std::wstring Transaction::getAccountName() const {
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

void Transaction::uploadTransaction() {
    std::vector<Transaction*> transactions = m_user->getTransactions();
    auto it = std::find_if(transactions.begin(), transactions.end(), [this](Transaction* p) {
        return p->getId() == this->getId();
        });
    if (it != transactions.end()) {
        (*it)->setType(this->getType());
        (*it)->setAmount(this->getAmount());
        (*it)->setAccountType(this->getAccountType());
        (*it)->setDate(this->getDateString());
    }
}

bool Transaction::addTransaction() {
	if (m_user == nullptr) return false;
	int type = this->getType();
	bool check = FileManager::appendTextToFile(FileManager::getUserTransactionsFilePath(m_user->getUsername()),
		std::to_wstring(m_id) + L'|' + std::to_wstring(type) + L'|' +
		this->getDateString() + L'|' +
		std::to_wstring(this->getAccountType()) + L'|' +
		std::to_wstring(this->getAmount()) + L'\n');
	if(check){ m_user->addTransactionVector(this); }
	return check;
}
