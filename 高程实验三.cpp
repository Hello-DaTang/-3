#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 定义账户类型枚举
enum AccountType {
  SAVINGS,        // 普通储蓄账户
  FIXED_DEPOSIT,  // 定期存款账户
  FINANCIAL,      // 理财账户
  CREDIT_CARD     // 信用卡账户
};

// 定义抽象账户类
class Account {
public:
  // 构造函数和析构函数
  Account(string name, int accountNumber, AccountType type, int key);
  virtual ~Account();

  // 抽象方法：存款
  virtual void deposit(double amount) = 0;

  // 抽象方法：取款
  virtual bool withdraw(double amount) = 0;

  // 抽象方法：查询余额
  virtual double getBalance() const = 0;

  // 抽象方法：计算利息收益
  virtual double calculateInterest() const = 0;

  //转账
  virtual bool transfer(double amount, Account* toAccount) = 0;

  // 获取账户信息
  string getName() const;
  int getAccountNumber() const;
  AccountType getType() const;
  double getInterestRate()const;
  int getKEY() const;

protected:
  string name;          // 账户名称
  int accountNumber;    // 账户号码
  AccountType type;     // 账户类型
  double balance;       // 账户余额
  double interestRate;  // 利率
  int key;              // 密码
};

// 普通储蓄账户类
class SavingsAccount : public Account {
public:
  SavingsAccount(string name, int accountNumber,int key);
  virtual ~SavingsAccount();

  virtual void deposit(double amount);
  virtual bool withdraw(double amount);
  virtual double getBalance() const;
  virtual double calculateInterest() const;
  bool transfer(double amount, Account* toAccount);
};

// 定期存款账户类
class FixedDepositAccount : public Account {
public:
  FixedDepositAccount(string name, int accountNumber, int term, int key);
  virtual ~FixedDepositAccount();

  virtual void deposit(double amount);
  virtual bool withdraw(double amount);
  virtual double getBalance() const;
  virtual double calculateInterest() const;
  bool transfer(double amount, Account* toAccount);

private:
  int term;  // 存款期限（月）
};

// 理财账户类
class FinancialAccount : public Account {
public:
  FinancialAccount(string name, int accountNumber, double rate, int key);
  virtual ~FinancialAccount();

  virtual void deposit(double amount);
  virtual bool withdraw(double amount);
  virtual double getBalance() const;
  virtual double calculateInterest() const;
  bool transfer(double amount, Account* toAccount);

private:
  double rate;  // 理财产品的利率
};

// 信用卡账户类
class CreditCardAccount : public Account {
public:
  CreditCardAccount(string name, int accountNumber, double creditLimit, double interestRate, int key);
  virtual ~CreditCardAccount();

  virtual void deposit(double amount);
  virtual bool withdraw(double amount);
  virtual double getBalance() const;
  virtual double calculateInterest() const;
  bool transfer(double amount, Account* toAccount);
  void makePayment(double amount);  // 还款

private:
  double creditLimit;  // 信用卡额度
  double balanceDue;   // 当前应还款额
  double interestRate; // 信用卡利率
};

// 账户管理系统类
class AccountManagementSystem {
public:
  AccountManagementSystem();
  ~AccountManagementSystem();

  // 添加账户
  void addAccount(AccountType type, string name, int accountNumber, int key, double initialDeposit = 0.0);

  // 存款
  void deposit(int accountNumber, double amount);

  // 取款
  bool withdraw(int accountNumber, double amount);

  // 转账
  bool transfer(int fromAccountNumber, int toAccountNumber, double amount);

  // 还款
  void makePayment(int accountNumber, double amount);

  // 查询余额
  double getBalance(int accountNumber) const;

  // 查询利息收益
  double calculateInterest(int accountNumber) const;
  //显示账户信息
  void displayAccountInfo(int accountNumber) const;
  // 显示所有账户的信息
  void displayAllAccountsInfo() const;
  double calculateTotalInterestPaid() const;

  // 查找指定账户编号的账户对象
  int getkey(int accountNumber) const;
private:

  vector<Account*> accounts;  // 存储所有账户
  Account* findAccount(int accountNumber) const;  // 查找账户
};


// 实现抽象账户类
Account::Account(string name, int accountNumber, AccountType type, int key)
    : name(name), accountNumber(accountNumber), type(type), balance(0.0), interestRate(0.0), key(key){}

Account::~Account() {}

string Account::getName() const {
  return name;
}

