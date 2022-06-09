#pragma once
#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#define ACCURACY 5

using namespace std;

// 异常类，在除数为0时返回
class DividedByZeroException{
public:
    void error(){std::cout<<"Divided By Zero Exception!"<< std::endl;}
};

// 高精度实数类

/* 基本参数
实现思路：
将整数部分和小数部分分开存储，integer（整数），decimal（小数）
存储的时候使用vector动态数组存储char类型。
tag用来表示正数（true）和负数（false）



支持功能：
支持各种内置且合法的类型转化为大数 （如 int，long long，double， string，char等等）也包括他本身
同样支持内置且合法的类型给大数赋值 operator= 
支持+ - * / 四则运算，以及其延申出来的各种运算操作 +=， -=， *=， /=
支持大数之间所有大小比较操作符
提供abs（取绝对值），pow（幂次方）等math函数， pow函数目前支持传入正负整数
支持>>、<< 流操作进行输入输出。

关于除法设置有效小数位，我采用的是外部调用setBit() 来改变类里面的bit的值，从而改变除法有效位数，
默认有效位是5位, 
做除法的时候因为有除数为0，需要获取异常
*/

/*
优化过的地方：
TODO:
vector：提前设置cap大小，减少copy次数

*/

class BigNum{
private:
	std::vector<char> integer;
	std::vector<char> decimal;
	//剪枝，如将01100.000变成 1100.0， 使其美观，同时需要保证比较函数的正确，这个是重点。
	//剪枝就是将一个数可能表达的形式都转化为统一形式。
	void trim();
 	bool tag;
	void setBigNumByStr(const string&);
	static int bit;
public:
	// ctor
	BigNum();
	template<typename T>
	BigNum(const T& val) {
		const string str = std::to_string(val);
		setBigNumByStr(str);
	}


	BigNum(const std::string&);
	// 由于加上了template，对于常量的char* 需要下面这种方法
	BigNum(const char*);
	BigNum(const BigNum&);


	template<typename T>
	BigNum operator=(const T& op) {
		BigNum tmp(op);
		integer = tmp.integer;
		decimal = tmp.decimal;
		tag = tmp.tag;
		return *this;
	}

	BigNum operator=(const BigNum& op);
	

	//TODO: 移动语义


	//basic function
	static void setBits(int);
	BigNum      abs() const;
	BigNum      pow(int a) const;

	//binary operators
	friend BigNum operator+(const BigNum&,const BigNum&);
	friend BigNum operator-(const BigNum&,const BigNum&);
	friend BigNum operator*(const BigNum&,const BigNum&);
	friend BigNum operator/(const BigNum&,const BigNum&) noexcept(false);

	friend BigNum operator-(const BigNum&);   //negative

	friend bool operator==(const BigNum&,const BigNum&);
	friend bool operator!=(const BigNum&,const BigNum&);
	friend bool operator<(const BigNum&,const BigNum&);
	friend bool operator<=(const BigNum&,const BigNum&);
	friend bool operator>(const BigNum&,const BigNum&);
	friend bool operator>=(const BigNum&,const BigNum&);

	friend BigNum operator+=(BigNum&,const BigNum&);
	friend BigNum operator-=(BigNum&,const BigNum&);
	friend BigNum operator*=(BigNum&,const BigNum&);
	friend BigNum operator/=(BigNum&,const BigNum&) noexcept(false);

	string to_string() const;
	friend ostream& operator<<(ostream&,const BigNum&);    //print the BigInteger
	friend istream& operator>>(istream&, BigNum&);         // input the BigInteger

public:
	// 主要用于计算时判断当前值是否符合要求，如除数是否为0，类似宏定义
	static const BigNum ZERO;
	static const BigNum ONE;
	static const BigNum TEN;
 
};
