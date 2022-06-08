#include <iostream>
using namespace std;
class Animals {
public:
    Animals(){ cout << "Animals cons" << endl; }
    ~Animals(){ cout << "Animals des" << endl; }
    virtual void eat() const { cout << "I like eating everything!" << endl; }
};
class Carnivore: public Animals {
public:
    Carnivore(){ cout << "Carnivore cons" << endl;}
    ~Carnivore(){ cout << "Carnivore des" << endl; }
    void eat() const{ cout << "I like eating meat!" << endl; }
};
class Herbivore : public Animals {
public:
    Herbivore(){ cout << "Herbivore cons" << endl; }
    ~Herbivore(){ cout << "Herbivore des" << endl; }
    void eat() const{ cout << "I like eating grass!" << endl; }
};
int main(){
    Animals* ptr = new Carnivore;
    ptr->eat();
    delete ptr;
    return 0;
}