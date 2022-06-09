#include "BigNum.h"

using namespace std;

BigNum operator-(const BigNum& op)
{
    BigNum temp(op);
    temp.tag = !temp.tag;
    return temp;
}

// 
void BigNum::trim() {
    vector<char>::reverse_iterator iter = integer.rbegin();
    while(!integer.empty() && (*iter) == 0){
        integer.pop_back();
        iter=integer.rbegin();
    }
    if( integer.size()==0 ) {
        // tag = true;
        integer.push_back(0);
    }
    vector<char>::const_iterator it = decimal.begin();
    while(!decimal.empty() && (*it) == 0){
        it = decimal.erase(it);
    }
    if( decimal.size()==0 ) {
        // tag = true;
        decimal.push_back(0);
    }
}

int BigNum::bit = ACCURACY;

//delete those 0 in the front
const BigNum BigNum::ZERO=BigNum(0);
const BigNum BigNum::ONE =BigNum(1);
const BigNum BigNum::TEN =BigNum(10);

BigNum::BigNum() 
    : tag(true), integer(vector<char>(1,0)), decimal(vector<char>(1,0)) {
        integer.reserve(10);
        decimal.reserve(10);
    }


// private成员函数，主要用于提供给其他成员函数使用。
void BigNum::setBigNumByStr(const string& val) {
    integer.reserve(10);
    decimal.reserve(10);
    // 设置精度位 
    bool type = true;
    tag = true;
    for(auto iter = val.rbegin() ; iter < val.rend();  iter++)
    {
        char ch = (*iter);
        if(ch == '.'){
            type = false;
            iter++;
        }
        if (iter == val.rend()-1){
            if (ch == '+' )
                break;
            if(ch == '-' ){
                tag = false;
                break;
            }
        }
        // Use the reverse iterator of string here to process the entire data from back to front. 
        if(type)decimal.push_back( (char)((*iter) - '0' ) );
        else integer.push_back( (char)((*iter) - '0' ) );
    }
    
    // 用户可能的输入情况（不考虑正负）:
    // 100.0  正常情况
    // 100    无小数部分， 但是实际存储的时候会把整数的100存到小数里去，整数数组为0，需要push0，并且和小数部分交换
    // .100 100ac0 等等复杂的非人类的输入情况后果由用户来承担

    if (integer.size() == 0 && type == true) {
        integer.push_back(0);
        // 这种情况说明用户只输入了整数部分但没有小数部分。
        swap(integer, decimal);
    }

    // 剪枝
    trim();
}


BigNum::BigNum(const char* val) {
    const string str = val;
    setBigNumByStr(str);
}


// 这里考虑用户输入时可能会输入100 而不加. 所以需要特殊处理
BigNum::BigNum(const string& val){
    setBigNumByStr(val);
}

BigNum::BigNum(const BigNum &op) {
    integer = op.integer;
    decimal = op.decimal;
    tag = op.tag;
}



BigNum BigNum::operator=(const BigNum& op) {
    integer = op.integer;
    decimal = op.decimal;
    tag = op.tag;
    return (*this);
}

void BigNum::setBits(int b) {
    if (b > 0) {
        bit = b;
    }
}

BigNum BigNum::abs() const  {
    if(tag)  return (*this);
    else      return -(*this);
}

// 考虑负数的情况（这里就不考虑小数的情况了）
BigNum BigNum::pow(int a) const {
    bool tg; 
    if (a < 0) {
        tg = false;
        a = -a;
    } else if (a == 0) {
        return BigNum(1);
    } else {
        tg = true;
    }
    
    BigNum res(1);
    for(int i=0; i<a; i++)
        res*=(*this);

    // 指数为负数，取倒数
    if (tg == false) {
        return (BigNum(1)/res);
    }
    return res;
}


// 这里原本存储的时候整数部分和小数部分是分开存储并且倒序的，
// 所以转化为字符串需要同样reserver操作
string BigNum::to_string() const {
    string num = "";
    if (!tag)
        num += "-"; 

    for ( vector<char>::const_reverse_iterator iter = integer.rbegin(); iter != integer.rend() ; iter++)
        num += (char)((*iter) + '0'); 

    num += ".";

    for ( vector<char>::const_reverse_iterator iter = decimal.rbegin(); iter != decimal.rend() ; iter++)
        num += (char)((*iter) + '0');
    return num;
}


ostream& operator<<(ostream& stream,const BigNum& val){    //print the BigInteger
    string str = val.to_string();
    stream << str;
    return stream;
}

