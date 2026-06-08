#include "User.h"
#include "FileManager.h"
#include "Account.h"
#include "Transaction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

User::User(std::wstring realname, std::wstring username, std::wstring password)
	: m_realname(realname), m_username(username), m_password(password) {
	// 初始化4个固定账户
	for (int i = 1; i <= 4; i++) {
		m_accounts.push_back(new Account(this, i, 0));
	}
}

bool User::findUser() {
	std::wifstream ifs;
	ifs.open(FileManager::getUsersFilePath());
	if (!ifs.is_open()) {
		std::wcout << L"Users.dat could't be opened!\n";
		return false;
	}
	std::wstring singleUserMessage;
	while (std::getline(ifs, singleUserMessage)) {
		int partitionPos1 = singleUserMessage.find(L'|');
		int partitionPos2 = singleUserMessage.find(L'|', partitionPos1 + 1);
		std::wstring temp_username = singleUserMessage.substr(partitionPos1 + 1, partitionPos2 - partitionPos1 - 1);
		if (temp_username == m_username) {
			return true;
		}
	}
	return false;
}

bool User::loginUser() {
	std::wifstream ifs;
	ifs.open(FileManager::getUsersFilePath());
	if (!ifs.is_open()) {
		std::wcout << L"Users.dat could't be opened!\n";
		return false;
	}
	std::wstring singleUserMessage;
	while (std::getline(ifs, singleUserMessage)) {
		if (singleUserMessage.empty()) {
			continue;
		}                                                  //跳过空行
		int partitionPos1 = singleUserMessage.find(L'|');
		int partitionPos2 = singleUserMessage.find(L'|', partitionPos1 + 1);
		std::wstring temp_username = singleUserMessage.substr(partitionPos1 + 1,partitionPos2-partitionPos1-1);
		std::wstring temp_password = singleUserMessage.substr(partitionPos2 + 1);
		if (temp_username == L"" || temp_password == L"") {
			continue;                                        //跳过无信息
		}
		if (temp_username == m_username) {
			if (temp_password == m_password) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool User::addUser() {
	std::wifstream ifs;
	ifs.open(FileManager::getUsersFilePath());
	if (!ifs.is_open()) {
		std::wcout << L"Users.dat could't be opened!\n";
		return false;
	}
	std::wstring singleUserMessage;
	while (std::getline(ifs, singleUserMessage)) {
		if (singleUserMessage.empty()) {
			continue;
		}
		int partitionPos1 = singleUserMessage.find(L'|');
		int partitionPos2 = singleUserMessage.find(L'|', partitionPos1 + 1);
		std::wstring temp_username = singleUserMessage.substr(partitionPos1 + 1, partitionPos2 - partitionPos1 - 1);
		if (temp_username == m_username) {
			return false;
		}

	}

	std::wstring content = m_realname+L'|'+m_username + L'|' + m_password + L'\n';
	return FileManager::appendTextToFile(FileManager::getUsersFilePath(), content);
}

void User::loadAccounts() {
	std::wstring data = FileManager::readTextFromFile(FileManager::getUserAccountsFilePath(m_username));
	std::wstringstream allData(data);
	std::wstring dataLine;
	std::wstringstream singleData;
	while (std::getline(allData, dataLine)) {
		for (auto& ch : dataLine) {
			if (ch == L'|')ch = L' ';
		}
		singleData.str(dataLine);
		int accountType;
		double balance;
		singleData >> accountType >> balance;
		// 只更新已有账户的余额，不创建新账户
		for (auto acc : m_accounts) {
			if (acc->getAccountType() == accountType) {
				acc->setBalance(balance);
				break;
			}
		}
		singleData.clear();
		singleData.str(L""); //彻底清空：状态 + 缓冲区
	}
}


void User::loadTransactions() {
	for (Transaction* trans : m_transactions) delete trans;
	m_transactions.clear();

	std::wstring data = FileManager::readTextFromFile(
		FileManager::getUserTransactionsFilePath(m_username));
	if (data.empty()) return;

	std::wstringstream allData(data);
	std::wstring line;

	while (std::getline(allData, line)) {
		if (line.empty()) continue;

		std::wstringstream ss(line);
		std::wstring token;

		std::getline(ss, token, L'|');
		int id = std::stoi(token);

		std::getline(ss, token, L'|');
		int type = std::stoi(token);

		std::getline(ss, token, L'|');
		std::wstring date = token;

		std::getline(ss, token, L'|');
		int accountType = std::stoi(token);

		std::getline(ss, token, L'|');
		double amount = std::stod(token);

		m_transactions.push_back(new Transaction(this, type, date, accountType, amount, id));
	}
	// 按日期从新到旧排序
	std::sort(m_transactions.begin(), m_transactions.end(), [](Transaction* a, Transaction* b) {
		return a->getDateString() > b->getDateString();
	});
}

void User::saveAccounts() {
	std::wstring data;
	for (Account* account : m_accounts) {
		data += std::to_wstring(account->getAccountType()) + L'|' + std::to_wstring(account->getBalance()) + L'\n';
	}
	FileManager::writeTextToFile(FileManager::getUserAccountsFilePath(m_username), data);
}

void User::saveTransactions() {
	std::wstring data;
	for (Transaction* trans : m_transactions) {
		data += std::to_wstring(trans->getId()) + L'|' +
				std::to_wstring(trans->getType()) + L'|' +
				trans->getDateString() + L'|' +
				std::to_wstring(trans->getAccountType()) + L'|' +
				std::to_wstring(trans->getAmount()) +  L'\n';
	}
	FileManager::writeTextToFile(FileManager::getUserTransactionsFilePath(m_username), data);
}
