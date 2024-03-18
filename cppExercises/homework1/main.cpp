#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;
class Product {
public:

    string name;
    float price;

    Product() {}
    Product(string n, float m) : name(std::move(n)), price(m){}
};

class Customer{

    string customer_name;
    float credit_card_limit;
    Product list_of_ordered_products[5];
    int count_of_ordered_products;

public:

    Customer(string cname) : customer_name(std::move(cname)) {
        credit_card_limit = 1000;
        count_of_ordered_products = 0;
    }

    Customer(string cname, float cclimit) : customer_name(std::move(cname)), credit_card_limit(cclimit) {
        count_of_ordered_products = 0;
    }

    float calculate_total_debt() {
        float sum = 0;
        for(int i = 0; i < count_of_ordered_products; i++) {
            sum += list_of_ordered_products[i].price;
        }
        return sum;
    }

    void print() {
        cout << "Customer Name: " << customer_name << endl;
        cout << "Credit Card Limit: " << credit_card_limit << endl;
        cout << "List Of Ordered Products:" << endl;
        for(int i = 0; i < count_of_ordered_products; i++) {
            cout << "Product " << i+1 << ":" << endl;
            cout << "Name: " << list_of_ordered_products[i].name << "\tProduct Price: " << list_of_ordered_products[i].price << endl;
        }
        cout << "Count of Ordered Products: " << count_of_ordered_products << endl;
        cout << "Total Debt: " << calculate_total_debt() << endl;;
    }

    void operator+(Product P) {

        float debt = calculate_total_debt();
        cout << "Add Product: " << P.name << endl;

        if((debt + P.price) > credit_card_limit) {
            cout << "Customer does not have enough credit card limit to order this product" << endl;
        }

        else if(count_of_ordered_products == 5) {
            cout << "Customer already reached the maximum order count" << endl;
        }

        else {
            list_of_ordered_products[count_of_ordered_products] = P;
            count_of_ordered_products += 1;
            cout << "Product is added to customer succesfully" << endl;
        }
    }
};

int main() {
    cout << "PROGRAM STARTED\n" << endl;

    Customer c1("JOHN FISCHER", 2000);
    Customer c2("RONALD CRAIG");
    Customer c3("THOMAS AUSTIN", 750);

    c1+Product("Panasonic Phone", 800);
    c1+Product("Toshiba Battery", 300);
    c1+Product("Kenwood DVD", 400);
    c1.print();
    cout << "\n" << endl;

    c2+Product("Canon Battery", 500);
    c2+Product("Nikon Accessory", 600);
    c2+Product("Yamaha Subwoofer", 200);
    c2.print();
    cout << "\n" << endl;

    c3+Product("Whirlpool Charger", 90);
    c3+Product("Logitech Remote", 20);
    c3+Product("LG Dryer", 100);
    c3+Product("Linksys Router", 60);
    c3+Product("Nintendo Portable", 150);
    c3+Product("Mitsubishi Stand", 50);
    c3.print();
    cout << "PROGRAM FINISHED" << endl;
}
