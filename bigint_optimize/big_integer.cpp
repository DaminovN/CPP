//#include<bits/stdc++.h>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include "big_integer.h"
using namespace std;


__extension__ typedef __int128 int128_t;

const long long int BASE = (1ll << 31ll);
const int NEEDBIT = (int) (BASE - 1ll);
const long long int MOD = (1ll << 31ll);
const int BASEPOW = 31;
// const long long int BASE = 10;
// const int NEEDBIT = 9;
// const long long int MOD = 10ll;
// const int BASEPOW = 31;
int nothing;

big_integer::big_integer() : v(1, 0), sign(1) {}

big_integer::big_integer(big_integer const& value) : v(value.v), sign(value.sign) {}

big_integer::big_integer(big_integer const& value, int sign): v(value.v), sign(sign) {}

big_integer::big_integer(int val)
{
    if (val >= 0)
        sign = 1;
    else
        sign = -1;
    long long int value = abs((long long) val);
    v.clear();
    if (value == 0)
        v.push_back(0);
    while (value > 0)
    {
        v.push_back((value) % BASE);
        value /= BASE;
    }
}
big_integer::big_integer(const myVec& val, int sgn) : sign(sgn)
{
    v = val;
}
void normalize(myVec &val)
{
    if (val.empty())
    {
        val.push_back(0);
    }
    while (val.size() != 1 && val.back() == 0)
    {
        val.pop_back();
    }
}
void shortDivMod(long long int dividendBase, long long int const& divider, const myVec a, myVec& res, int& mod)
{
    long long int cur = 0;
    res.resize(a.size(), 0);
    for (int i = a.size() - 1; i >= 0; --i)
    {
        cur = cur * dividendBase + a[i];
        res[i] = cur / divider;
        cur %= divider;
    }
    mod = (int) cur;
    normalize(res);
}
big_integer::big_integer(string const& value)
{
    v.clear();
    sign = 1;
    int end = 0;
    if (value[0] == '-')
        sign = -1, end = 1;
    myVec temp;
    for (int i = (int) value.size() - 1; i >= end; --i)
    {
        temp.push_back((int)(value[i] - '0'));
    }
    int mod = 0;
    while(temp.size() != 1 || temp[0] != 0)
    {
        shortDivMod(10ll, (long long int) BASE, temp, temp, mod);
        v.push_back(mod);
    }
    normalize(v);
    if (v.size() == 1 && v[0] == 0)
        sign = 1;
}
big_integer::~big_integer() {}


big_integer big_integer::operator+() const
{
    return *this;
}
big_integer ZERO(0);
big_integer ONE(1);
big_integer big_integer::operator-() const
{
    return (*this != ZERO) ? big_integer(*this, -sign) : ZERO;
}


big_integer big_integer::operator~() const
{
    return (-(*this) - ONE);
}

big_integer inverse(big_integer const& val)
{
    big_integer rhs(val);
    for (size_t i = 0; i < rhs.size(); ++i)
    {
        rhs[i] = ~(rhs[i]);
    }
    return rhs;
}

myVec to_byte(myVec v, int sign)
{
    if (sign < 0)
    {
        v = ((inverse(big_integer(v, 1))) + ONE).v;
    }
    v.push_back((sign >= 0) ? 0 : NEEDBIT);
    return v;
}
big_integer from_byte(myVec v)
{
    int sign = 1;
    if (v.back() == NEEDBIT)
        sign = -1;
    v.pop_back();
    big_integer res((sign == -1) ? big_integer((inverse(big_integer(v, 1))) + ONE, -1) : big_integer(v, 1));
    if (res.size() == 1 && res[0] == 0)
        res.sign = 1;
    return res;

}

enum operation { XOR, OR, AND };

