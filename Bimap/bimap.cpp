#include <bits/stdc++.h>
#include "bimap.h"

using namespace std;



struct counted
{
	counted() : data()
	{
		auto p = instances.insert(this);
        if (!(p.second == true))
        cout << "WRONG1" << endl;
	}
	counted(int data)
        : data(data)
    {
        // cerr << "HERE insert " << data << endl;
        auto p = instances.insert(this);
        // cerr << "HERE insert " << data << " " << instances.size() << endl;
        if (!(p.second == true))
        cout << "WRONG2" << endl;
    }

    counted(counted const& other)
        : data(other.data)
    {
        // cerr << "-? " << instances.size() << endl;
        // for(auto i : instances)
        //     cerr << i->data << " ";
        // cout << endl;
        auto p = instances.insert(this);
        // cerr << "-? " << instances.size() << endl;
        // for(auto i : instances)
        //     cerr << i->data << " ";
        // cout << endl;
        if (!(p.second == true))
            {cout << data << " WRONG3" << endl;}
    }

    ~counted()
    {
        // cerr << "CALLED " << instances.size() << "\n";
        size_t n = instances.erase(this);
        if (!(1u == n))
        cout << "WRONG4" << endl;
    }

    counted& operator=(counted const& c)
    {
        if (!((instances.find(this) != instances.end()) == true))
        cout << "WRONG5" << endl;

        data = c.data;
        return *this;
    }

    operator int() const
    {
        if (!((instances.find(this) != instances.end()) == true))
    	cout << "WRONG6" << endl;

        return data;
    }

    static void expect_no_instances()
    {
        // EXPECT_EQ(0u, instances.size());
        if (!(0u == instances.size()))
            cout << "WRONG7" << endl;
    }
private:
	int data;
	static set<counted const*> instances;
};

std::set<counted const*> counted::instances;

using container = bimap<counted, counted>;


void expect_has_pair(container& m, int a, int b)
{
	auto i = m.find_left(a);
    if (!(!(i == m.end_left())))
	cout << "WRONG8" << endl;
    if (!(*i == a))
	cout << "WRONG9" << endl;
    if (!(*(i.flip()) == b))
	cout << "WRONG_10" << endl;
	auto j = m.find_right(b);
    if (!(!(j == m.end_right())))
	cout << "WRONG_11" << endl;
    if (!(*j == b))
	cout << "WRONG_12" << endl;
    if (!(*(j.flip()) == a))
	cout << "WRONG_13" << endl;
}
template<typename T>
void EXPECT_EQ(T a, T b)
{
    if (!(a == b))
	cout << "WRONG_14" << endl;
}
void insert1()
{
    // {
    	container c;
        c.insert(1, 2);
        c.insert(3, 4);
        c.insert(5, 6);
        // cerr << "FINISHED INSERT\n";
    // }
    // counted::expect_no_instances();

    expect_has_pair(c, 1, 2);
    expect_has_pair(c, 3, 4);
    expect_has_pair(c, 5, 6);

    EXPECT_EQ(c.find_left(2), c.end_left());
    EXPECT_EQ(c.find_left(4), c.end_left());

    EXPECT_EQ(c.find_right(1), c.end_right());
    EXPECT_EQ(c.find_right(3), c.end_right());
    EXPECT_EQ(c.find_right(5), c.end_right());
}
void insert2()
{
	container c;
    c.insert(5, 5);
    c.insert(3, 6);
    c.insert(2, 8);
    c.insert(4, 4);
    c.insert(7, 3);
    c.insert(6, 7);
    c.insert(8, 2);

    expect_has_pair(c, 5, 5);
    expect_has_pair(c, 3, 6);
    expect_has_pair(c, 2, 8);
    expect_has_pair(c, 4, 4);
    expect_has_pair(c, 7, 3);
    expect_has_pair(c, 6, 7);
    expect_has_pair(c, 8, 2);
}
int main()
{
	// m.insert(mp, mp);
	insert1();
    // std::cerr << "AFTER first Insert\n";
 //    // cerr << "the size " << 
	insert2();
    // bimap<int, int> mp;
    // mp.insert(1, 2);
    
	return 0;
}
