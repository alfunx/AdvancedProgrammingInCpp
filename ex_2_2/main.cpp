#include "fraction.h"
#include "pvector.h"
#include <iostream>
using namespace std;

template<typename T>
void fn_ref(pvector<T>* pv, T e)
{
	cout << "Pass by reference." << endl;
	pv->push_back(e);
}

template<typename T>
void fn_val(pvector<T> pv, T e)
{
	cout << "Pass by value." << endl;
	pv.push_back(e);
}

int main(int argc, char** argv)
{
	// pvector<fraction> pv("pvector.txt");
        //
	// for (const fraction &f : pv) {
	// 	cout << f << endl;
	// }

	// fraction f;
	// cout << ">>> ";
	// cin >> f;
	// pv.push_back(f);

	// cout << ">>> fraction val" << endl;
	// pvector<fraction> pv_f_v("fraction_val.txt");
	// fn_val(pv_f_v, fraction(1, 2));

	// cout << ">>> fraction ref" << endl;
	// pvector<fraction> pv_f_r("fraction_ref.txt");
	// fn_ref(&pv_f_r, fraction(1, 2));

	// cout << ">>> string val" << endl;
	// pvector<string> pv_s_v("string_val.txt");
	// fn_val(pv_s_v, string("hello"));

	// cout << ">>> string ref" << endl;
	// pvector<string> pv_s_r("string_ref.txt");
	// fn_ref(&pv_s_r, string("hello"));

	return 0;
}
