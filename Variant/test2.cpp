#include <bits/stdc++.h>
#include <variant>

using namespace std;

void f(string) {
	cout << "STRING\n";
}

void f(bool) {
	cout << "BOOL\n";
}

int main()
{
	// variant<int, int, int> a;
	// a = 2;
	f("asdasd");
}