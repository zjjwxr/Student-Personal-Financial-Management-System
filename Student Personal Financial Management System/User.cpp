#include "User.h"
#include "FileManager.h"
#include "Account.h"
#include "Transaction.h"

#include <iostream>
#include <fstream>
#include <sstream>

User::User(std::wstring realname, std::wstring username, std::wstring password)
	: m_realname(realname), m_username(username), m_password(password) {
	m_transactionManager = new TransactionManager();
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
	std::wstring data=FileManager::readTextFromFile(FileManager::getUserAccountsFilePath(m_username));
	std::wstringstream allData(data);
	std::wstring dataLine;
	std::wstringstream singleData;
	while (std::getline(allData,dataLine)) {
		for (auto& ch : dataLine) {
			if (ch == L'|')ch = L' ';
		}
		singleData.str(dataLine);
		std::wstring accountName;
		double balance;
		singleData >> accountName >> balance;
		m_accounts.push_back(new Account(this, accountName, balance));
		singleData.clear();
	}
}

void User::loadTransactions() {
	std::wstring filepath = FileManager::getUserTransactionsFilePath(m_username);
	if (m_transactionManager->loadFromFile(filepath)) {
		std::vector<Transaction>& allTrans = m_transactionManager->getAllTransactions();
		m_transactions.clear();
		for (auto& trans : allTrans) {
			m_transactions.push_back(&trans);
		}
	}
}

void User::saveAccounts() {
	std::wstring data;
	for (Account* account : m_accounts) {
		data += account->getAccountName() + L'|' + std::to_wstring(account->getBalance()) + L'\n';
	}
	FileManager::writeTextToFile(FileManager::getUserAccountsFilePath(m_username), data);
}

void User::saveTransactions() {
	std::wstring filepath = FileManager::getUserTransactionsFilePath(m_username);
	m_transactionManager->saveToFile(filepath);
}
