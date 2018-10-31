#ifndef DICT_H_
#define DICT_H_

#include <iostream>
#include <string>
#include "pset.h"
using std::string;

class spellchecker
{

	pset<string> set;

public:

	spellchecker(string& dict_file);

	void check_file(string& input_file);
	void check_word(string& word);
	void replace_word(string& word, string& clean_word, string& prefix, string& suffix);
	bool contains(string& word) const;

};

#endif  // DICT_H_