istream& operator>>(istream& stream, BigNum& val){    //Input the BigInteger
    string str;
    stream >> str;
    val=BigNum(str);
    return stream;
}

BigNum operator+=(BigNum& op1,const BigNum& op2){
    if( op1.tag == op2.tag ) {     //只处理相同的符号的情况，异号的情况给-处理
        vector<char>::iterator iter1;
        vector<char>::const_iterator iter2,it;
//处理小数部分
    //比较两个数的小数位，从小数位少的一方开始计算。
        int op1_len = op1.decimal.size();
        int op2_len = op2.decimal.size();
        char to_add = 0;     //进位

        if(op1_len<op2_len){
            iter1 = op1.decimal.begin();
            iter2 = op2.decimal.begin();
            iter2 = iter2 - (op1_len - op2_len);
                
        while ( iter1 != op1.decimal.end() && iter2 != op2.decimal.end()){
            (*iter1) = (*iter1) + (*iter2) + to_add;
            to_add = ((*iter1) > 9);    // 大于9进一位
            (*iter1) = (*iter1) % 10;
            iter1++; iter2++;
        }
        // 将op2中多出来的小数位加到op1中
            it = op2.decimal.begin();
            iter2 = op2.decimal.end();
            iter2 = iter2 - op1_len -1;
            while(iter2 != it){
                op1.decimal.insert(op1.decimal.begin(),*iter2);
                iter2--;
            }
            op1.decimal.insert(op1.decimal.begin(),*iter2);
            iter1 = op1.decimal.begin();
        }
        else if(op1_len > op2_len){
            iter1 = op1.decimal.begin();
            iter1 = iter1+(op1_len-op2_len);
            iter2 = op2.decimal.begin();
            while ( iter1 != op1.decimal.end() && iter2 != op2.decimal.end()){
                (*iter1) = (*iter1) + (*iter2) + to_add;
                to_add = ((*iter1) > 9);    // 大于9进一位
                (*iter1) = (*iter1) % 10;
                iter1++; iter2++;
            }
        }
        else {
            iter1 = op1.decimal.begin();
            iter2 = op2.decimal.begin();
            while ( iter1 != op1.decimal.end() && iter2 != op2.decimal.end()){
                (*iter1) = (*iter1) + (*iter2) + to_add;
                to_add = ((*iter1) > 9);    // 大于9进一位
                (*iter1) = (*iter1) % 10;
                iter1++; iter2++;
            }
        }
        
//处理整数部分
        iter1 = op1.integer.begin();
        iter2 = op2.integer.begin();
        //进位
        while ( iter1 != op1.integer.end() && iter2 != op2.integer.end()){
            (*iter1) = (*iter1) + (*iter2) + to_add;
            to_add = ((*iter1) > 9);    // 大于9进一位
            (*iter1) = (*iter1) % 10;
            iter1++; iter2++;
        }
        
        while ( iter1 != op1.integer.end() ){   
            (*iter1) = (*iter1) + to_add;
            to_add = ( (*iter1) > 9 );
            (*iter1) %= 10;
            iter1++;
        }
        while ( iter2 != op2.integer.end() ){
            char val = (*iter2) + to_add;
            to_add = (val > 9) ;
            val %= 10;
            op1.integer.push_back(val);
            iter2++;
        }
        if( to_add != 0 )
            op1.integer.push_back(to_add);
        return op1;
    }
    else{
        if (op1.tag)
            return op1 -= (-op2);
        else
            return op1= op2 - (-op1);
    }
}


