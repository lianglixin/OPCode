#pragma once

#include "Disassembler.h"

class TestData
{
public:
	void testBinaryCodeToInstruction (
		std::function <void (
			const std::vector <Byte> & binaryCode,
			Instruction expected)> callback);
	void testInstructionToString (
		std::function <void (
			const std::vector <Byte> & binaryCode,
			const std::string & desc)> callback);
	void testBinaryCodeToString_MultiInstructions (
		std::function <void (
			const std::string & strBinaryCode,
			const std::string & descs)> callback);

	// x64
public:
	void to_inst_x64 (
		std::function <void (
			const std::vector <Byte> & binaryCode,
			Instruction expected)> callback);
	void to_string_x64 (
		std::function <void (
			const std::vector <Byte> & binaryCode,
			const std::string & desc)> callback);

private:

	class ExpectedInstruction
	{
	public:
		std::vector <Byte> binaryCode;
		std::string desc;
		Instruction inst;

	public:
		ExpectedInstruction (
			std::string opcode,
			std::string desc,
			Instruction inst)
			: desc {desc}
			, inst {inst}
		{
			binaryCode = Tools::toVecOpcode (opcode);
			this->inst.size = binaryCode.size ();
		}
		ExpectedInstruction (
			std::string opcode,
			std::string desc,
			InstructionName name)
			: ExpectedInstruction {opcode, desc, Instruction {name}}
		{
		}
		ExpectedInstruction (
			std::string opcode,
			std::string desc,
			InstructionName name,
			const Operand & operand_0)
			: ExpectedInstruction {opcode, desc, Instruction {name, {operand_0}}}
		{
		}
		ExpectedInstruction (
			std::string opcode,
			std::string desc,
			InstructionName name,
			const Operand & operand_0,
			const Operand & operand_1)
			: ExpectedInstruction {opcode, desc, Instruction {name, {operand_0, operand_1}}}
		{
		}
		ExpectedInstruction (
			std::string opcode,
			std::string desc,
			InstructionName name,
			const Operand & operand_0,
			const Operand & operand_1,
			const Operand & operand_2)
			: ExpectedInstruction {opcode, desc, Instruction {name, {operand_0, operand_1, operand_2}}}
		{
		}
	};
	class ExpectedInstructions
	{
	public:
		std::string opcode;
		std::string descs;
	};
private:
	static const std::vector <ExpectedInstruction> _instructions_x86;
	static const std::vector <ExpectedInstruction> _instructions_x64;
	static const std::vector <ExpectedInstructions> _instructions;
};