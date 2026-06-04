#pragma once
#include "User.h"
#include "FileManager.h"
#include <string>
#include <vector>
#include<iostream>
#include<iomanip>
class Account {
private:   
    std::wstring m_accountName;   //账户名称
    double m_balance;            //账户余额
	User* m_user;                //账户所属用户
public:
    Account(User* user=nullptr, const std::wstring& accountName=L"", double balance=0.0);

    std::wstring getAccountName() const { return m_accountName; };
    double getBalance() const { return m_balance; };

	void loadAccountBalance(); //加载账户余额(如果账户存在）
	void uploadAccountBalance(); //上传账户余额（更新账户余额）

    bool addAccount();//添加新账户

    void deposit(double amount);             //存款
    bool withdraw(double amount);            //取款
    void setBalance(double bal);             //设置余额
};
