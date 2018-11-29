#ifndef FILE_LOCKER_H_
#define FILE_LOCKER_H_

#include <string>
#include <sys/file.h>

class file_locker
{

	const std::string file;
	int fd;

public:

	file_locker(const std::string& file);
	~file_locker();
	std::string path() const;

};

#endif  // FILE_LOCKER_H_
