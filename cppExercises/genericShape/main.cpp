#include <iostream>
#include <cmath>
using namespace std;

float pow(int number, int degree) {

    if(degree == 0) {
        return 1;
    }

    if(degree == 1) {
        return number * 1;
    }

    number *= number;
    return pow(number, degree-1);
}

class GenericShape {

public:

    float density;

    GenericShape(float density) : density(density){}

    float virtual volume() {
        return 0;
    }

    float weight() {
        return density * volume();
    }
};

class Prism : public GenericShape{

public:

    int a, b, c;

    Prism(float density, int a, int b, int c) : GenericShape(density), a(a), b(b), c(c){}

    float volume() override {
        return a*b*c;
    }
};

class Sphere : public GenericShape {

public:

    int r;

    Sphere(float density, int r) : GenericShape(density), r(r){}

    float volume() override {
        return 4.0/3.0 * 3.14 * pow(r, 3);
    }
};

class Cylinder : public GenericShape {

public:

    int r, h;

    Cylinder(float density, int r, int h) : GenericShape(density), r(r), h(h){}

    float volume() override {
        return 3.14 * pow(r, 2) * h;
    }
};

class Cone : public Cylinder {

public:

    Cone(float density, int r, int h) : Cylinder(density, r, h){}

    float volume() override {
        return 1.0/3.0 * 3.14 * pow(r, 2) * h;
    }
};


int main() {
    GenericShape *arr[10];
    arr[0] = new Prism(2, 6, 8, 5);
    arr[1] = new Prism(3, 5, 4, 9);
    arr[2] = new Sphere(1, 3);
    arr[3] = new Cylinder(1, 4, 8);
    arr[4] = new Cylinder(4, 2, 9);
    arr[5] = new Cone(3, 5, 7);
    arr[6] = new Prism(1, 7, 2, 1);
    arr[7] = new Sphere(2, 7);
    arr[8] = new Cylinder(1, 4, 6);
    arr[9] = new Cone(1, 5, 3);

    for(int i = 0; i < 10; i++) {
        cout << arr[i]->weight() << endl;
    }
}
