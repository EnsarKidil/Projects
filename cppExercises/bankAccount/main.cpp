#include <iostream>
using namespace std;

class Account {

    string name;
    float value;

public:

    Account(string cust_name) : name(std::move(cust_name)), value(0){}
    Account(string cust_name, float init_value) : name(std::move(cust_name)), value(init_value){}

    void Deposit(float amount) {
        value += amount;
    }

    bool Withdraw(float amount) {

        if(value - amount >= 0) {
            value -= amount;
            return true;
        }

        return false;
    }

    bool Withdraw(float amount, float feeRate) {

        amount += feeRate*amount/100;
        return Withdraw(amount);

    }

    bool Transfer(Account &target, float amount) {

        if(&target == this) {
            cout << "It is impossible to transfer to the same account." << endl;
            return false;
        }

        bool flag = Withdraw(amount, 1);

        if(flag) {
            target.Deposit(amount);
            return true;
        }

        return false;
    }

    void Print() {
        cout << "Name: " << name << " Value: " << value << endl;
    }
};

int main() {
    Account M1("AAA", 1000);
    M1.Withdraw(500, 2);
    Account M2("BBB");
    M1.Transfer(M2, 300);
    M2.Withdraw(200);
    M2.Deposit(400);
    M2.Transfer(M1, 100);
    M1.Transfer(M1, 70);
    M1.Print();
    M2.Print();
}
