#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

static const int collection_size = 500000000;
static const double nano_per_sec = 1000000000.0;

template<typename E, typename C>
void find_element(C c, bool (*matcher)(const E))
{
	high_resolution_clock::time_point start = high_resolution_clock::now();
	auto it = find_if(c->begin(), c->end(), matcher);
	high_resolution_clock::time_point end = high_resolution_clock::now();

	if (it == c->end())
		cout << "Element not found." << endl;
	else
		cout << "Element found: " << *it << endl;

	auto duration = duration_cast<nanoseconds>(end - start).count() / nano_per_sec;
	cout << "Time: " << duration << "s" << endl << endl;
}

template<typename E, typename C>
void prepare_collection(C c, E wrong, E correct)
{
	for (int i = 1; i < collection_size; ++i) {
		if (i % (collection_size / 10) == 0)
			cout << " > inserted: " << i << endl;

		c->push_back(wrong);
	}
	c->push_back(correct);

	cout << "Collection ready." << endl << endl;
}

int main(int argc, char** argv)
{
	const int find = 1;
	const int last = 1;
	const int wrong = 0;

	// vector
	auto collection = std::make_shared<vector<int>>();
	collection->reserve(collection_size);

	prepare_collection(collection, wrong, last);

	auto matcher = [](const int i) { return find == i; };

	for (int i = 0; i < 3; i++)
		find_element<int>(collection, matcher);

	return 0;
}
