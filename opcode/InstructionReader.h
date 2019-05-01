#pragma once

#include "DataType.h"
#include "ByteReader.h"

class InstructionReader
{
public:
	InstructionReader (const std::vector <Byte> & binaryCode, InstSet instSet);

public:
	void reset (size_t begin);
	bool isPrefixExist (Prefix prefix);
	SegName getSegPrefix ();
	Byte readOpcode ();
	size_t getOpcodeReadedSize ();
	Byte getOpcode (size_t index);
	Byte getMod ();
	Byte getReg ();
	Byte getSeg ();
	Byte getRM ();
	Byte getBase ();
	Byte getIndex ();
	Byte getScale ();
	int getDisplacement (int size, bool noModrm = false);
//	uint32 getImm (int size);
	void readImm (int size, uint32* val, uint32* val_2);
//	uint32 readImm (int size);
	size_t getReadedSize ();
	Byte getModrm ();
	std::vector <Prefix> getPrefixs ();
	bool is_x86 ();
	bool is_x64 ();
	bool hasRex ();
	bool hasRexB ();
	bool hasRexW ();
	Byte getRexB ();
	Byte getRexR ();
	Byte getRexX ();
	Byte getRexW ();

private:
	template <typename T>
	T readBytes (bool isReorder = true);
	Byte getSib ();
	bool trySaveAsPrefix (Byte b);

private:
	struct
	{
		bool hasOperandSize = false;
		bool hasAddressSize = false;
		bool hasSeg = false;
		SegName seg;
		bool hasLockRepeat = false;
		Prefix lockRepeat;
		bool hasRex = false;
		Byte rex {};
	} _prefix {};

	struct
	{
		bool isReaded = false;
		std::vector <Byte> vec;
	} _opcode {};

	struct
	{
		bool isReaded = false;
		Byte val;
	} _modrm {}, _sib {};

	struct
	{
		bool isReaded = false;
		int size;
		int val;
	} _displacement {};

	struct
	{
		bool isReaded = false;
//		int size;
//		uint32 val;
	} _imm {};

	ByteReader _byteReader;
	InstSet _instSet {};
};