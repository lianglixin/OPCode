#pragma once


#include "DataType.h"
#include <map>
#include <functional>


class InstructionReader;


class OpcodeTable
{
public:
	OpcodeMap getOpcodeMap (InstructionReader & reader);

private:
	OpcodeMap getOpcodeMapWithout66 (InstructionReader & reader);
	const OpcodeMap & getOpcodeMapByEscape (InstructionReader & reader);
	const OpcodeMain & getOpcodeMain (InstructionReader & reader);
	const OpcodeMap & getOpcodeMap_DX_11XXXXXX (Byte opcode, Byte modrm);
	const OpcodeMap & getOpcodeMap_DX_non_11XXXXXX (Byte opcode, Byte item);	//item: reg field
	const OpcodeMain & getOpcodeMain_XX (Byte opcode, bool is_x64, bool hasRexB, bool hasRexW, bool hasPrefixOperandSize);
	const OpcodeMain & getOpcodeMain_0FXX (Byte opcode, bool is_x64);
	const OpcodeGroup & getOpcodeGroup (GroupName name, Byte item);	//item: reg field

private:
	static const std::map <Byte, OpcodeMain> _main;
	static const std::map <Byte, OpcodeMain> _main_diff_x64;
	static const std::map <Byte, OpcodeMain> _main_diff_RexB;
	static const std::map <Byte, OpcodeMain> _main_diff_RexW;
	static const std::map <Byte, OpcodeMain> _main_diff_PrefixOperandSize;
	static const std::map <Byte, OpcodeMain> _main_0FXX;
	static const std::map <Byte, OpcodeMain> _main_0FXX_diff_x64;
	using GroupItem = std::map <Byte, OpcodeGroup>;
	static const std::map <GroupName, GroupItem> _group;
	static const std::map <Byte /*opcode*/, std::map <Byte /*modrm*/, OpcodeMap>> _escape_11XXXXXX;
	static const std::map <Byte /*opcode*/, std::map <Byte /*item*/, OpcodeMap>> _escape_non_11XXXXXX;
};