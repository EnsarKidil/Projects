#include <iostream>
#include <string>
#include <vector>


class Person {
public:
    std::string Name;
    int Age;

    Person() {
        Name = "";
        Age = 0;
    }

    Person(std::string name, int age) {
        Name = name;
        Age = age;
    }
};


template <typename Member>
class Array {
public:
    std::pmr::vector<Member> Members;
    int Size;

    Array(int const& size) {
        Size = size;
        Members.resize(Size);
    }

     Member& operator[](int index) {
        return Members.at(index);
    }

public:
    bool Find(Member member) {
        for(int i = 0; i < Size; i++) {
            if (Members[i] == member)
                return true;
        }
        return false;
    }

    Member Smallest() {
    }
};

int main() {
    Array<Person> persons(3);
    Person p1("Ensar", 30);
    persons[1] = p1;
    std::cout << persons[1].Name;
    Array<int> ArrI(3);
}
