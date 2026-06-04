#pragma once
#include <string>
#include <vector>
#include "Account.h"
#include "Transaction.h"

class User {
private:
    std::wstring m_realname;
    std::wstring m_username;
    std::wstring m_password;
    std::vector<Account*> m_accounts;
    std::vector<Transaction*> m_transactions;
public:
    User(std::wstring realname=L"",std::wstring username = L"", std::wstring password = L"");

	bool findUser(); //检查用户是否存在
    bool loginUser(); //登录逻辑
    bool addUser(); //注册逻辑

    std::wstring getRealname() const { return m_realname; }

	void loadAccounts(); //加载账户数据
	void loadTransactions(); //加载交易数据
    void addAccountVector(Account* account) { m_accounts.push_back(account); }
    void addTransactionVector(Transaction* transaction) { m_transactions.push_back(transaction); }
    std::vector<Account*> getAccounts() const { return m_accounts; }
    std::vector<Transaction*> getTransactions() const { return m_transactions; }

	void saveAccounts(); //保存账户数据
	void saveTransactions(); //保存交易数据
};