BigNum operator-=(BigNum& op1,const BigNum& op2){
    if( op1.tag == op2.tag ) {     //只处理相同的符号的情况，同号的情况给+处理
        if(op1.tag)  {             
            if(op1 < op2)  // 2 - 3
            {
                BigNum op(op2 - op1);
                op1 = -op;
                return op1;//
            }
        } 
        else {
            if(-op1 > -op2)  // (-3)-(-2) = -(3 - 2)
                return op1=-((-op1)-(-op2));
            else             // (-2)-(-3) = 3 - 2 
                return op1= (-op2) - (-op1);
        }
//小数部分 
        char to_substract = 0;  //借位
        int a = op1.decimal.size();
        int b = op2.decimal.size();
        vector<char>::iterator it1 = op1.decimal.begin();
        vector<char>::const_iterator it2 = op2.decimal.begin();
        if(a>b){
            a -= b;
            it1 = it1 + a;
        }
        else{
            int number = b-a;
            while(number!=0)
            {
                op1.decimal.insert(op1.decimal.begin(),'0');//should be insert into the head of the vector
                number--;
            }
        }
        while ( it1 != op1.decimal.end() && it2 != op2.decimal.end()) {
                (*it1) = (*it1) - (*it2) - to_substract;
                to_substract = 0;
                if( (*it1) < 0 ) {
                    to_substract=1;
                    (*it1) += 10;
                }
                it1++;
                it2++;
            }
//整数部分
        vector<char>::iterator iter1;
        vector<char>::const_iterator iter2;
        iter1 = op1.integer.begin();
        iter2 = op2.integer.begin();

        while ( iter1 != op1.integer.end() && iter2 != op2.integer.end()) {
            (*iter1) = (*iter1) - (*iter2) - to_substract;
            to_substract = 0;
            if( (*iter1) < 0 ) {
                to_substract=1;
                (*iter1) += 10;
            }
            iter1++;
            iter2++;
        }
        while ( iter1 != op1.integer.end() ) {
            (*iter1) = (*iter1) - to_substract;
            to_substract = 0;
            if( (*iter1) < 0 ) {
                to_substract=1;
                (*iter1) += 10;
            }
            else break;
            iter1++;
        }
        op1.trim();
        return op1;
    }//符号相同
    else {
        if (op1 > BigNum::ZERO)
            return op1 += (-op2);
        else
            return op1 = -(op2 + (-op1));
    }
}

BigNum operator*=(BigNum& op1,const BigNum& op2) {
    BigNum result(0);
    if (op1 == BigNum::ZERO || op2==BigNum::ZERO)
        result = BigNum::ZERO;
    else{
        int size = 0;
        vector<char> op_temp1(op1.integer.begin(), op1.integer.end());
        if(op1.decimal.size()!=1||(op1.decimal.size()==1&&(*op1.decimal.begin())!=0)){
            op_temp1.insert(op_temp1.begin(),op1.decimal.begin(), op1.decimal.end());
            size += op1.decimal.size();
        }
        vector<char> op_temp2(op2.integer.begin(), op2.integer.end());
        if(op2.decimal.size()!=1||(op2.decimal.size()==1&&(*op2.decimal.begin())!=0)){
            op_temp2.insert(op_temp2.begin(),op2.decimal.begin(), op2.decimal.end());
            size += op2.decimal.size();
        }
        vector<char>::const_iterator iter2 = op_temp2.begin();
        while( iter2 != op_temp2.end() ){
            if(*iter2 != 0){
                deque<char> temp(op_temp1.begin() , op_temp1.end());
                char to_add = 0;
                deque<char>::iterator iter1 = temp.begin();
                while( iter1 != temp.end() ){
                    (*iter1) *= (*iter2);
                    (*iter1) += to_add;
                    to_add = (*iter1) / 10;
                    (*iter1) %= 10;
                    iter1++;
                }//while
                if( to_add != 0)
                    temp.push_back( to_add );
                int num_of_zeros = iter2 - op_temp2.begin();
                while(  num_of_zeros--)
                    temp.push_front(0);
                BigNum temp2;
                temp2.integer.clear();
                temp2.integer.insert( temp2.integer.end() , temp.begin() , temp.end() );
                temp2.trim();
                result = result + temp2;
                //
            }//if
            iter2++;
        }//while
        result.tag = ( (op1.tag && op2.tag) || (!op1.tag && !op2.tag) );
        if(size!=0){
            result.decimal.clear();
            result.decimal.insert(result.decimal.begin(), result.integer.begin(), result.integer.begin()+size);
            result.integer.erase(result.integer.begin(), result.integer.begin()+size);
        }
    }//else
    op1 = result;
    return op1;
}

BigNum operator/=(BigNum& op1, const BigNum& op2) {
    if (op2 == BigNum::ZERO)
        throw DividedByZeroException();
    if (op1 == BigNum::ZERO)
        return op1;
    BigNum op_temp2 = op2;
    BigNum op_temp1 = op1;
    int Integer_Size = 0; // 表示10的几次方
    if ((op_temp2.decimal.size() == 1) && (*(op_temp2.decimal.begin()) == 0)) {}
    else {
        //Integer_Size -= op_temp2.decimal.size();
        int t = op_temp2.decimal.size();
        while (t--) {
            op_temp1 = op_temp1 * BigNum::TEN;
            op_temp2 = op_temp2 * BigNum::TEN;
        }
    }

    while (op_temp1 >= op_temp2) {
        op_temp1.decimal.push_back(*op_temp1.integer.begin());
        op_temp1.integer.erase(op_temp1.integer.begin());
        Integer_Size++;
    }
    
    op_temp1 *= BigNum::TEN;
    int k = op1.bit + 1;
    string str = "0.";
    while (k--) {
        if (op_temp1 == BigNum::ZERO) {
            break;
        }
        if (op_temp1 < op_temp2) {
            str += '0';
        }
        else {
            int i;
            BigNum compare;
            for (i = 1; i < 10; i++) {
                BigNum BF(i);
                compare = op_temp2 * BF;
                if (compare > op_temp1)
                    break;
            }
            compare -= op_temp2;
            op_temp1 -= compare;
            str += i - 1 + '0';
        }
        op_temp1 = op_temp1 * BigNum::TEN;
    }

    BigNum re(str);

    while (Integer_Size--) {
        re = re * BigNum::TEN;
    }

    // 符号位判断，剪枝
    op1 = re;
    op1.trim();
    op1.tag = ((op1.tag && op2.tag) || (!op1.tag && !op2.tag));

    


    return op1;
}