big_integer byteFunctionBigInteger(const myVec& a, const myVec& b, operation op)
{
    myVec res(max(a.size(), b.size()));
    for(int i = 0; i < (int)res.size(); i++)
    {
        if (op == AND)
            res[i] = a[min((int)a.size() - 1, i)] & b[min((int)b.size() - 1, i)];
        else if (op == OR)
            res[i] = a[min((int)a.size() - 1, i)] | b[min((int)b.size() - 1, i)];
        else
            res[i] = a[min((int)a.size() - 1, i)] ^ b[min((int)b.size() - 1, i)];
    }
    return from_byte(res);
}
big_integer leftShift(const myVec& a, int shift)
{
    myVec res(shift / BASEPOW, 0);
    long long int cur = 0;
    int last = a.back();
    shift %= BASEPOW;
    for (size_t i = 0; i < a.size(); ++i)
    {
        cur += ((long long int) a[i]) << shift;
        res.push_back(cur & NEEDBIT);
        cur >>= BASEPOW;
    }
    res.push_back(last);
    while (res.size() > 1 && res.back() == res[res.size() - 2])
        res.pop_back();
    return from_byte(res);
}
big_integer rightShift(const myVec& a, int shift)
{
    myVec res;
    int last = a.back();
    int i = shift / BASEPOW;
    shift %= BASEPOW;
    long long int cur = a[i] >> shift;
    while(i + 2 < (int)a.size())
    {
        cur = cur + (((long long int) a[i + 1]) << (BASEPOW - shift));
        res.push_back(cur & (long long int) NEEDBIT);
        cur >>= BASEPOW;
        i++;
    }
    if (cur)
        res.push_back(cur);
    res.push_back(last);
    while (res.size() > 1 && res.back() == res[res.size() - 2])
        res.pop_back();
    return from_byte(res);
}
void print(big_integer value)
{
    if (value.sign == -1)
        printf("-");
    int mod = 0;
    string res = "";
    while (value.size() != 1 || value[0] != 0)
    {
        shortDivMod(BASE, 10, value.v, value.v, mod);
        res += (char) (mod + 48);
    }
    if (res == "")
        res = "0";
    reverse(res.begin(), res.end());
    cout << res << "\n";
}
big_integer& big_integer::operator=(big_integer const& value)
{
    v.resize(value.size());
    sign = value.sign;
    for (size_t i = 0; i < value.size(); ++i)
    {
        v[i] = value[i];
    }
    return *this;
}


void add(myVec &res, const myVec a, const myVec &b)
{
    long long int carry = 0;
    res.resize(max(a.size(), b.size()));
    for (size_t i = 0; i < res.size(); ++i)
    {
        carry += (i < a.size() ? (long long int)a[i] : 0) + (i < b.size() ? (long long int)b[i] : 0);
        res[i] = (int) (carry % BASE);
        carry /= BASE;
    }
    if (carry != 0)
    {
        res.push_back(carry);
    }
    normalize(res);
}
void subtract(myVec &res, const myVec a, const myVec b)
{
    res = a;
    long long int cur;
    for (size_t i = 0; i < res.size(); ++i)
    {
        cur = res[i];
        if (res[i] < (i < b.size() ? b[i] : 0))
        {
            cur += BASE;
            res[i + 1]--;
        }
        cur -= (i < b.size() ? b[i] : 0);
        res[i] = cur;
    }
    normalize(res);
}
void multiply(myVec &res, const myVec a, const myVec &b)
{
    res.resize(a.size() + b.size() + 1);
    res.myFill(0);
    long long int carry;
    vector<long long int> resTemp;
    resTemp.resize(a.size() + b.size() + 1);
    long long int cur;
    for (size_t i = 0; i < a.size(); ++i)
    {
        carry = 0;
        for (size_t j = 0; j < b.size(); ++j)
        {
            cur = resTemp[i + j] + a[i] * 1ll* b[j];
            resTemp[i + j] = cur % BASE;
            carry = cur / BASE;
            resTemp[i + j + 1] += carry;
        }
    }
    for (size_t i = 0; i < resTemp.size(); ++i)
    {
        res[i] = (int) resTemp[i];
    }
    normalize(res);
}
int vec_cmp(myVec const &a, myVec const &b, int pos1, int pos2, int len)
{
     int x, y;
     for (int i = 0; i < len; ++i)
     {
//         assert(pos1 + i < (int) a.size());
        x = a[pos1 - i];
        y = b[pos2 - i];
//        x= 0 ;
        if (x != y)
        {
            return x > y ? 1 : -1;
        }
     }
     return 0;
 }