int Account::getAccountNumber() const {
  return accountNumber;
}
int Account::getKEY() const {
  return key;
}
AccountType Account::getType() const {
  if(type==SAVINGS)
  cout<<"普通储蓄账户"<<endl;
  if(type==FIXED_DEPOSIT)
  cout<<"定期存款账户"<<endl;
  if(type==FINANCIAL)      
  cout<<"理财账户"<<endl;
  if(type==CREDIT_CARD)     
  cout<<"信用卡账户"<<endl;
  return type;
}
double Account::getInterestRate()const{
  return interestRate;
}


// 实现普通储蓄账户类
SavingsAccount::SavingsAccount(string name, int accountNumber, int key)
    : Account(name, accountNumber, SAVINGS, key) {}

SavingsAccount::~SavingsAccount() {}

void SavingsAccount::deposit(double amount) {
  balance += amount;
  cout<<"存款后金额："<<balance<< endl;
}

bool SavingsAccount::withdraw(double amount) {
  if (amount > balance) {
    return false;
  }
  balance -= amount;
  return true;
}

double SavingsAccount::getBalance() const {
  return balance;
}

double SavingsAccount::calculateInterest() const {
  // 计算利息
  return balance * interestRate / 12.0;
}
bool SavingsAccount::transfer(double amount, Account* toAccount) {
  if(this->balance<amount)
  {
    cout<<"ERROR,余额不足，请充值；"<<endl;
    return false;
  }
  
  else
  {
    this->balance-amount;
    toAccount->deposit(amount);
    return true;
  }

}

// 实现定期存款账户类
FixedDepositAccount::FixedDepositAccount(string name, int accountNumber, int term, int key)
    : Account(name, accountNumber, FIXED_DEPOSIT, key), term(term) {}

FixedDepositAccount::~FixedDepositAccount() {}

void FixedDepositAccount::deposit(double amount) {
  balance += amount;
  cout<<"您的存款为："<<balance<<endl;
}

bool FixedDepositAccount::withdraw(double amount) {
  // 判断是否在存款期内
  // 如果是，则不允许取款
  // 如果不是，则允许取款，但要扣除违约金
  cout<<"还在存款期内，不允许取款"<<endl;
  return false;
}

double FixedDepositAccount::getBalance() const {
  return balance;
}

double FixedDepositAccount::calculateInterest() const {
  // 计算利息
  return balance * interestRate * term / 12.0;
}
bool FixedDepositAccount::transfer(double amount, Account* toAccount) {
  cout<<" 不允许转账，直接返回"<<endl;
  return false;
}

// 实现理财账户类
FinancialAccount::FinancialAccount(string name, int accountNumber, double rate, int key)
    : Account(name, accountNumber, FINANCIAL, key), rate(rate) {}

FinancialAccount::~FinancialAccount(){}

void FinancialAccount::deposit(double amount) {
  
}

bool FinancialAccount::withdraw(double amount) {
  if(this->balance<amount)
  {
    cout<<"ERROR,余额不足，请充值；"<<endl;
    return false;
  }
  
  else
  {
    this->balance-=amount;
    cout<<"取款成功，余额为:"<<balance<<endl;
    return true;
  }
}

double FinancialAccount::getBalance() const {
  return balance;
}

double FinancialAccount::calculateInterest() const {
  // 计算利息
  return balance * rate / 12.0;
}bool FinancialAccount::transfer(double amount, Account* toAccount) {
  if(this->balance<amount)
  {
    cout<<"ERROR,余额不足，请充值；"<<endl;
    return false;
  }
  
  else
  {
    this->balance-=amount;
    toAccount->deposit(amount);
    return true;
  }

}

// 实现信用卡账户类
CreditCardAccount::CreditCardAccount(string name, int accountNumber, double creditLimit, double interestRate, int key)
    : Account(name, accountNumber, CREDIT_CARD, key), creditLimit(creditLimit), balanceDue(0.0), interestRate(interestRate) {}

CreditCardAccount::~CreditCardAccount() {}

void CreditCardAccount::deposit(double amount) {
  balance += amount;
  cout<<"您的存款为："<<balance<<endl;
}

bool CreditCardAccount::withdraw(double amount) {
  if (amount > balance) {
    return false;
  }
  balance -= amount;
  cout<<"您的余额还剩："<<balance<<endl;
  return true;
}

bool CreditCardAccount::transfer(double amount, Account* toAccount) {
  cout<<"不允许转账，直接返回"<<endl;
  return false;
}

