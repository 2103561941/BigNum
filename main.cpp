#include <iostream>
#include "BigNum.h"
using namespace std;

// 测试基本计算
void test_calculate(BigNum& A, BigNum& B) {
    cout << A + B << endl;
    cout << A - B << endl;
    cout << A * B << endl;
    try{
        cout << A / B << endl;
    } catch(DividedByZeroException d) {
        cout << "div = 0" << endl; 
    }
    cout << A.pow(2) << endl;
    cout << A.pow(0.5) << endl;
    cout << (-A) << endl;
    cout << (-A).abs() << endl;
}

// 测试大小比较
void test_compare(BigNum& A, BigNum& B) {
    cout << "A: " << A << endl;
    cout << "B: " << B << endl;


    cout << (A < B) << endl;
    cout << (A == B) << endl;
    cout << (A <= B) << endl;
    cout << (A >= B) << endl;
    cout << (A != B) << endl;
}


// 测试输入输出， 赋值构造
// 
void test_ctor() {
    BigNum B("1230");
    BigNum A(10);
    A = 20;
    cout << A << endl;
    A = -10.01;
    cout << A << endl;
    A = "100000000";
    cout << A << endl;
}


int main() {
    BigNum a(1000);
    cout << a.pow(1) << endl;
    cout << a.pow(-1) << endl;
    cout << BigNum(120) / BigNum(120) << endl;
    return 0;
}



/* 问题累计
2. 除法小数有点问题                                     

*/
