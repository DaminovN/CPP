#include <bits/stdc++.h>
#include <variant>

using namespace std;

int main()
{
	variant<string, bool> x("abc");

	cout << holds_alternative<bool>(x) << "\n";

	return 0;
}