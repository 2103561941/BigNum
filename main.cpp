#include <iostream>
#include <algorithm>
#include "BigNum.h"
using namespace std;


void ctor();
void assign();
void calculate(const BigNum& , const BigNum& );  //  二元操作符
void calculate_Monocular(BigNum& a, const BigNum& b);
void compare(const BigNum& , const BigNum& );
void compare_const();
void basic_fun();
string transform(bool);
void test_ctor();
void test_compare();
void test_calculate();
void test_bits();

int main() {
    BigNum::setBits(10);
    test_ctor();
    cout << "=============================================================" << endl;
    test_compare();
    cout << "=============================================================" << endl;
    test_calculate();
    cout << "=============================================================" << endl;
    basic_fun();
    cout << "=============================================================" << endl;
    test_bits();


    return 0;
}


// 测试用例----------------------------------------------------------------
void test_bits() {
    BigNum::setBits(50);
    BigNum a(20);
    BigNum b(3);
    BigNum c = a / b;
    cout << "20 / 3 = " << c << endl;
    
}


void test_compare() {
    compare(BigNum("10000"), BigNum("10001"));
    cout << endl;
    compare(BigNum("123456789"), BigNum("-123456789"));
    cout << endl;
    compare(BigNum(765.4321), BigNum(765.4321));
    cout << endl;
    // 判断是否瘦身剪枝
    cout << "compare(BigNum(\"10.0000\"), BigNum(\"00010.0\"));" << endl;
    compare(BigNum("10.0000"), BigNum("00010.0"));
    cout << endl;

    compare_const();
    // 测试常值
}       

void test_calculate() {
    // 一般案例
    calculate("123456789", "123456789");
    cout << endl;
    calculate("0", "123");
    cout << endl;
    calculate("321", "0");
    cout << endl;
    calculate("213.5678", "123.987");
    cout << endl;

    // string随机数，随机测试
    // for (int i = 0; i < 3; i++) {
        
    // }

    BigNum a = 1000;
    calculate_Monocular(a, "1000");
    cout << endl;
    calculate_Monocular(a, "123.4");
}

void test_ctor() {
    ctor();
    assign();
}

// 测试单元---------------------------------------------------------------
// 测试用户可能的各种合法输入及构造函数
void ctor() {
    // 构造函数
    cout << "BigNum() : "  << BigNum() << endl;
    // 大整数,大负实数字符串
    BigNum a("1234567890987654321");
    cout << "a(\"1234567890987654321\") : " << a << endl; 
    BigNum b("-123456789.0987654321");
    cout << "b(\"-123456789.0987654321\") : " << b << endl;

    // 内置整数，浮点数类型  
    BigNum c(10.000);
    cout << "c(10.000) : " << c << endl; 
    BigNum d(-10);
    cout << "d(-10) : " << d << endl; 
    BigNum e((long long)12345678910);
    cout << "e((long long)12345678910) : " << e << endl;
    BigNum f((unsigned int)1234);
    cout << "f((unsigned int)1234) : " << f << endl;
    BigNum g((double)1234.5678910);
    cout << "g((double)1234.5678910) : " << g << endl;
    BigNum h(string("123.321"));
    cout << "h(string(\"123.321\")) : " << h << endl;

    // >> << 输入输出流操作， 输出流上面已经检测，主要检测输入流, 这里会中断整体打印，所以我注释了
    cout << "please input BigNum: " << endl;
    BigNum i;
    cin >> i;
    cout << "cin >> i, i = " <<  i << endl;


}

void assign() {
    BigNum a(312);
    a = -10;
    cout << "a = -10, a = " << a << endl;
    a = 10.123;
    cout << "a = -10.123, a = " << a << endl;
    a = "123321.123321";
    cout << "a = \"123321.123321\", a = " << a << endl;
}

void basic_fun() {
    BigNum a(-1000);
    cout << "abs(-1000)" << a.abs() << endl;

    BigNum b(25);
    cout << "b.pow(3)" << b.pow(3) << endl;
    cout << "b.pow(-1)" << b.pow(-1) << endl;
    cout << "b.pow(0)" << b.pow(0) << endl;

}


// 测试基本计算
void calculate(const BigNum& a, const BigNum& b) {
    cout << a << " + " << b << " = " << a + b << endl;
    cout << a << " - " << b << " = " << a - b << endl;
    cout << a << " * " << b << " = " << a * b << endl;
    // 除数为零要接收异常
    try{
        cout << a << " / " << b << " = " << a / b << endl;
    }catch(DividedByZeroException d) {
        d.error();
    }
}

// 单目操作符
void calculate_Monocular(BigNum& a, const BigNum& b) {
    cout << "a = " << a << endl;
    // 用c来保存a的原始值
    BigNum c = a;
    c += b;
    cout << "a += b " << c << endl;
    c = a;
    c -= b;
    cout << "a -= b " << c << endl;    
    c = a;
    c *= b;
    cout << "a *= b " << c << endl;
    c = a;
    try{
        c /= b;
        cout << "a /= b " << c << endl;
    } catch(DividedByZeroException d) {
        d.error();
    }
}

// 测试大小比较
void compare(const BigNum& a, const BigNum& b) {
    cout << a << " > " << b << " : " << transform(a > b) << endl;
    cout << a << " < " << b << " : " << transform(a < b) << endl;
    cout << a << " == " << b << " : " << transform(a == b) << endl;
    cout << a << " != " << b << " : " << transform(a != b) << endl;
    cout << a << " >= " << b << " : " << transform(a >= b) << endl;
    cout << a << " <= " << b << " : " << transform(a <= b) << endl;
}


// 与内置类型进行比较
void compare_const() {
    cout << "compare with built-in type" << endl; 
    BigNum a(123);
    int b = 10;
    cout << a << " > " << b << " : " << transform(a > b) << endl;
    cout << a << " > " << b << " : " << transform(a > b) << endl;
    cout << a << " < " << b << " : " << transform(a < b) << endl;
    cout << a << " == " << b << " : " << transform(a == b) << endl;
    cout << a << " != " << b << " : " << transform(a != b) << endl;
    cout << a << " >= " << b << " : " << transform(a >= b) << endl;
    cout << a << " <= " << b << " : " << transform(a <= b) << endl;
}


// bool 在输出时转化为string 方便观察
string transform(bool b) {
    if (b) return "true";
    else return "false";
}

