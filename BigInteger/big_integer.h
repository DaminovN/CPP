#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H
struct big_integer
{
	big_integer();
	big_integer(big_integer const& value);
	big_integer(const std::vector<uint32_t>& val, int sign);
	big_integer(big_integer const& value, int sign);
	big_integer(int value);
	explicit big_integer(std::string const& value);
	~big_integer();
	//operations
	big_integer operator+() const;
	big_integer operator-() const;
    big_integer operator~() const;

	big_integer& operator=(big_integer const& value);

	big_integer& operator+=(big_integer const& value);
	big_integer& operator/=(big_integer const& value);
	big_integer& operator-=(big_integer const& value);
	big_integer& operator*=(big_integer const& value);
	big_integer& operator%=(big_integer const& value);
	big_integer& operator&=(big_integer const& value);
	big_integer& operator|=(big_integer const& value);
	big_integer& operator^=(big_integer const& value);
	big_integer& operator<<=(int const& value);
	big_integer& operator>>=(int const& value);

	friend big_integer operator+(big_integer a, big_integer const& b);
	friend big_integer operator-(big_integer a, big_integer const& b);
	friend big_integer operator*(big_integer a, big_integer const& b);
	friend big_integer operator/(big_integer a, big_integer const& b);

	big_integer& operator++();
	big_integer operator++(int);
	big_integer& operator--();
	big_integer operator--(int);

	friend bool operator==(big_integer const& a, big_integer const& b);
	friend bool operator!=(big_integer const& a, big_integer const& b);
	friend bool operator<(big_integer const& a, big_integer const& b);
	friend bool operator>(big_integer const& a, big_integer const& b);
	friend bool operator<=(big_integer const& a, big_integer const& b);
	friend bool operator>=(big_integer const& a, big_integer const& b);

	friend std::string to_string(big_integer const& a);

	friend void print(big_integer value);

private:
	std::vector<uint32_t> v;
	int sign;
	friend int comp(big_integer const& a, big_integer const& b);
	friend std::vector<uint32_t> to_byte(std::vector<uint32_t> v, int sign);
	friend big_integer leftShift(big_integer const& val, int shift);
	friend big_integer rightShift(big_integer const& val, int shift);
	uint32_t& operator[](int pos)
	{
		return v[pos];
	}

	const uint32_t& operator[](int pos) const
	{
		return v[pos];
	}

	size_t size() const
	{
		return v.size();
	}
};

bool operator==(big_integer const& a, big_integer const& b);

bool operator!=(big_integer const& a, big_integer const& b);

bool operator<(big_integer const& a, big_integer const& b);

bool operator>(big_integer const& a, big_integer const& b);

bool operator<=(big_integer const& a, big_integer const& b);

bool operator>=(big_integer const& a, big_integer const& b);


big_integer operator+(big_integer a, big_integer const& b);

big_integer operator-(big_integer a, big_integer const& b);

big_integer operator*(big_integer a, big_integer const& b);

big_integer operator/(big_integer a, big_integer const& b);

big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);

big_integer operator|(big_integer a, big_integer const& b);

big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int const& b);

big_integer operator>>(big_integer a, int const& b);


std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);
#endif