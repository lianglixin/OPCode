#pragma once


#include <string>
#include <vector>
#include "DataType.h"


class TestFunc
{
public:
	void to_inst (const std::vector<Byte>& binaryCode, const Instruction & expected, InstSet instSet);
	void to_string (const std::vector<Byte>& binaryCode, const std::string & desc, InstSet instSet);

//	// x86
//public:
//	void to_inst_x86 (
//		const std::vector <Byte> & binaryCode, const Instruction & expected);
//	void to_string_x86 (
//		const std::vector <Byte> & binaryCode,  const std::string & desc);
//
//	// x64
//public:
//	void to_inst_x64 (
//		const std::vector <Byte> & binaryCode, const Instruction & expected);
//	void to_string_x64 (
//		const std::vector <Byte> & binaryCode,  const std::string & desc);

private:
	void testInst (const Instruction & expected, const Instruction & actual);
	void testOperand (const Operand & expected, const Operand & actual);
	void inst_to_string (const Instruction & inst, const std::string & desc);
};