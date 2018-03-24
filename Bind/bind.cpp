#include <bits/stdc++.h>
#include "bind.h"

void f(int a, int b, int c)
{
    std::cout << a << b << c << std::endl;
}

int g(int a, int b)
{
    return a + b;
}

/*int x(int a)
{
    return a;
}*/
using namespace my_bind;
int main()
{
	std::function<void(int)> x = [](int a){std::cout << a << "\n";};	
    auto s = my_bind::bind(x, 1);
    x = [](int a){std::cout << a + 1 << "\n";};
    s(1, 2, 1, 2);
    bind(&f, 1, 2, 3)();
    bind(&f, _1, _3, _2)(4, 6, 5);
    bind(&f, _1, _1, _2)(7, 8);
    bind(&f, _1, bind(&g, _1, 5), _2)(2, 3);
    return 0;
}