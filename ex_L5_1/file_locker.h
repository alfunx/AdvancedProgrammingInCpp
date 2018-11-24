#ifndef FILE_LOCKER_H_
#define FILE_LOCKER_H_

#include <string>
#include <sys/file.h>

class file_locker
{

	const std::string file;
	int fd;

public:

	file_locker(const std::string& file) : file(file)
	{
		fd = open(file.c_str(), O_RDWR);
		flock(fd, LOCK_EX);
	}

	~file_locker()
	{
		flock(fd, LOCK_UN);
	}

	std::string path() const
	{
		return file;
	}

};

#endif  // FILE_LOCKER_H_
