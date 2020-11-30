#include<iostream>
#include<list>
#include<iterator>
#include<algorithm>
#include<ctime>
#include"MyList.cpp"
using namespace std;

int main()
{
	clock_t start, end;
	double time;

	int a[5] = { 1,3,4,5,3 };
	int b[4] = { 6,7,6,9 };

	mylist<int> amlist(a, 5);
	mylist<int> bmlist(b, 4);

	list<int>alist(a, a + 5);
	list<int>blist(b, b + 4);

	cout << "swap:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		amlist.swap(bmlist);
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		alist.swap(blist);
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "begin:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		amlist.begin();
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		alist.begin();
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "end:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		amlist.end();
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		alist.end();
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "insert:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		amlist.insert(amlist.begin(),1);
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
		alist.insert(alist.begin(), 1);
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "erase:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		mylist<int>::iterator itbeg = amlist.begin();
		amlist.erase(itbeg, ++itbeg);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.erase(alist.begin(), ++alist.begin());
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "clear:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.clear();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.clear();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "empty:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.empty();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.empty();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "front:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		bmlist.front();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		blist.front();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "back:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		bmlist.back();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		blist.back();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "push_back(e):" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		bmlist.push_back(9);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		blist.push_back(9);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "pop_back():" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		int e = 0;
		bmlist.pop_back(e);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		blist.pop_back();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "push_front(e):" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		bmlist.push_front(7);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		blist.push_front(7);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "l.splice(pos,a):" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.splice(amlist.begin(), bmlist);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.splice(alist.begin(), blist);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;


	bmlist = amlist;
	blist = alist;
	cout << "l.splice(pos,a,abeg£¬aend):" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.splice(amlist.begin(), bmlist, bmlist.begin(), bmlist.end());
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.splice(alist.begin(), blist, blist.begin(), blist.end());
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;


	bmlist = amlist;
	blist = alist;
	cout << "l.splice(pos,a,posa):" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.splice(amlist.begin(), bmlist, bmlist.begin());
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.splice(alist.begin(), blist, blist.begin());
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "unique():" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.unique();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.unique();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "remove£¨x£©:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.remove(7);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.remove(7);
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "Sort(£©:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.Sort();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.sort();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;

	cout << "reverse(£©:" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		amlist.reverse();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "mylist:" << time << "*10^-6ms" << endl;
	start = clock();
	for (int i = 0; i < 1000000; i++)
	{
		alist.reverse();
	}
	end = clock();
	time = (double)end - (double)start;
	cout << "list:" << time << "*10^-6ms" << endl;
	cout << endl;
}