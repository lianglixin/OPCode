#pragma once

//#pragma comment (lib, "opcode.lib")

#include <string>
#include "DataType.h"


class Tools
{
public:
	template <typename T, int size = sizeof (T)>
	static T reorder (T val)
	{
		static_assert (size == 1 ||
					   size == 2 ||
					   size == 4, "");

		if (size == 1)
			return val;

		if (size == 2)
		{
			char* p = (char*) & val;
			std::swap (p[0], p[1]);
			return val;
		}
		if (size == 4)
		{
			char* p = (char*) & val;
			std::swap (p[0], p[3]);
			std::swap (p[1], p[2]);
			return val;
		}

//		assert (0);
	}
	static Byte get67Bits (Byte b)
	{
		return (b & 0xc0) >> 6;
	}
	static Byte get345Bits (Byte b)
	{
		return (b & 0x38) >> 3;
	}
	static Byte get012Bits (Byte b)
	{
		return b & 0x07;
	}
	static Byte getBit (Byte b, int c)
	{
		if (b & (1 << c))
			return 1;
		else
			return 0;
	}
	static std::string disassemble (std::string str, bool isNote, InstSet instSet = InstSet::x86);
	static std::vector <Byte> toVecOpcode (const std::string & strOpcode);
	static std::vector <Instruction> toInsts (const std::vector <Byte> & vecOpcode, InstSet instSet = InstSet::x86);
	static std::vector <std::pair <size_t, NoteString>> toNoteStrings (const std::vector <Note> & notes);
};