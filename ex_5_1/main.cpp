#include "dumb_pointer.h"
#include "smart_pointer.h"
#include <iostream>
#include <list>
#include <vector>
using namespace std;

template<typename T>
void pass_dumb_pointer(dumb_pointer<T> p)
{
	cout << ">>> p_pass: " << p << endl << endl;
}

void dumb_pointer_test(bool pass = false)
{
	std::list<int> *l = new list<int>();
	l->push_back(1);
	l->push_back(2);

	dumb_pointer<list<int>> p(l);
	cout << ">>> p:      " << p << endl << endl;

	list<int> l_new = *p;
	cout << ">>> l:      " << p->size() << endl;
	cout << "    l_new:  " << l_new.size() << endl << endl;

	if (pass)
		pass_dumb_pointer(p);

	cout << ">>> p:      " << p << endl << endl;
}

template<typename T>
void pass_smart_pointer(smart_pointer<T> p)
{
	cout << ">>> p_pass: " << p << endl << endl;
}

void smart_pointer_test(bool pass = false)
{
	std::list<int> *l = new list<int>();
	l->push_back(1);
	l->push_back(2);

	smart_pointer<list<int>> p(l);
	cout << ">>> p:      " << p << endl << endl;

	list<int> l_new = *p;
	cout << ">>> l:      " << p->size() << endl;
	cout << "    l_new:  " << l_new.size() << endl << endl;

	if (pass)
		pass_smart_pointer(p);

	cout << ">>> p:      " << p << endl << endl;
}

void smart_pointer_test2()
{
	std::list<int> *l = new list<int>();
	l->push_back(1);
	l->push_back(2);

	smart_pointer<list<int>> p(l);
	cout << ">>> p0:     " << p << endl << endl;

	smart_pointer<list<int>> p1 = p;
	smart_pointer<list<int>> p2 = p;
	smart_pointer<list<int>> p3 = p;
	cout << ">>> p0:     " << p << endl;
	cout << "    p1:     " << p1 << endl;
	cout << "    p2:     " << p2 << endl;
	cout << "    p3:     " << p3 << endl << endl;

	std::list<int> *l1 = new list<int>();
	l1->push_back(3);

	smart_pointer<list<int>> p4(l1);
	cout << ">>> p4:     " << p4 << endl << endl;

	p3 = p4;
	cout << ">>> p0:     " << p << endl;
	cout << "    p1:     " << p1 << endl;
	cout << "    p2:     " << p2 << endl;
	cout << "    p3:     " << p3 << endl;
	cout << "    p4:     " << p4 << endl << endl;
}

void print_help()
{
	cout << "usage: pointer [-d] [-dp] [-s] [-sp] [-s2]" << endl;
}

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	for (int i = 1; i < argc; i++) {
		if ("-d" == args[i]) {
			dumb_pointer_test();
			return 0;
		} else if ("-dp" == args[i]) {
			dumb_pointer_test(true);
			return 0;
		} else if ("-s" == args[i]) {
			smart_pointer_test();
			return 0;
		} else if ("-sp" == args[i]) {
			smart_pointer_test(true);
			return 0;
		} else if ("-s2" == args[i]) {
			smart_pointer_test2();
			return 0;
		} else if ("-h" == args[i]) {
			print_help();
			return 0;
		} else {
			print_help();
			return 1;
		}
	}

	return 0;
}
