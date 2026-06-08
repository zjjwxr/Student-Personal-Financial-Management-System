#pragma once
#include <string>
#include <vector>
#include <ctime>

class User;

enum class TransactionType {
    EXPENSE = 1,  // 支出
    INCOME = 2   // 收入
};

class Transaction {
private:
    int m_id;                                           //交易唯一标识ID
    int m_type;                                //收入或支出 1.支出，2.收入
    double m_amount;                                        //交易金额
    int m_accountType;                               //交易账户（如微信）1.微信 2.支付宝 3.银行卡 4.现金
    std::wstring m_date;                                       //交易时间
    User* m_user;                                         //交易所属用户
    
    static int generateUniqueId();                        //生成唯一ID
public:
    Transaction(User* user = nullptr,  int type = 1, const std::wstring date = L"", 
        int accountType = 1,
        double amount = 0.0,  int id = -1);

    int getId() const { return m_id; }
    void setId(int id) { m_id = id; }
    int getType() const { return m_type; }
    double getAmount() const { return m_amount; }
    int getAccountType() const { return m_accountType; }
    std::wstring getAccountName() const;
    std::wstring getDateString() const { return m_date; }
    User* getUser() const { return m_user; }
    void setUser(User* user) { m_user = user; }
    void setType(int type) { m_type = type; }
    void setAmount(double amount) { m_amount = amount; }
    void setAccountType(int accountType) { m_accountType = accountType; }
    void setDate(const std::wstring& date) { m_date = date; }

	void uploadTransaction(); //上传交易数据（更新已存在交易数据） 暂时用不上

	bool addTransaction(); //添加新交易
};






