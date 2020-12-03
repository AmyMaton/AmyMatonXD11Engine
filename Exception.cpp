#include "Exception.h"
#include <sstream>

MyException::MyException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* MyException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< OriginString();
	BufferUsed = oss.str();
	return BufferUsed.c_str();
}

const char* MyException::GetType() const noexcept
{
	return "MyException";
}

int MyException::GetLine() const noexcept
{
	return line;
}

const std::string& MyException::GetFile() const noexcept
{
	return file;
}

std::string MyException::OriginString() const noexcept
{
	std::ostringstream oss;
	oss << "The File " << file << std::endl
		<< "The Line " << line;
	return oss.str();
}