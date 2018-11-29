#include <iostream>
#include <vector>

using namespace std;

void print_help()
{
	cout << "usage: inheritance [foo | bar | baz | foobar | barfoo | diamond | tree]" << endl;
}

#define GEN(NAME, ...) \
	struct NAME __VA_OPT__(: public __VA_ARGS__) \
	{ \
		NAME() { cout << #NAME "()" << endl; } \
		~NAME() { cout << "~" #NAME "()" << endl; } \
	}

GEN(foo);
GEN(bar);

GEN(baz, foo);
GEN(baaz, foo);

GEN(foobar, foo, bar);
GEN(barfoo, bar, foo);

GEN(barbaz, bar, baz);
GEN(bazbar, baz, bar);

GEN(diamond, baz, baaz);

/*  inheritance tree:
 *
 *                            f
 *                            |
 *                    -----------------
 *                   /                 \
 *                  b                   g
 *                  |                   |
 *              ---------               -----
 *             /         \                   \
 *            a           d                   i
 *                        |                   |
 *                    ---------            ----
 *                   /         \          /
 *                  c           e        h
 *
 *  post-order tree traversal:
 *  a, c, e, d, b, h, i, g, f
 *
 */

GEN(h);
GEN(i, h);
GEN(g, i);
GEN(e);
GEN(c);
GEN(d, c, e);
GEN(a);
GEN(b, a, d);
GEN(f, b, g);

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
		} else if ("barbaz" == args[i]) {
			barbaz x;
		} else if ("bazbar" == args[i]) {
			bazbar x;
		} else if ("diamond" == args[i]) {
			diamond x;
		} else if ("tree" == args[i]) {
			f x;
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
