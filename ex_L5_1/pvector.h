#ifndef PVECTOR_H_
#define PVECTOR_H_

#include <fstream>
#include <vector>
#include "file_locker.h"
#include "persistence_traits.h"

template<typename T, typename P=persistence_traits<T>>
class pvector : public std::vector<T>
{

	const file_locker file;

	void load()
	{
		std::ifstream ifs(file.path());

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
		std::ofstream ofs(file.path());

		for (const T& t : *this) {
			P::write(ofs, t);
		}
	}

public:

	pvector(const std::string& file) : file(file)
	{
		load();
	}

	~pvector()
	{
		save();
	}

};

#endif  // PVECTOR_H_
