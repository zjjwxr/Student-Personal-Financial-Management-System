#pragma once
#include <string>
#include <vector>
#include <ctime>

enum class TransactionType {
    INCOME,
    EXPENSE
};

class Transaction {
private:
    int id;                                              //单笔交易唯一id
    TransactionType type;                                //收入或支出
    std::wstring category;                                //交易主类别
    std::wstring subCategory;                             //交易子类别
    double amount;                                        //交易金额
    std::wstring description;                              //该交易备注
    std::wstring accountName;                               //交易账户（如微信）
    time_t date;                                            //交易时间

public:


    //构建
    Transaction();
    Transaction(int tid, TransactionType t, const std::wstring& cat,
        const std::wstring& subCat, double amt, const std::wstring& desc,
        const std::wstring& accName, time_t dt);


    //获取函数
    int getId() const;
    TransactionType getType() const;
    std::wstring getCategory() const;
    std::wstring getSubCategory() const;
    double getAmount() const;
    std::wstring getDescription() const;
    std::wstring getAccountName() const;
    time_t getDate() const;
    void setId(int tid);
    std::wstring getDateString() const;
    
    //显示
    void display() const;


};





//交易管理器
class TransactionManager {
private:
    std::vector<Transaction> transactions;   //储存交易
    int nextId;                              //递增id

public:
    TransactionManager();


    bool addTransaction(TransactionType type, const std::wstring& category,      
        const std::wstring& subCategory, double amount,
        const std::wstring& description, const std::wstring& accountName);       //添加交易

    bool deleteTransaction(int id);                                             //删去交易
   
    Transaction* findTransaction(int id);                                        //查询交易

    std::vector<Transaction>& getAllTransactions();                              //获取所有交易

    std::vector<Transaction> getTransactionsByCategory(const std::wstring& category);  //获取某一类别所有的交易

    std::vector<Transaction> getTransactionsByDateRange(time_t startDate, time_t endDate);   //获取某段时间的所有交易

    std::vector<Transaction> getTransactionsByMonth(int year, int month);                //获取某月的所有交易

    double getTotalExpenseByCategory(const std::wstring& category) const;                  //获取某一类别所有支出交易

    double getTotalIncomeByCategory(const std::wstring& category) const;                    //获取某一类别所有收入交易

    double getTotalExpenseByDateRange(time_t startDate, time_t endDate) const;               //获取某月的所有支出交易

    double getTotalIncomeByDateRange(time_t startDate, time_t endDate) const;                //获取某月的所有收入交易

    void displayAllTransactions() const;                                                   //显示所有交易

    bool saveToFile() const;                                      //保存

    bool loadFromFile();                                           //加载
};
