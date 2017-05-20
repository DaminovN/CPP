#include<bits/stdc++.h>
#include "big_integer.h"
using namespace std;


const uint64_t BASE = (1ull << 32ull);
const uint32_t NEEDBIT = (uint32_t) (BASE - 1ull);
const uint64_t MOD = (1ull << 32ull);
const int BASEPOW = 32;
int nothing;

big_integer::big_integer() : v(1, 0), sign(1) {}

big_integer::big_integer(big_integer const& value) : v(value.v), sign(value.sign) {}

big_integer::big_integer(big_integer const& value, int sign): v(value.v), sign(sign) {}

big_integer::big_integer(int value)
{
	if (value >= 0)
		sign = 1;
	else
		sign = -1;
	value = abs(value);
	v.clear();
	if (value == 0)
		v.push_back(0);
	while (value > 0)
	{
		v.push_back(value % BASE);
		value /= BASE;
	}
}
big_integer::big_integer(const vector<uint32_t>& val, int sgn) : sign(sgn)
{
	v.insert(v.begin(), val.begin(), val.end());
}
void normalize(vector<uint32_t> &val)
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
void shortDivMod(int const& divider, const vector<uint32_t> a, vector<uint32_t>& res, uint32_t& mod)
{
	uint64_t cur = 0;
	res.resize(a.size(), 0);
	for (int i = a.size() - 1; i >= 0; --i)
	{
		cur = cur * BASE + a[i];
		res[i] = cur / divider;
		cur %= divider;
	}
	mod = (uint32_t) cur;
	normalize(res);
}
big_integer::big_integer(string const& value)
{
	v.clear();
	sign = 1;
	int end = 0;
	if (value[0] == '-')
		sign = -1, end = 1;
	vector<uint32_t> temp;
	for (int i = (int) value.size() - 1; i >= end; --i)
	{
		temp.push_back((uint32_t)(value[i] - '0'));
	}
	uint32_t mod = 0;
	while(temp.size() != 1 || temp[0] != 0)
	{
		shortDivMod(10, temp, temp, mod);
		v.push_back(mod);
	}
	normalize(v);
}
big_integer::~big_integer() {}


big_integer big_integer::operator+() const
{
	return *this;
}
big_integer big_integer::operator-() const
{
	return big_integer(*this, -sign);
}

big_integer ZERO(0);
big_integer ONE(1);

big_integer big_integer::operator~() const
{
	return (-(*this) - ONE);
}

vector<uint32_t> to_byte(vector<uint32_t> v, int sign)
{
	// cout << v.size() << " " << v[0] << endl;
	if (sign < 0)
	{
		// cout << (~big_integer(v, 1)).v.size() << " " << (~big_integer(v, 1)).v[0] << endl;
		// print(~(big_integer(v, 1)));
		// print(ONE);
		// print((~(big_integer(v, 1))) + ONE);
		v = ((~big_integer(v, 1)) + ONE).v;
	}
	v.push_back((sign >= 0) ? 0 : NEEDBIT);
	// cout << "HERE\n";
	// cout << v.size() << " " << v[0] << " " << v[1] << endl;
	// cout << "HERE\n";
	return v;
}
big_integer from_byte(vector<uint32_t> v)
{
	// cout << "->  " << v.size() << " " << v[0] << " " << v[1] << endl;
	int sign = 1;
	if (v.back() == NEEDBIT)
		sign = -1;
	v.pop_back();
	return (sign == -1) ? big_integer((~big_integer(v, 1)) + ONE) : big_integer(v, 1);

}

enum operation { XOR, OR, AND };

