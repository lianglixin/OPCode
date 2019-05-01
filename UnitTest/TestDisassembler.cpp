#include "TestDisassembler.h"


#include "CppUnitTest.h"
#include "Tools.h"
#include "Analysis.h"
#include "Disassembler.h"
#include "OpcodeToString.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace Microsoft{ namespace VisualStudio {namespace CppUnitTestFramework
{
#define SS(A)	template<> inline std::wstring ToString <A> (const A & t) { return L""; }
	SS (RegName);
	SS (SegName);
	SS (InstructionName);
	SS (OperandType);
	SS (Prefix);
#undef SS
}}}


void TestDisassembler::testBinaryCodeToInstruction (
	const std::vector <Byte> & binaryCode,
	const Instruction & expected)
{
	Disassembler conv {binaryCode};
	auto res = conv.conv ();

	//size
	assert (binaryCode.size () == expected.size);
	Assert::AreEqual (expected.size, res.size);

	//name
	Assert::AreEqual (expected.name, res.name);

	//prefixs
	Assert::AreEqual (expected.prefixs.size (), res.prefixs.size ());
	for (unsigned i = 0; i < expected.prefixs.size (); i++)
		Assert::AreEqual (expected.prefixs[i], res.prefixs[i]);

	//operands
	Assert::AreEqual (expected.operands.size (), res.operands.size ());

	if (expected.operands.size () >= 4)
		Assert::Fail ();

	for (unsigned i = 0; i < expected.operands.size (); i++)
		testOperand (expected.operands[i], res.operands[i]);
}
void TestDisassembler::testOperand (
	const Operand & expected, const Operand & actual)
{
	Assert::AreEqual (expected.type, actual.type);

	if (expected.type == OperandType::REG)
	{
		Assert::AreEqual (expected.reg.name, actual.reg.name);
		return;
	}

	if (expected.type == OperandType::SEG)
	{
		Assert::AreEqual (expected.seg.name, actual.seg.name);
		return;
	}

	if (expected.type == OperandType::MEM)
	{
		Assert::AreEqual (expected.mem.addr.index, actual.mem.addr.index);
		Assert::AreEqual (expected.mem.addr.base, actual.mem.addr.base);
		Assert::AreEqual (expected.mem.addr.displacement, actual.mem.addr.displacement);
		if (expected.mem.addr.index != RegName::NONE)
			Assert::AreEqual (expected.mem.addr.scale, actual.mem.addr.scale);
		return;
	}

	if (expected.type == OperandType::IMM)
	{
		Assert::AreEqual (expected.imm.size, actual.imm.size);
		Assert::AreEqual (expected.imm.val, actual.imm.val);
		return;
	}

	Assert::Fail ();
}
void TestDisassembler::testInstructionToString (
	const std::vector <Byte> & binaryCode,  const std::string & desc)
{
	Disassembler conv {binaryCode};
	auto res = conv.conv ();

	testDesc (res, desc);
}
void TestDisassembler::testDesc (
	const Instruction & inst, const std::string & desc)
{
	if (desc.empty ())
		return;

	OpcodeToString conv (inst);
	Assert::AreEqual (desc, conv.toString ());
}
void TestDisassembler::testBinaryCodeToString_MultiInstructions (
	const std::string & strBinaryCode,
	const std::string & descs)
{
	auto binaryCode = Tools::toVecOpcode (strBinaryCode);

	test2 (binaryCode, descs);
}
void TestDisassembler::test2 (
	const std::vector <Byte> & opcode,
	const std::string & desc)
{
	unsigned index {};
	std::string actual;
	std::vector <std::string> strs_expected =
		getStrs (desc);

	while (1)
	{
		if (index == opcode.size ())
			break;
		Disassembler conv (opcode);
		auto instruction = conv.conv (index);
		OpcodeToString conv2 {instruction};
		actual += conv2.toString ();
		actual += '\n';
		index += instruction.size;
		if (index > opcode.size ())
			Assert::Fail ();
	}

	if (desc.empty ())
		return;

	std::vector<std::string> strs_actual =
		getStrs (actual);

	//Following sames as Assert::AreEqual (desc, actual);
	{
		for (unsigned i = 0; ; i++)
		{
			if (i >= strs_expected.size ())
				break;
			if (i >= strs_actual.size ())
				break;

			Assert::AreEqual (strs_expected[i], strs_actual[i]);
		}
		Assert::AreEqual (strs_expected.size (), strs_actual.size ());
	}

	Assert::AreEqual (desc, actual);
}
std::vector <std::string> TestDisassembler::getStrs (const std::string & str, char c)
{
	std::vector <std::string> strs;

	unsigned index {};

	while (1)
	{
		if (index >= str.length ())
			break;

		std::string one;

		while (1)
		{
			if (index >= str.length ())
				break;
			if (str[index] == c)
			{
				index ++;
				break;
			}

			one += str[index];
			index ++;
		}

		strs.push_back (one);
	}

	return strs;
}
