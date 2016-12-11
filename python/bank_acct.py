#! /usr/bin/python

class BankAccount:
    def __init__(self):
        self.balance = 0;
        print("Bank Account Created");

    def deposit(self, amount):
        self.balance += amount;
        return self.balance;

    def withdraw(self, amount):
        self.balance -= amount;
        return self.balance;

class MinimumBalanceAccount(BankAccount):

    def __init__(self, min_bal):
        BankAccount.__init__(self);
        self.min_bal = min_bal;
        self.balance += min_bal;
        print("Minimum Balance Bank Account Created");
    
    # "withdraw" method overridden  
    # "withdraw" method overridden with different signature
    #  http://stackoverflow.com/questions/12764995/python-overriding-an-inherited-class-method
    def withdraw(self, amount):
        if self.balance - amount < self.min_bal:
            return "Cannot withdraw :: Minimum Balance is required";
        else:
            return BankAccount.withdraw(self, amount);

if __name__ == "__main__":
    
    a1 =  BankAccount();

    print("Amount after deposit : " + str(a1.deposit(1000)) );
    print("Amount after withdraw : " + str(a1.withdraw(100)) );
    
    a2 = MinimumBalanceAccount(500);

    print("Amount after deposit : " + str(a2.deposit(1000)) );
    print("Amount after withdraw : " + str(a2.withdraw(1200)) ); 
    print("Amount after withdraw : " + str(a2.withdraw(800)) );

    a3 = MinimumBalanceAccount(500);
    a3.withdraw(10);

