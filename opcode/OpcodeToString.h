#pragma once

#include "DataType.h"

class OpcodeToString
{
public:
	OpcodeToString (const Instruction & instruction);
	std::string toString ();

private:
	std::string toString (const std::vector <Prefix> & prefixs, InstructionName name);
	std::string toString (const InstructionName & name);
	std::string toString (const SegName & name);
	std::string toString (const CrName & name);
	std::string toString (const DrName & name);
	std::string toString (const StName & name);
	std::string toString (const RegName & name);
	std::string getMemSizeString (int size);
	std::string getScaleString (int scale);
	int extendSignBit (size_t size, uint32 val);
	std::string getImm6String (InstructionName instructionName, uint32 val, uint32 val_2);
	std::string getImmString (InstructionName instructionName, size_t meanSize, size_t storeSize, uint32 val);
	std::string getDisplacementString (int displacement, bool isForceShowSign);
	std::string toString (const MemAddr & addr);
	size_t getRegSize (RegName name);
	size_t getFirstOperandSize ();
	std::string toString (InstructionName instructionName, const Operand & operand);

private:
	const Instruction & _instruction;
};