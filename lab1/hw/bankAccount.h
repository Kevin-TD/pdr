class bankAccount {
public: 
    // A default constructor that will be called when a program creates a bankAccount object. This constructor should set the bankAccount balance to $0.00;
    bankAccount(); 
    
    // A constructor that will be called when a program creates a bankAccount object with an initial balance.
    bankAccount(double amount);

    // A destructor that will be called when an object is deleted from program memory. You must have this in your .h and .cpp file, but you can leave the implementation empty
    ~bankAccount();

    // A method that withdraws the specified amount of money from your bank account. The method will return the new amount in the bank account after the withdraw goes through. If the withdraw amount is too high, don’t withdraw any amount and return the current balance in the account. You can assume that amount >= 0.
    double withdraw(double amount);

    // A method that deposits the specified amount of money from your bank account. The method will return the new amount in the bank account after the deposit goes through. You can assume that amount >= 0.
    double deposit(double amount);

    // A method that will return the balance currently in the bank account.
    double getBalance();
private: 
    // A private variable that will hold the amount of money in the bank account.
    double balance; 
};