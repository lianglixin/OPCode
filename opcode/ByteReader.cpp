#include "ByteReader.h"


ByteReader::ByteReader (const std::vector <Byte> & vec)
	: _vec {vec}
{
}
size_t ByteReader::getUnreadedSize ()
{
	if (_begin + _readedSize >= _vec.size ())
		return 0;

	return _vec.size () - (_begin + _readedSize);
}