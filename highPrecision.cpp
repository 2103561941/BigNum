#include "highPrecision.h"

// 构造函数------------------------------------------------------------------------------------------------------------------


// 创建一个空的高精度数字，不提供参数默认为0， 这里预设了vector的大小比long long类型大
Num::Num() : sign(1), num(std::vector<int>(20)) { }


// 读取字符串提供的数字，判断符号，反向保存到vector数组中
//如果输入的字符串除符号外参杂其他非数字的字符，抛出异常
Num::Num(const std::string& str) {
    int len = str.size();
    this->num = std::vector<int>(len);
    
    int i = 0;
    if (str[0] == '-') { this->sign = -1; i++; }
    else if (str[0] == '+') { this->sign = 1; i++; } 
    else this->sign = 1;
	
    for( i ; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') throw -1;
        this->num[len - i] = str[i] - '0'; 
    }
}

// 拷贝构造函数
Num::Num(const Num& num) {
    this->num = num.num;
    this->sign = num.sign;
}

//IO操作 ----------------------------------------------------------------------------------------------------------------------------

// num 转化成string类型
std::string Num::convstr() const {
    std::string ans = "";
    if (sign == -1) ans += '-';
    int len = this->num.size();
    for (int i = len - 1; i >= 0; i--) {
        ans += this->num[i] + '0';
    }

    return ans;
}


std::ostream& operator << (std::ostream& os, const Num& num) {
    std::string str = num.convstr();
    os << str;  
    return os;
}



// 计算------------------------------------------------------------------------------------------------------------------------


