#pragma once
#include <string>
#include <vector>
#include<iostream>
#include<iomanip>
class User;

enum class AccountType {
    WECHAT = 1,    // 微信
    ALIPAY = 2,    // 支付宝
    BANK = 3,      // 银行卡
    CASH = 4       // 现金
};

class Account {
private:   
    int m_accountType;   //账户名称 1.微信 2.支付宝 3.银行卡 4.现金
    double m_balance;            //账户余额
	User* m_user;                //账户所属用户
public:
    Account(User* user=nullptr, int accountName=1 , double balance=0.0);

    int getAccountType() const { return m_accountType; }
    std::wstring getAccountName() const;
    double getBalance() const { return m_balance; };
    User* getUser() const { return m_user; }

	void loadAccountBalance(); //加载账户余额(如果账户存在）
	void uploadAccountBalance(); //上传账户余额（更新已存在账户余额）

    bool addAccount();//添加新账户

    void deposit(double amount);             //存款
    bool withdraw(double amount);            //取款
    void setBalance(double bal);             //设置余额
};