int comparePref(const myVec& a, int pos, int len, myVec& b)
{
    while (len > 0 && pos >= 0 && a[pos] == 0)
    {
        --len;
        --pos;
    }
    if (len == 0)
    {
        pos++;
        len++;
    }
    if ((int) b.size() != len)
    {
        return len < (int) b.size() ? -1 : 1;
    }
    return vec_cmp(a, b, pos, (int) b.size() - 1, len);
}
void subPref(myVec& a, int pos, int len, const myVec& b)
{
    long long int cur;

    int pos2 = pos - len + 1;

    for (int i = 0; i < len; ++i)
    {
        cur = a[pos2 + i];
        if (a[pos2 + i] < (i < (int) b.size() ? b[i] : 0))
        {
            cur += BASE;
            a[pos2 + i + 1]--;
        }
        cur -= (i < (int) b.size() ? b[i] : 0);
        a[pos2 + i] = cur;
    }
    return;
}
void longDiv(myVec& res, myVec a, const myVec& b)
{
    if (a.size() < b.size())
    {
        res.clear();
        res.push_back(0);
        return;
    }
    else if (b.size() == 1)
    {
        int nth = 0;
        shortDivMod(BASE, b[0], a, res, nth);
        return;
    }
    res.clear();
    int128_t divident = 0, divisor = 0, result = 0;
    myVec temp;
    a.push_back(0);
    for (int i = (int) a.size() - 1; i >= (int) b.size(); --i)
    {
        divident = ((int128_t) a[i]) * ((int128_t) BASE) * ((int128_t) BASE) + ((int128_t) a[i - 1]) * ((int128_t) BASE) + ((int128_t) a[i - 2]);
        divisor = ((int128_t) b[b.size() - 1]) * ((int128_t) BASE) + ((int128_t) b[b.size() - 2]);
        result = divident / divisor;
        result = min(result, (int128_t) NEEDBIT);
        multiply(temp, myVec(1, (int) result), b);
        if (comparePref(a, i, (int) b.size() + 1, temp) == -1)
        {
            --result;
             multiply(temp, myVec(1, (int) result), b);
        }
        res.push_back((int) result);
        subPref(a, i, (int) b.size() + 1, temp);
    }
    res.reverseAll();
    normalize(res);
}

int comp(big_integer const& a, big_integer const& b, bool absCompare)
{
    if (!absCompare && a.sign != b.sign)
        return (a.sign > b.sign ? 1 : -1);
    if (a.size() != b.size())
    {
        if (a.size() > b.size() && a.sign == 1 && !absCompare)
            return 1;
        if (a.size() < b.size() && a.sign == -1 && !absCompare)
            return 1;
        if (absCompare)
        {
            if (a.size() > b.size())
                return 1;
        }
        return -1;
    }
    for (int i = a.size() - 1; i >= 0; --i)
    {
        if (a[i] == b[i])
            continue;
        if (!absCompare && a[i] > b[i] && a.sign == 1)
            return 1;
        if (!absCompare && a[i] < b[i] && a.sign == -1)
            return 1;
        if (absCompare)
            return (a[i] > b[i]) ? 1 : -1;
        return -1;
    }
    return 0;
}

big_integer& big_integer::operator/=(big_integer const& value)
{
    int signOther = value.sign;
    longDiv(v, v, value.v);
    sign *= signOther;
    return *this;
}

