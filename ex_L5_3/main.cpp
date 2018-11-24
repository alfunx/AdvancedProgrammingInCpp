#include <iostream>
#include <vector>

using namespace std;

void print_help()
{
	cout << "usage: inheritance [foo | bar | baz | foobar | barfoo | diamond]" << endl;
}

struct foo
{
	foo() { cout << "foo()" << endl; }
	~foo() { cout << "~foo()" << endl; }
};

struct bar
{
	bar() { cout << "bar()" << endl; }
	~bar() { cout << "~bar()" << endl; }
};

struct baz : public foo
{
	baz() { cout << "baz()" << endl; }
	~baz() { cout << "~baz()" << endl; }
};

struct foobar : public foo, bar
{
	foobar() { cout << "foobar()" << endl; }
	~foobar() { cout << "~foobar()" << endl; }
};

struct barfoo : public bar, foo
{
	barfoo() { cout << "barfoo()" << endl; }
	~barfoo() { cout << "~barfoo()" << endl; }
};

struct baaz : public foo
{
	baaz() { cout << "baaz()" << endl; }
	~baaz() { cout << "~baaz()" << endl; }
};

struct diamond : public baz, baaz
{
	diamond() { cout << "diamond()" << endl; }
	~diamond() { cout << "~diamond()" << endl; }
};

int main(int argc, char** argv)
{
	vector<string> args(argv, argv + argc);

	if (argc < 2) {
		print_help();
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		if ("foo" == args[i]) {
			foo x;
		} else if ("bar" == args[i]) {
			bar x;
		} else if ("baz" == args[i]) {
			baz x;
		} else if ("foobar" == args[i]) {
			foobar x;
		} else if ("barfoo" == args[i]) {
			barfoo x;
		} else if ("diamond" == args[i]) {
			diamond x;
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
