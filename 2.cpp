#include <iostream>
using namespace std;
class A{
public:
    A(){cout << "As cons." << endl;}
    virtual ~A(){cout << "As des." << endl;}
    virtual void f(){cout << "As f()." << endl;}
    void g(){f();}
};
class B :public A{
public:
    B(){f(); cout << "Bs cons." << endl; }
    ~B(){cout << "Bs des." << endl;}
};
class C :public B{
public:
    C(){cout << "Cs cons." << endl;}
    ~C(){cout << "Cs des." << endl;}
    void f(){cout << "Cs f()." << endl;}
};
int main(){
    A* a = new C;
    a->g();
    delete a;
    return 0;
}