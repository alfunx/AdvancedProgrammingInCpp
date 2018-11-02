#include <functional>
#include <iostream>
using namespace std;

struct foo {

	std::string name;

	foo(std::string name) : name(name) { /* void */ }

	void say_hello()
	{
		cout << "Hello, World! Here's " << name << "." << endl;
	}

};

int main(int argc, char** argv)
{
	vector<foo*> foobar;
	foo bar("bar");
	foo baz("baz");
	foo qux("qux");
	foobar.push_back(&bar);
	foobar.push_back(&baz);
	foobar.push_back(&qux);

	for (vector<foo*>::iterator i = foobar.begin(); i < foobar.end(); i++)
		(*i)->say_hello();

	auto greet = std::mem_fun(&foo::say_hello);
	for_each(foobar.begin(), foobar.end(), greet);

	// or

	for (auto f : foobar)
		f->say_hello();

	for (auto f : foobar)
		greet(f);

	return 0;
}