double CreditCardAccount::getBalance() const {

  return balance;
}

double CreditCardAccount::calculateInterest() const {
  // 计算利息
  return balanceDue * interestRate / 12.0;
}

void CreditCardAccount::makePayment(double amount) {
  balanceDue -= amount;
}

// 实现账户管理系统类
AccountManagementSystem::AccountManagementSystem() {}

AccountManagementSystem::~AccountManagementSystem() {
  // 释放所有账户对象的内存
  for (auto account : accounts) {
    delete account;
  }
}

void AccountManagementSystem::addAccount(AccountType type, string name, int accountNumber, int key, double initialDeposit) {
  Account* account;
  switch (type) {
    case SAVINGS:
      account = new SavingsAccount(name, accountNumber,key);
      break;
    case FIXED_DEPOSIT:
      account = new FixedDepositAccount(name, accountNumber, 12, key);
      break;
    case FINANCIAL:
      account = new FinancialAccount(name, accountNumber, 0.005, key);
      break;
    case CREDIT_CARD:
      account = new CreditCardAccount(name, accountNumber, 5000.0, 0.2, key);
      break;
    default:
      return;
  }
  if (initialDeposit > 0.0) {
    account->deposit(initialDeposit);
  }
  accounts.push_back(account);
}

Account* AccountManagementSystem::findAccount(int accountNumber) const {
  // 查找账户
  for (auto account : accounts) {
    if (account->getAccountNumber() == accountNumber) {
      return account;
    }
  }
  cout<<"未查找到该账户"<<endl;
  return nullptr;
}
int AccountManagementSystem::getkey(int accountNumber) const{
  Account* account = findAccount(accountNumber);
  if (account) {
    return account->getKEY();
  }
  return 0;
}

void AccountManagementSystem::deposit(int accountNumber, double amount) {
  Account* account = findAccount(accountNumber);
  if (account) {
    account->deposit(amount);
  }
}

bool AccountManagementSystem::withdraw(int accountNumber, double amount) {
  Account* account = findAccount(accountNumber);
  if (account) {
    return account->withdraw(amount);
  }
  return false;
}
bool AccountManagementSystem::transfer(int fromAccountNumber, int toAccountNumber, double amount) {
  Account* fromAccount = findAccount(fromAccountNumber);
  Account* toAccount = findAccount(toAccountNumber);
  if (fromAccount && toAccount) {
     fromAccount->withdraw(amount);
      toAccount->deposit(amount);
      return true;
  }
  return false;
}

void AccountManagementSystem::displayAccountInfo(int accountNumber) const {
  Account* account = findAccount(accountNumber);
  if (account) {
    cout << "账户类型: "  << endl;account->getType();
    cout << "账户号主: " << account->getName() << endl;
    cout << "账户卡号: " << account->getAccountNumber() << endl;
    cout << "账户余额: " << account->getBalance() << endl;
    cout << "账户利息: " << account->getInterestRate() << endl;
    cout << endl;
  }
}

void AccountManagementSystem::displayAllAccountsInfo() const {
  for (auto account : accounts) {
    displayAccountInfo(account->getAccountNumber());
  }
}

double AccountManagementSystem::calculateTotalInterestPaid() const {
  double totalInterest = 0.0;
  for (auto account : accounts) {
    totalInterest += account->calculateInterest();
  }
  return totalInterest;
}

//菜单
void menum()
{
  
}
void createNewaccount(AccountManagementSystem &s)
{
  cout<<"开始创建一个账户"<<endl;
  cout<<"请依次输入"<<endl<<"开户人姓名，预期的银行卡号，预设密码，初始存入金额"<<endl;
  string name ;
  int cardNumber;
  int key;
  int i=0;
  double money;
  cin>>name>>cardNumber>>key>>money;
  cout<<"开通普通储蓄账户——————输入1"<<endl;
  cout<<"开通定期存款账户——————输入2"<<endl;
  cout<<"开通理财账户——————————输入3"<<endl;
  cout<<"开通信用卡账户————————输入4"<<endl;
  cout<<"请选择您要开通的账户类型:";
  cin>>i;
  switch (i)
  {
  case 1:s.addAccount(SAVINGS,name,cardNumber,key,money);
    break;
  case 2:s.addAccount(FIXED_DEPOSIT,name,cardNumber,key,money);
    break;
  case 3:s.addAccount(FINANCIAL,name,cardNumber,key,money);
    break;
  case 4:s.addAccount(CREDIT_CARD,name,cardNumber,key,money);
    break;
  default:
    break;
  }
  system("cls");
}
// 一个简单的控制台菜单接口函数
// 定义菜单项的结构体
struct MenuItem {
  char key; // 菜单项的访问键
  string text; // 菜单项的文本
  void (*func)(AccountManagementSystem &s); // 菜单项对应的函数指针
};

