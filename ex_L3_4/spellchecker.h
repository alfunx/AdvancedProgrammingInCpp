#ifndef SPELLCHECKER_H_
#define SPELLCHECKER_H_

#include <iostream>
#include <string>
#include "pset.h"
using std::string;

class spellchecker
{

	pset<string> set;
	std::set<string> ignored_set;

public:

	spellchecker(string& dict_file);

	void check_file(string& input_file);
	void check_line(string& line);

	void correct(string& line, string::iterator& a, string::iterator& b);
	bool found(string word) const;
	bool ignored(string word) const;
	void record(string& word);
	void ignore(string& word);

	static bool next_word(string::iterator& a, string::iterator& b, const string::iterator& e);

};

#endif  // SPELLCHECKER_H_
