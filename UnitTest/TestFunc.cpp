#include "TestFunc.h"


#include "Disassembler.h"
#include "CppUnitTest.h"
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


void TestFunc::testInst (const Instruction & expected, const Instruction & actual)
{
	//size
	Assert::AreEqual (expected.size, actual.size);

	//name
	Assert::AreEqual (expected.name, actual.name);

	//prefixs
	Assert::AreEqual (expected.prefixs.size (), actual.prefixs.size ());
	for (unsigned i = 0; i < expected.prefixs.size (); i++)
		Assert::AreEqual (expected.prefixs[i], actual.prefixs[i]);

	//operands
	Assert::AreEqual (expected.operands.size (), actual.operands.size ());

	if (expected.operands.size () >= 4)
		Assert::Fail ();

	for (unsigned i = 0; i < expected.operands.size (); i++)
		testOperand (expected.operands[i], actual.operands[i]);
}
void TestFunc::testOperand (
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
		Assert::AreEqual (expected.mem.addr.isRelativeEip, actual.mem.addr.isRelativeEip);
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
void TestFunc::inst_to_string (
	const Instruction & inst, const std::string & desc)
{
	if (desc.empty ())
		return;

	OpcodeToString conv (inst);
	Assert::AreEqual (desc, conv.toString ());
}
void TestFunc::to_string (
	const std::vector <Byte> & binaryCode,  const std::string & desc, InstSet instSet)
{
	Disassembler conv {binaryCode, instSet};
	auto result = conv.conv ();

	inst_to_string (result, desc);
}
void TestFunc::to_inst (
	const std::vector <Byte> & binaryCode, const Instruction & expected, InstSet instSet)
{
	if (binaryCode.size () == 2
		&& binaryCode[0] == 0x48
		&& binaryCode[1] == 0x98)
	{//4898
		instSet = instSet;
	}
	Disassembler conv {binaryCode, instSet};
	auto result = conv.conv ();

	testInst (expected, result);
}

//void TestFunc::to_inst_x86 (
//	const std::vector <Byte> & binaryCode, const Instruction & expected)
//{
//	to_inst (binaryCode, expected, InstSet::x86);
//}
//void TestFunc::to_inst_x64 (
//	const std::vector <Byte> & binaryCode, const Instruction & expected)
//{
//	to_inst (binaryCode, expected, InstSet::x64);
//}
//void TestFunc::to_string_x86 (
//	const std::vector <Byte> & binaryCode,  const std::string & desc)
//{
//	to_string (binaryCode, desc, InstSet::x86);
//}
//void TestFunc::to_string_x64 (
//	const std::vector <Byte> & binaryCode,  const std::string & desc)
//{
//	to_string (binaryCode, desc, InstSet::x64);
//}