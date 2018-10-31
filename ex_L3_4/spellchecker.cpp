#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include "spellchecker.h"
#include "pvector.h"
using std::string;

spellchecker::spellchecker(string& dict_file) :
	set(dict_file)
{
	/* void */
}

void spellchecker::check_file(string& input_file)
{
	pvector<string> lines(input_file);

	for (string& line : lines) {
		check_line(line);
	}
}

void spellchecker::check_line(string& line)
{
	string::iterator a = line.begin();
	string::iterator b = line.begin();

	while (next_word(a, b, line.end())) {
		string word(a, b);

		if (found(word) || ignored(word)) {
			a = b;
			continue;
		}

		char opt;
		std::cout << "check: " << word << std::endl;
		std::cout << ">>> (a)dd, (i)gnore, (r)eplace? ";
		std::cin >> opt;
		std::cout << std::endl;

		switch (opt) {
			case 'a':
				record(word);
				break;
			case 'i':
				ignore(word);
				break;
			case 'r':
				correct(line, a, b);
				continue;
			default:
				std::cout << "Unknown command!" << std::endl;
				std::cout << std::endl;
				continue;
		}

		// check next word
		a = b;
	}
}

void spellchecker::correct(string& line, string::iterator& a, string::iterator& b)
{
	string word;
	std::cout << "replace: " << string(a, b) << std::endl;
	std::cout << ">>> ";
	std::cin >> word;
	std::cout << std::endl;

	std::ostringstream ost;
	ost << string(line.begin(), a) << word << string(b, line.end());
	line = ost.str();

	a = line.begin();
	b = line.begin();
}

bool spellchecker::found(string word) const
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	return set.find(word) != set.end();
}

bool spellchecker::ignored(string word) const
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	return ignored_set.find(word) != ignored_set.end();
}

void spellchecker::record(string& word)
{
	set.insert(word);
}

void spellchecker::ignore(string& word)
{
	ignored_set.insert(word);
}

bool spellchecker::next_word(string::iterator& a, string::iterator& b, const string::iterator& e)
{
	// find beginning of word
	while (a < e && !isalpha(*a)) ++a;
	b = a;

	// find space (after end of word)
	while (b < e && !isspace(*b)) ++b;

	// move back to end of word (to avoid special chars)
	while (b - 1 > a && !isalpha(*(b - 1))) --b;

	return a != e;
}
