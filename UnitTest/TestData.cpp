#include "TestData.h"



void TestData::testBinaryCodeToInstruction (
	std::function <void (
		const std::vector <Byte> & binaryCode,
		Instruction expected)> callback)
{
	for (auto & one : _instructions_x86)
		callback (one.binaryCode, one.inst);
}

void TestData::testInstructionToString (
	std::function <void (
		const std::vector <Byte> & binaryCode,
		const std::string & desc)> callback)
{
	for (auto & one : _instructions_x86)
		callback (one.binaryCode, one.desc);
}
void TestData::testBinaryCodeToString_MultiInstructions (
	std::function <void (
		const std::string & strBinaryCode,
		const std::string & descs)> callback)
{
	for (auto & instruction : _instructions)
		callback (instruction.opcode, instruction.descs);
}
void TestData::to_inst_x64 (
	std::function <void (
		const std::vector <Byte> & binaryCode,
		Instruction expected)> callback)
{
	for (auto & one : _instructions_x64)
		callback (one.binaryCode, one.inst);
}
void TestData::to_string_x64 (
	std::function <void (
		const std::vector <Byte> & binaryCode,
		const std::string & desc)> callback)
{
	for (auto & one : _instructions_x64)
		callback (one.binaryCode, one.desc);
}