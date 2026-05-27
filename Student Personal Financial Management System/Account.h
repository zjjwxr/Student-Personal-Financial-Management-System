#pragma once

#include <string>
#include <vector>
#include<iostream>
#include<iomanip>
class Account {
private:   
    std::wstring accountName;   //账户名称
    double balance;            //账户余额

public:
    //构造
    Account();
    Account( const std::wstring& name, double bal);

    //获取
    std::wstring getAccountName() const;
    double getBalance() const;

    
    void deposit(double amount);             //存款
    bool withdraw(double amount);            //取款
    void setBalance(double bal);             //设置余额
    void display() const;                    //显示账户余额
};


//账户管理器

class AccountManager {
private:
    std::vector<Account> accounts;   //存储账户

public:
    AccountManager();

    bool addAccount( const std::wstring& name, double balance);   //添加账户
    bool deleteAccount(const std::wstring& accountName);          //删除账户              
    Account* findAccount(const std::wstring& accountName);        //查询账户       
    std::vector<Account>& getAllAccounts();                      //获取所有账户
    double getTotalBalance() const;                              //获取总余额
    void displayAllAccounts() const;                             //显示所有账户
    bool saveToFile() const;          //保存
    bool loadFromFile();              //加载
};


