#ifndef PVECTOR_H_
#define PVECTOR_H_

#include "persistence_traits.h"
#include <fstream>
#include <vector>

template<typename T, typename P=persistence_traits<T>>
class pvector : public std::vector<T>
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
			std::vector<T>::push_back(t);
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

	pvector(std::string&& file) : file(file)
	{
		load();
	}

	~pvector()
	{
		save();
	}

};

#endif  // PVECTOR_H_