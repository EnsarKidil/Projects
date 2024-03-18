#include <algorithm>
#include <iostream>

class Clock {
    int hour;
    int minute;

public:

    Clock() {
        hour = 0;
        minute = 0;
    }

    Clock(int hour, int minute): hour(hour), minute(minute){}

    Clock operator+(int add) {
        increment_time(add);
        return *this;
    }

    Clock operator+=(int add) {
        increment_time(add);
        return *this;
    }

    Clock operator++(int) {
        increment_time(1);
        return *this;
    }

    void print() {
        std::cout << "" << hour << ":" << minute << std::endl;
    }

    void increment_time(int add) {
        int hours_to_be_added = add / 60;
        int minutes_to_be_added = add % 60;
        int new_hour = hour + hours_to_be_added;
        int new_minute = minute + minutes_to_be_added;

        while(new_hour >= 24 || new_minute>=60) {
            if(new_minute >= 60) {
                new_minute = new_minute - 60;
                new_hour++;
            }

            if(new_hour>=24) {
                new_hour = new_hour - 24;
            }

        }
        hour = new_hour;
        minute = new_minute;
    }
};

int main() {
    Clock t1(23,50);
    t1+15;
    t1+=20;
    t1.print();
    Clock t2 = t1+10;
    t2++;
    t2.print();
}
