#ifndef PVECTOR_H_
#define PVECTOR_H_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template<typename T>
class pvector : public std::vector<T>
{

	const std::string f;

	void load()
	{
		std::ifstream ifs(f);

		for (;;) {
			T t;
			ifs >> t;
			if (!ifs.good())
				break;
			std::vector<T>::push_back(t);
		}
	}

	void save()
	{
		std::ofstream ofs(f);

		for (const T &t : *this) {
			ofs << t << std::endl;
		}
	}

public:

	pvector(std::string&& file) : f(file)
	{
		load();
		std::cout << "Constructor called." << std::endl;
	}

	~pvector()
	{
		save();
		std::cout << "Destructor called." << std::endl;
	}

};

#endif  // PVECTOR_H_