// 定义菜单项对应的函数
void func1(AccountManagementSystem &s) {
  cout << "你选择了新建账户" << endl;
  createNewaccount(s);
}

void func2(AccountManagementSystem &s) {
  cout << "你选择了存款" << endl;
  int ID;
  int key;
  double money;
  cout<<"输入卡号和密码"<< endl;
  cin>>ID;
  while(1)
  {
    cin>>key;
   if(s.getkey(ID)==key)
    {
      cout<<"密码正确!!!"<<endl;
      cout<<"输入存入金额:";
      cin>>money;
      s.deposit(ID,money);
      break;
    }
    else
    {
      cout<<"密码错误!!!"<<endl;
      cout<<"请重新输入密码:";
      continue;
    }
  }
}

void func3(AccountManagementSystem &s) {
  cout << "你选择了取款" << endl;
  int ID;
  int key;
  double money;
  cout<<"输入卡号和密码"<< endl;
  cin>>ID;
  while(1)
  {
    cin>>key;
   if(s.getkey(ID)==key)
    {
      cout<<"密码正确!!!"<<endl;
      cout<<"输入取款金额:";
      cin>>money;
      s.withdraw(ID,money);
      break;
    }
    else
    {
      cout<<"密码错误!!!"<<endl;
      cout<<"请重新输入密码:";
      continue;
    }
  }
}

void func4(AccountManagementSystem &s) {
  cout << "你选择了转账" << endl;
  int ID1,ID2,key;
  double money;
  
  cout<<"请输入转出账户和密码:"<< endl;
  cin>>ID1;
  while(1)
  {
    cin>>key;
   if(s.getkey(ID1)==key)
    {
      cout<<"请输入转入账户和金额:"<< endl;
      cin>>ID2>>money;
      s.transfer(ID1,ID2,money);
      break;
    }
    else
    {
      cout<<"密码错误!!!"<<endl;
      cout<<"请重新输入密码:";
      continue;
    }
  }
}

void func5(AccountManagementSystem &s) {
  cout << "你选择了账户信息显示" << endl;
  s.displayAllAccountsInfo();
}
void func6(AccountManagementSystem &s) {
  cout << "你选择了修改密码：" << endl;
  int KEY;
  cout<<"请输入你的新密码:"<< endl;

}

void exit(AccountManagementSystem &s) {
  cout << "退出程序" << endl;
}

// 定义菜单数组，包含6个菜单项
MenuItem menu[] = {
  {'1', "功能1:新建账户", func1},
  {'2', "功能2:存款", func2},
  {'3', "功能3:取款", func3},
  {'4', "功能4:转账", func4},
  {'5', "功能5:显示账户信息", func5},
  {'6', "功能6:修改密码", func6},
  {'0', "退出", exit}
};

// 定义菜单接口函数，显示菜单并根据用户输入执行相应的函数
void showMenu(AccountManagementSystem &s) {
  char choice; // 用户输入的选择
  bool quit = false; // 是否退出的标志
  do {
    system("cls"); // 清屏
    cout << "欢迎使用本程序，请选择一个功能：" << endl;
    // 显示菜单项
    for (int i = 0; i < sizeof(menu) / sizeof(MenuItem); i++) {
      cout << menu[i].key << "." << menu[i].text << endl;
    }
    cin >> choice; // 获取用户输入
    // 根据用户输入执行相应的函数
    for (int i = 0; i < sizeof(menu) / sizeof(MenuItem); i++) {
      if (choice == menu[i].key) {
        menu[i].func(s); // 调用函数指针指向的函数
        if (choice == '0') quit = true; // 如果选择了退出，设置退出标志为真
        break;
      }
    }
    if (!quit) system("pause"); // 如果没有退出，暂停等待用户按任意键继续
  } while (!quit); // 循环直到退出标志为真
}
int main() {
  AccountManagementSystem system;
  showMenu(system);


  cout << "Total Interest Paid: " << system.calculateTotalInterestPaid() << endl;

  return 0;
}
