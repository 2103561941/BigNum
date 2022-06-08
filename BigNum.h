#pragma once
#include <deque>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#define ACCURACY 100

using namespace std;

class DividedByZeroException{
public:
    void error(){std::cout<<"Divided By Zero Exception!"<< std::endl;}
};

class BigNum{
private:
	std::vector<char> integer;
	std::vector<char> decimal;
	void trim();
	bool tag; 
	void setBigNumByStr(const string&);
public:
	// ctor
	BigNum();
	// BigNum(int);
	// BigNum(unsigned int);
	// BigNum(long long);    // construct with a long long
	// BigNum(float);
	// BigNum(double);
	
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
	

	// TODO: 移动语义

	// basic function
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
	static const BigNum ZERO;
	static const BigNum ONE;
	static const BigNum TEN;
};