big_integer byteFunctionBigInteger(const vector<uint32_t>& a, const vector<uint32_t>& b, operation op)
{
    vector<uint32_t> res(max(a.size(), b.size()));
    for(int i = 0; i < (int)res.size(); i++)
    {
    	if (op == AND)
    		res[i] = a[min((int)a.size() - 1, i)] & b[min((int)b.size() - 1, i)];
    	else if (op == XOR)
    		res[i] = a[min((int)a.size() - 1, i)] | b[min((int)b.size() - 1, i)];
    	else 
    		res[i] = a[min((int)a.size() - 1, i)] ^ b[min((int)b.size() - 1, i)];
    }
    return from_byte(res);
}
big_integer leftShift(const vector<uint32_t>& a, int shift)
{
    vector<uint32_t> res(shift / BASEPOW, 0);
    uint64_t cur = 0;
    uint32_t last = a.back();
    shift %= BASEPOW;
    for (size_t i = 0; i < a.size(); ++i)
    {
        cur += ((uint64_t) a[i]) << shift;
        res.push_back(cur & NEEDBIT);
        cur >>= BASEPOW;
    }

    res.push_back(last);
    return from_byte(res);
}
big_integer rightShift(const vector<uint32_t>& a, int shift)
{
    vector<uint32_t> res;
    uint32_t last = a.back();
    int i = shift / BASEPOW;
    shift %= BASEPOW;
    uint64_t cur = a[i] >> shift;
    while(i + 1 < (int)a.size())
    {
        cur = cur + (((uint64_t) a[i + 1]) << (BASEPOW - shift));
        res.push_back(cur & (uint64_t) NEEDBIT);
        cur >>= BASEPOW;
        i++;
    }
    res.push_back(last);
    return from_byte(res);
}
void print(big_integer value)
{
	if (value.sign == -1)
		printf("-");
	uint32_t mod = 0;
	string res = "";
	while (value.size() != 1 || value[0] != 0)
	{
		shortDivMod(10, value.v, value.v, mod);
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


void add(vector<uint32_t> &res, const vector<uint32_t> a, const vector<uint32_t> &b)
{
	uint64_t carry = 0;
	res.resize(max(a.size(), b.size()));
	for (size_t i = 0; i < res.size(); ++i)
	{
		carry += (i < a.size() ? (uint64_t)a[i] : 0) + (i < b.size() ? (uint64_t)b[i] : 0);
		res[i] = (uint32_t) (carry % BASE);
		carry /= BASE;
	}
	if (carry != 0)
	{
		res.push_back(carry);
	}
	normalize(res);
}
void subtract(vector<uint32_t> &res, const vector<uint32_t> a, const vector<uint32_t> b)
{
	res = a;
	uint64_t cur;
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
void multiply(vector<uint32_t> &res, const vector<uint32_t> a, const vector<uint32_t> &b)
{
	res.resize(a.size() + b.size() + 1);
	fill(res.begin(), res.end(), 0);
	uint64_t carry = 0;
	vector<uint64_t> resTemp;
	resTemp.resize(a.size() + b.size() + 1);
	for (size_t i = 0; i < a.size(); ++i)
	{
		for (size_t j = 0, carry = 0; j < b.size(); ++j)
		{
			uint64_t cur = resTemp[i + j] + a[i] * 1ull* b[j];
			resTemp[i + j] = cur % BASE;
			carry = cur / BASE;
			resTemp[i + j + 1] += carry;
		}
	}
	for (size_t i = 0; i < resTemp.size(); ++i)
	{
		res[i] = (uint32_t) resTemp[i];
	}
	normalize(res);
}
void longDiv(vector<uint32_t>& res, const vector<uint32_t> a, const vector<uint32_t>& b)
{
	if (a.size() < b.size())
	{
		res = {0};
		return;
	}
	else if (b.size() == 1)
	{
		uint32_t nth = 0;
		shortDivMod(b[0], a, res, nth); 
		return;
	}
	vector<uint32_t> temp, val;
	res.resize(a.size() - b.size() + 2);
	fill(res.begin(), res.end(), 0);
	for (int i = (int) a.size() - 1; i >= 0; --i)
	{
		val.insert(val.begin(), a[i]);
		uint64_t l = 1, r = BASE;
		while (l < r)
		{
			uint64_t m = (l + r) / 2ull;
			multiply(temp, {(uint32_t) m}, b);
			if (comp(big_integer(val, 1), big_integer(temp, 1)) >= 0)
				l = m + 1;
			else 
				r = m;
		}
		res[i] = (uint32_t) (r - 1);
		multiply(temp, {res[i]}, b);
		subtract(val, val, temp);
		while(!val.empty() && val.back() == 0)
			val.pop_back();
	} 
	normalize(res);
}
int comp(big_integer const& a, big_integer const& b)
{
	if (a.sign != b.sign)
		return (a.sign > b.sign ? 1 : -1);
	if (a.size() != b.size())
	{
		if (a.size() > b.size() && a.sign == 1)
			return 1;
		if (a.size() < b.size() && a.sign == -1)
			return 1;
		return -1;
	}
	for (int i = a.size() - 1; i >= 0; --i)
	{
		if (a[i] == b[i])
			continue;
		if (a[i] > b[i] && a.sign == 1)
			return 1;
		if (a[i] < b[i] && a.sign == -1)
			return 1;
		return -1;
	}
	return 0;
}

big_integer& big_integer::operator/=(big_integer const& value)
{
	int signOther = (value >= 0);
	if (signOther < 0)
		signOther = - signOther;
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
		int res = comp(*this, value);
		if (res == 1)
			subtract(v, v, value.v);
		else if (res == -1)
			subtract(v, value.v, v);
		else
			*this = ZERO;
	}
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
	vector<uint32_t> v = a.v;
	uint32_t mod;
	while(!(v.size() == 1 && v[0] == 0))
	{
		shortDivMod(10, v, v, mod);
		res += (char) (mod + 48);
	}
	if (a.sign == -1)
	{
		res += "-";
	}
	reverse(res.begin(), res.end());
	return (!res.empty()) ? res : "0";
}
int main()
{
	return 0;
}