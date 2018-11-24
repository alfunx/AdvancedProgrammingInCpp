#ifndef PERSISTENCE_TRAITS_H_
#define PERSISTENCE_TRAITS_H_

#include <fstream>

template<typename T>
struct persistence_traits
{

	static void read(std::ifstream& ifs, T& t)
	{
		ifs >> t;
	}

	static void write(std::ofstream& ofs, const T t)
	{
		ofs << t << std::endl;
	}

};

template<>
struct persistence_traits<std::string>
{

	static void read(std::ifstream& ifs, std::string& s)
	{
		std::getline(ifs, s);
	}

	static void write(std::ofstream& ofs, const std::string& s)
	{
		ofs << s << std::endl;
	}

};

#endif  // PERSISTENCE_TRAITS_H_