big_integer& big_integer::operator+=(big_integer const& value)
{
    if (sign == value.sign)
    {
        add(v, v, value.v);
    }
    else
    {
        int res = comp(*this, value, true);
        if (res == 1)
            subtract(v, v, value.v);
        else
            subtract(v, value.v, v), sign = value.sign;
    }
    if (v.size() == 1 && v[0] == 0)
        sign = 1;
    return *this;
}

big_integer& big_integer::operator-=(big_integer const& value)
{
    return *this += -value;
}

big_integer& big_integer::operator*=(big_integer const& value)
{
    multiply(v, v, value.v);
    sign *= value.sign;
    return *this;
}
big_integer& big_integer::operator%=(big_integer const& value)
{
    *this = *this - (*this / value) * value;
    return *this;
}
big_integer& big_integer::operator&=(big_integer const& value)
{
    return *this = byteFunctionBigInteger(to_byte(v, sign), to_byte(value.v, value.sign), AND);
}

big_integer& big_integer::operator|=(big_integer const& value)
{
    return *this = byteFunctionBigInteger(to_byte(v, sign), to_byte(value.v, value.sign), OR);
}

big_integer& big_integer::operator^=(big_integer const& value)
{
    return *this = byteFunctionBigInteger(to_byte(v, sign), to_byte(value.v, value.sign), XOR);
}
big_integer& big_integer::operator<<=(int const& value)
{
    return (*this = leftShift(to_byte(v, sign), value));
}
big_integer& big_integer::operator>>=(int const& value)
{
    return (*this = rightShift(to_byte(v, sign), value));
}
bool operator==(big_integer const& a, big_integer const& b)
{
    return (comp(a, b) == 0);
}
bool operator!=(big_integer const& a, big_integer const& b)
{
    return (comp(a, b) != 0);
}
bool operator<(big_integer const& a, big_integer const& b)
{
    return (comp(a, b) == -1);
}
bool operator>(big_integer const& a, big_integer const& b)
{
    return (comp(a, b) == 1);
}
bool operator<=(big_integer const& a, big_integer const& b)
{
    return (comp(a, b) != 1);
}
bool operator>=(big_integer const& a, big_integer const& b)
{
    return (comp(a, b) != -1);
}
big_integer& big_integer::operator++()
{
    return (*this += ONE);
}
big_integer big_integer::operator++(int)
{
    big_integer res = *this;
    ++*this;
    return res;
}
big_integer& big_integer::operator--()
{
    return (*this -= ONE);
}
big_integer big_integer::operator--(int)
{
    big_integer res = *this;
    --*this;
    return res;
}


big_integer operator+(big_integer a, big_integer const& b)
{
    return a += b;
}
big_integer operator-(big_integer a, big_integer const& b)
{
    return a -= b;
}
big_integer operator*(big_integer a, big_integer const& b)
{
    return a *= b;
}
big_integer operator/(big_integer a, big_integer const& b)
{
    return a /= b;
}
big_integer operator%(big_integer a, big_integer const& b)
{
    return a %= b;
}
big_integer operator&(big_integer a, big_integer const& b)
{
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b)
{
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b)
{
    return a ^= b;
}
big_integer operator>>(big_integer a, int const& b)
{
    return a >>= b;
}
big_integer operator<<(big_integer a, int const& b)
{
    return a <<= b;
}
string to_string(big_integer const& a)
{
    string res = "";
    myVec v = a.v;
    int mod;
    while(!(v.size() == 1 && v[0] == 0))
    {
        shortDivMod(BASE, 10, v, v, mod);
        res += (char) (mod + 48);
    }
    if (a.sign == -1)
    {
        res += "-";
    }
    reverse(res.begin(), res.end());
    return (!res.empty()) ? res : "0";
}
std::ostream& operator>>(std::ostream &s, big_integer const& a)
{
    s << to_string(a);
    return s;
}
/*int main()
{
    big_integer a("1000000000000000000000000000000000"); /// 10^33
    big_integer b("100000000000000000000000"); /// 10^23
    print(a / b);
    // big_integer("-21474x83648");
    return 0;
}*/
