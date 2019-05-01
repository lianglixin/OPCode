#pragma once

#include "DataType.h"
#include "Tools.h"

class ByteReader
{
public:
	ByteReader (const std::vector <Byte> & vec);

public:
	enum class ExceptionType
	{
		TOO_SHORT,	// when read
	};

public:
	template <typename T>
	T read (bool isReorder = true);
	size_t getReadedSize () { return _readedSize; }
	void reset (size_t begin) { _begin = begin; }

private:
	size_t getUnreadedSize ();

private:
	const std::vector <Byte> & _vec;
	size_t _readedSize {};
	size_t _begin {};
};


template <typename T>
T ByteReader::read (bool isReorder)
{
	const size_t size = sizeof (T);
	if (getUnreadedSize () < size)
		throw Exception {(int) ExceptionType::TOO_SHORT};

	T re = *(T*) & _vec[_begin + _readedSize];		//auto reorder
	_readedSize += size;

	if (false == isReorder)
		re = Tools::reorder (re);

	return re;
}