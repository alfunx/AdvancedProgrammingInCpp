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
		std::vector<string> words;

		std::istringstream ist(line);
		string word;
		while (ist >> word) {
			words.push_back(word);
		}

		for (string& w : words) {
			check_word(w);
		}

		std::ostringstream ost;
		std::copy(words.begin(), words.end(), std::ostream_iterator<string>(ost, " "));
		line = ost.str();
		line.pop_back();
	}
}

void spellchecker::check_word(string& word)
{
	string::iterator si1 = word.begin();
	while (si1 < word.end() && !isalpha(*si1)) ++si1;
	string::iterator si2 = word.end();
	while (si2 >= word.begin() && !isalpha(*si2)) --si2;
	string clean_word = string(si1, si2 + 1);

	if (contains(clean_word))
		return;

	char opt;
	std::cout << "check: " << clean_word << std::endl;
	std::cout << ">>> (a)dd, (i)gnore, (r)eplace? ";
	std::cin >> opt;
	std::cout << std::endl;

	switch (opt) {
		case 'a':
			set.insert(clean_word);
			break;
		case 'r':
			{
				string prefix = string(word.begin(), si1);
				string suffix = string(si2 + 1, word.end());
				replace_word(word, clean_word, prefix, suffix);
				check_word(clean_word);
			}
			break;
		case 'i':
			break;
		default:
			std::cout << "Unknown command, ignoring word." << std::endl;
			std::cout << std::endl;
			break;
	}
}

void spellchecker::replace_word(string& word, string& clean_word, string& prefix, string& suffix)
{
	std::cout << "replace: " << clean_word << std::endl;
	std::cout << ">>> ";
	std::cin >> clean_word;
	std::cout << std::endl;

	std::ostringstream ost;
	ost << prefix << clean_word << suffix;
	word = ost.str();
}

bool spellchecker::contains(string& word) const
{
	return set.find(word) != set.end();
}
