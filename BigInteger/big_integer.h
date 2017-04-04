struct big_integer
{
	big_integer();
	big_integer(big_integer const& value);
	big_integer(int value);
	explicit big_integer(std::string const& value);
	~big_integer();
	friend void print(big_integer const& value);
	//operations
	//big_integer& operator=(big_integer const& value);
private:
	std::vector<int> v;
	int sign;
};