BigNum operator+(const BigNum& op1,const BigNum& op2){
    BigNum temp(op1);
    temp += op2;
    return temp;
}
BigNum operator-(const BigNum& op1,const BigNum& op2){
    BigNum temp(op1);
    temp -= op2;
    return temp;
}
BigNum operator*(const BigNum& op1,const BigNum& op2){
    BigNum temp(op1);
    temp *= op2;
    return temp;
}
BigNum operator/(const BigNum& op1,const BigNum& op2){
    BigNum temp(op1);
    temp /= op2;
    return temp;
}
bool operator<(const BigNum& op1,const BigNum& op2){
    bool sign;
    if( op1.tag != op2.tag ){
        sign =  !op1.tag;    
        return sign;
    }
    else{
        if(op1.integer.size() != op2.integer.size()){
            if(op1.tag){
                sign = op1.integer.size()<op2.integer.size();            
                return sign;
            }
            else {
                sign = op1.integer.size()>op2.integer.size();
                return sign;
            }
        } 
        vector<char>::const_reverse_iterator iter1,iter2;
        iter1 = op1.integer.rbegin();
        iter2 = op2.integer.rbegin();
        while( iter1 != op1.integer.rend() ){
            if(  op1.tag &&  *iter1 < *iter2 ) return true;
            if(  op1.tag &&  *iter1 > *iter2 ) return false;
            if( !op1.tag &&  *iter1 > *iter2 ) return true;
            if( !op1.tag &&  *iter1 < *iter2 ) return false;
            iter1++;
            iter2++;
        }
        vector<char>::const_reverse_iterator it1,it2;
        it1 = op1.decimal.rbegin();
        it2 = op2.decimal.rbegin();
        while( it1 != op1.decimal.rend() && it2 != op2.decimal.rend()){
            //cout<<((*it1)+'0')<<((*it1)+'0')<<endl;
            if(  op1.tag &&  *it1 < *it2 ) return true;
            if(  op1.tag &&  *it1 > *it2 ) return false;
            if( !op1.tag &&  *it1 > *it2 ) return true;
            if( !op1.tag &&  *it1 < *it2 ) return false;
            it1++;
            it2++;
        }
        return (op1.tag && it2!=op2.decimal.rend())
            || (!op1.tag && it1!=op1.decimal.rend());
    }
}
bool operator>(const BigNum& op1,const BigNum& op2){
    bool tag = !(op1<=op2);
    return tag;
}

bool operator==(const BigNum& op1, const BigNum& op2){
    if(op1.tag != op2.tag){
        return false;
    }

    if(op1.integer.size() != op2.integer.size() ){
        return false;
    }
    if( op1.decimal.size() != op2.decimal.size() ){
        return false;
    }
    vector<char>::const_iterator iter1,iter2;
    iter1 = op1.decimal.begin();
    iter2 = op2.decimal.begin();
    while( iter1!= op1.decimal.end() ){
        if( *iter1 != *iter2 )  return false;
        iter1++;
        iter2++;
    }
    iter1 = op1.integer.begin();
    iter2 = op2.integer.begin();
    while( iter1!= op1.integer.end() ){
        if( *iter1 != *iter2 )  return false;
        iter1++;
        iter2++;
    }
    return true;
}

bool operator!=(const BigNum& op1,const BigNum& op2){
    return !(op1==op2);
}
bool operator>=(const BigNum& op1,const BigNum& op2){
    bool tag = (op1>op2) || (op1==op2);   
    return tag;
}

bool operator<=(const BigNum& op1,const BigNum& op2){
    bool tag = (op1<op2) || (op1==op2);
    return tag;
}