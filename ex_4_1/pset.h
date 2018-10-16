#ifndef PSET_H_
#define PSET_H_

#include "persistence_traits.h"
#include <fstream>
#include <set>

template<typename T, typename P=persistence_traits<T>>
class pset : public std::set<T>
{

	const std::string file;

	void load()
	{
		std::ifstream ifs(file);

		for (;;) {
			T t;
			P::read(ifs, t);
			if (!ifs.good())
				break;
			std::set<T>::insert(t);
		}
	}

	void save()
	{
		std::ofstream ofs(file);

		for (const T &t : *this) {
			P::write(ofs, t);
		}
	}

public:

	pset(std::string&& file) : file(file)
	{
		load();
	}

	~pset()
	{
		save();
	}

};

#endif  // PSET_H_
