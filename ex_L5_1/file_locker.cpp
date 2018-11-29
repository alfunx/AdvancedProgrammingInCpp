#include "file_locker.h"

file_locker::file_locker(const std::string& file) : file(file)
{
	fd = open(file.c_str(), O_RDWR | O_CREAT);
	flock(fd, LOCK_EX);
}

file_locker::~file_locker()
{
	flock(fd, LOCK_UN);
}

std::string file_locker::path() const
{
	return file;
}
