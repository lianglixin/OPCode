#pragma once

#include "OpcodeTable.h"
#include "InstructionReader.h"


// convert binary code to assembly
class Disassembler
{
public:
	Disassembler (const std::vector <Byte> & binaryCode, InstSet instSet = InstSet::x86);
	Instruction conv (unsigned begin = 0);

private:
	Byte getBase ()		{ return _reader.getBase (); }
	Byte getIndex ()	{ return _reader.getIndex (); }
	Byte getScale ()	{ return _reader.getScale (); }
	Byte getMod ()		{ return _reader.getMod (); }
	Byte getReg ()		{ return _reader.getReg (); }
	Byte getSeg ()		{ return _reader.getSeg (); }
	Byte getRM ()		{ return _reader.getRM (); }
	bool is_x86 ()		{ return _reader.is_x86 (); }
	bool is_x64 ()		{ return _reader.is_x64 (); }
	bool hasRex ()		{ return _reader.hasRex (); }
	Byte getRexB ()		{ return _reader.getRexB (); }
	Byte getRexR ()		{ return _reader.getRexR (); }
	Byte getRexX ()		{ return _reader.getRexX (); }
	Byte getRexW ()		{ return _reader.getRexW (); }
	Byte getRexIndex ();
	OpcodeMap getOpcodeMap ();
	int getReadableScale ();
	SegName getSegName (Byte b);
	RegName getRegName (Byte b, int size, bool isUseSpl = false, Byte exIndex = 0);
	CrName getCrName (Byte b);
	DrName getDrName (Byte b);
	unsigned getOperandSize (OperandDesc::Size desc, OperandType type);
	unsigned getOperandSize (OperandDesc::Size desc);
	SegName getSegName (RegName base);
	RegName getRegNameByBase ();
	RegName getRegNameByIndex ();
	RegName getRegNameByRM ();
	RegName getRegNameByRM (unsigned size);
	RegName getRegNameByReg (unsigned size);
	void parseSIB (MemAddr * addr);
	void parseAddrByModrm (MemAddr * addr);
	void parseCrOperand (const OperandDesc & desc, Operand* operand);
	void parseDrOperand (const OperandDesc & desc, Operand* operand);
	void parseRegOperand (const OperandDesc & desc, Operand* operand, bool isRM);
	void parseSegOperand (const OperandDesc & desc, Operand* operand);
	void parseDisplaceOperand (const OperandDesc & desc, Operand* operand);
	void parseFixOperand (const OperandDesc & desc, Operand* operand);
	void parseRegxXXOperand (const OperandDesc & desc, Operand* operand);
	void parseRegrXXrXOperand (const OperandDesc & desc, Operand* operand);
	void parseImmOperand (const OperandDesc & desc, Operand* operand);
	void parseMemOperand (const OperandDesc & desc, Operand* operand);
	void parseRMOperand (const OperandDesc & desc, Operand* operand);
	void parseSiOperand (const OperandDesc & desc, Operand* operand);
	void parseDiOperand (const OperandDesc & desc, Operand* operand);
	void parseOperand (const OperandDesc & desc, Operand* operand);

private:
	InstructionReader _reader;
	OpcodeTable _table;
};