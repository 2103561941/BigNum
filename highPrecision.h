#pragma once
#include <vector>
#include <string>
#include <iostream>

class Num {
private:
    int sign;
    std::vector<int> num;

public:
    Num();
    Num(const std::string& str);
    Num(const Num& num);

public:
    std::string convstr() const;
    friend std::ostream& operator << (std::ostream& os, const Num& num);
};



