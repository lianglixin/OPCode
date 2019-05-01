#pragma once

#include <string>
#include <vector>
#include "DataType.h"

class TestDisassembler
{
public:
	void testBinaryCodeToInstruction (
		const std::vector <Byte> & binaryCode, const Instruction & expected);
	void testInstructionToString (
		const std::vector <Byte> & binaryCode,  const std::string & desc);
	void testBinaryCodeToString_MultiInstructions (
		const std::string & strBinaryCode, const std::string & descs);

private:
	void testOperand (const Operand & expected, const Operand & actual);
	void testDesc (const Instruction & inst, const std::string & desc);
	void test2 (const std::vector <Byte> & opcode, const std::string & desc);
	std::vector <std::string> getStrs (const std::string & str, char c = '\n');
};