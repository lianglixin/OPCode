#include "Disassembler.h"

#include <cassert>
#include <map>

OpcodeMap Disassembler::getOpcodeMap ()
{
	return _table.getOpcodeMap (_reader);
}
//return RexX(3) + Index(0-2)
Byte Disassembler::getRexIndex ()
{
	if (hasRex ())
	{
		return getIndex () + (getRexX () << 3);
	}
	else
		return getIndex ();
}
int Disassembler::getReadableScale ()
{
	Byte scale = getScale ();
	assert (scale >= 0x0 && scale <= 0x3);
	return 1 << scale;
}
SegName Disassembler::getSegName (Byte b)
{
	assert (b >= 0 && b <= 0x5);

	static SegName arr[6]
	{
		SegName::ES,
		SegName::CS,
		SegName::SS,
		SegName::DS,
		SegName::FS,
		SegName::GS,
	};

	return arr[b];
}
RegName Disassembler::getRegName (Byte b, int size, bool isUseSpl, Byte exIndex)
{
	assert (b >= 0 && b <= 7);
	if (is_x86 ())
		assert (size == 1 || size == 2 || size == 4);
	else	//x64
		assert (size == 1 || size == 2 || size == 4 || size == 8);
	if (is_x86 ())
		assert (0 == exIndex);
	else	//x64
		assert (0 == exIndex || 1 == exIndex);

	RegName (*arr)[4] {};
	if (false == isUseSpl)
	{
		static RegName arr0[16][4]
		{
			RegName::AL  , RegName::AX  , RegName::EAX , RegName::RAX,
			RegName::CL  , RegName::CX  , RegName::ECX , RegName::RCX,
			RegName::DL  , RegName::DX  , RegName::EDX , RegName::RDX,
			RegName::BL  , RegName::BX  , RegName::EBX , RegName::RBX,
			RegName::AH  , RegName::SP  , RegName::ESP , RegName::RSP,
			RegName::CH  , RegName::BP  , RegName::EBP , RegName::RBP,
			RegName::DH  , RegName::SI  , RegName::ESI , RegName::RSI,
			RegName::BH  , RegName::DI  , RegName::EDI , RegName::RDI,
			RegName::R8B , RegName::R8W , RegName::R8D , RegName::R8 ,
			RegName::R9B , RegName::R9W , RegName::R9D , RegName::R9 ,
			RegName::R10B, RegName::R10W, RegName::R10D, RegName::R10,
			RegName::R11B, RegName::R11W, RegName::R11D, RegName::R11,
			RegName::R12B, RegName::R12W, RegName::R12D, RegName::R12,
			RegName::R13B, RegName::R13W, RegName::R13D, RegName::R13,
			RegName::R14B, RegName::R14W, RegName::R14D, RegName::R14,
			RegName::R15B, RegName::R15W, RegName::R15D, RegName::R15,
		};
		arr = arr0;
	}
	else
	{
		static RegName arr1[16][4]
		{
			RegName::AL  , RegName::AX  , RegName::EAX , RegName::RAX,
			RegName::CL  , RegName::CX  , RegName::ECX , RegName::RCX,
			RegName::DL  , RegName::DX  , RegName::EDX , RegName::RDX,
			RegName::BL  , RegName::BX  , RegName::EBX , RegName::RBX,
			RegName::SPL , RegName::SP  , RegName::ESP , RegName::RSP,
			RegName::BPL , RegName::BP  , RegName::EBP , RegName::RBP,
			RegName::SIL , RegName::SI  , RegName::ESI , RegName::RSI,
			RegName::DIL , RegName::DI  , RegName::EDI , RegName::RDI,
			RegName::R8B , RegName::R8W , RegName::R8D , RegName::R8 ,
			RegName::R9B , RegName::R9W , RegName::R9D , RegName::R9 ,
			RegName::R10B, RegName::R10W, RegName::R10D, RegName::R10,
			RegName::R11B, RegName::R11W, RegName::R11D, RegName::R11,
			RegName::R12B, RegName::R12W, RegName::R12D, RegName::R12,
			RegName::R13B, RegName::R13W, RegName::R13D, RegName::R13,
			RegName::R14B, RegName::R14W, RegName::R14D, RegName::R14,
			RegName::R15B, RegName::R15W, RegName::R15D, RegName::R15,
		};
		arr = arr1;
	}

	static int tmp[9] 
	{
		-1,	//unused
		0,
		1,
		-1,	//unused
		2,
		-1,	//unused
		-1,	//unused
		-1,	//unused
		3,
	};

	b += (exIndex << 3);
	return arr[b][tmp[size]];

#if 0
	if (false == isUseSpl)
	{
		static RegName arr[8][4]
		{
			RegName::AL, RegName::AX, RegName::EAX, RegName::RAX,
			RegName::CL, RegName::CX, RegName::ECX, RegName::RCX,
			RegName::DL, RegName::DX, RegName::EDX, RegName::RDX,
			RegName::BL, RegName::BX, RegName::EBX, RegName::RBX,
			RegName::AH, RegName::SP, RegName::ESP, RegName::RSP,
			RegName::CH, RegName::BP, RegName::EBP, RegName::RBP,
			RegName::DH, RegName::SI, RegName::ESI, RegName::RSI,
			RegName::BH, RegName::DI, RegName::EDI, RegName::RDI,
		};

		static int tmp[9] 
		{
			-1,	//unused
			0,
			1,
			-1,	//unused
			2,
			-1,	//unused
			-1,	//unused
			-1,	//unused
			3,
		};

		return arr[b][tmp[size]];
	}
	else
	{
		static RegName arr[16][4]
		{
			RegName::AL  , RegName::AX  , RegName::EAX , RegName::RAX,
			RegName::CL  , RegName::CX  , RegName::ECX , RegName::RCX,
			RegName::DL  , RegName::DX  , RegName::EDX , RegName::RDX,
			RegName::BL  , RegName::BX  , RegName::EBX , RegName::RBX,
			RegName::SPL , RegName::SP  , RegName::ESP , RegName::RSP,
			RegName::BPL , RegName::BP  , RegName::EBP , RegName::RBP,
			RegName::SIL , RegName::SI  , RegName::ESI , RegName::RSI,
			RegName::DIL , RegName::DI  , RegName::EDI , RegName::RDI,
			RegName::R8B , RegName::R8W , RegName::R8D , RegName::R8 ,
			RegName::R9B , RegName::R9W , RegName::R9D , RegName::R9 ,
			RegName::R10B, RegName::R10W, RegName::R10D, RegName::R10,
			RegName::R11B, RegName::R11W, RegName::R11D, RegName::R11,
			RegName::R12B, RegName::R12W, RegName::R12D, RegName::R12,
			RegName::R13B, RegName::R13W, RegName::R13D, RegName::R13,
			RegName::R14B, RegName::R14W, RegName::R14D, RegName::R14,
			RegName::R15B, RegName::R15W, RegName::R15D, RegName::R15,
		};

		static int tmp[9] 
		{
			-1,	//unused
			0,
			1,
			-1,	//unused
			2,
			-1,	//unused
			-1,	//unused
			-1,	//unused
			3,
		};

		b += exIndex << 3;
		return arr[b][tmp[size]];
	}
#endif
}
CrName Disassembler::getCrName (Byte b)
{
	assert (b >= 0 && b <= 0x4);

	static CrName arr[5]
	{
		CrName::CR0,
		CrName::CR1,
		CrName::CR2,
		CrName::CR3,
		CrName::CR4,
	};

	return arr[b];
}
DrName Disassembler::getDrName (Byte b)
{
	assert (b >= 0 && b <= 0x7);

	static DrName arr[8]
	{
		DrName::DR0,
		DrName::DR1,
		DrName::DR2,
		DrName::DR3,
		DrName::DR4,
		DrName::DR5,
		DrName::DR6,
		DrName::DR7,
	};

	return arr[b];
}
//notice: will not fill the displacement field of the addr sometimes.
void Disassembler::parseSIB (MemAddr* addr)
{
	addr->scale = getReadableScale ();

	if (getRexIndex () == 0x4)
		addr->index = RegName::NONE;
	else
		addr->index = getRegNameByIndex ();

	if (getMod () != 0x0)
	{
		assert (getMod () == 0x1 ||getMod () == 0x2);
		addr->base = getRegNameByBase ();			//normal
	}
	else
	{
		if (getBase () != 0x5)
			addr->base = getRegNameByBase ();		//normal
		else
		{
			// treat 0x5 as disp32
			addr->base = RegName::NONE;
			addr->displacement = _reader.getDisplacement (4);
		}
	}
}
void Disassembler::parseCrOperand (
	const OperandDesc & desc, Operand* operand)
{
	assert (desc.type == OperandDesc::Type::C);

	operand->type = OperandType::CR;
	operand->cr.name = getCrName (getReg ());
}
void Disassembler::parseDrOperand (
	const OperandDesc & desc, Operand* operand)
{
	assert (desc.type == OperandDesc::Type::D);

	operand->type = OperandType::DR;
	operand->dr.name = getDrName (getReg ());
}
void Disassembler::parseRegOperand (
	const OperandDesc & desc, Operand* operand, bool isRM)
{
	if (isRM)
		assert (desc.type == OperandDesc::Type::E ||
				desc.type == OperandDesc::Type::R && getMod () == 0b11);
	else
		assert (desc.type == OperandDesc::Type::G);

	operand->type = OperandType::REG;
	unsigned size = getOperandSize (desc.size, OperandType::REG);
	Byte regIndex = (isRM ? getRM () : getReg ());
#if 0
	if (is_x86 ())
		operand->reg.name = getRegName (regIndex, size);
	else	//x64
	{
		Byte exIndex = (isRM ? getRexB () : getRexR ());
		operand->reg.name = getRegName (regIndex, size, hasRex (), exIndex);
	}
#endif
	if (isRM)
		operand->reg.name = getRegNameByRM (size);
	else
		operand->reg.name = getRegNameByReg (size);
}
void Disassembler::parseSegOperand (const OperandDesc & desc,
							  Operand* operand)
{
	assert (desc.type == OperandDesc::Type::S);
	operand->type = OperandType::SEG;
	operand->seg.name = getSegName (getSeg ());
}
void Disassembler::parseDisplaceOperand (const OperandDesc & desc,
								   Operand* operand)
{
	assert (desc.type == OperandDesc::Type::O);

	operand->type = OperandType::MEM;
	operand->mem.size = getOperandSize (desc.size);
	operand->mem.addr.setByDisplacement (
		_reader.getDisplacement (4, true));
	operand->mem.seg = getSegName (operand->mem.addr.base);
}
void Disassembler::parseSiOperand (const OperandDesc & desc,
							  Operand* operand)
{
	assert (desc.type == OperandDesc::Type::X);
	operand->type = OperandType::MEM;
	operand->mem.size = getOperandSize (desc.size);
	if (is_x86 ())
		operand->mem.addr.setByReg (RegName::ESI);
	else	//x64
		operand->mem.addr.setByReg (RegName::RSI);
	operand->mem.seg = SegName::DS;
}
void Disassembler::parseDiOperand (const OperandDesc & desc,
							  Operand* operand)
{
	assert (desc.type == OperandDesc::Type::Y);
	operand->type = OperandType::MEM;
	operand->mem.size = getOperandSize (desc.size);
	if (is_x86 ())
		operand->mem.addr.setByReg (RegName::EDI);
	else	//x64
		operand->mem.addr.setByReg (RegName::RDI);
	operand->mem.seg = SegName::ES;
}
void Disassembler::parseFixOperand (const OperandDesc & desc,
							  Operand* operand)
{
	assert (desc.type == OperandDesc::Type::F);
	*operand = desc.fix;
}
void Disassembler::parseRegxXXOperand (const OperandDesc & desc,
								 Operand* operand)
{
	assert (desc.type == OperandDesc::Type::RegxXX);
	operand->type = OperandType::REG;
	unsigned size = getOperandSize (desc.size);
	operand->reg.name = getRegName (desc.regxXX.index, size);
}
void Disassembler::parseRegrXXrXOperand (const OperandDesc & desc,
								 Operand* operand)
{
	assert (desc.type == OperandDesc::Type::RegrXXrX);
	operand->type = OperandType::REG;
	unsigned size = getOperandSize (desc.size);
	operand->reg.name = getRegName (desc.regxXX.index, size, false, getRexB ());
}
unsigned Disassembler::getOperandSize (OperandDesc::Size desc, OperandType type)
{
	if (OperandDesc::Size::RvMw == desc)
	{
		switch (type)
		{
		case OperandType::REG: return getOperandSize (OperandDesc::Size::v);
		case OperandType::MEM: return getOperandSize (OperandDesc::Size::w);
		}
		throw "";
	}
	
	return getOperandSize (desc);
}
unsigned Disassembler::getOperandSize (OperandDesc::Size desc)
{
	switch (desc)
	{
	case OperandDesc::Size::z:	//finish
	case OperandDesc::Size::e:	//finish
		if (getRexW ())
		{
			assert (is_x64 ());
			return 4;
		}
		else
		{	//x64 or x86
			if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
				return 2;
			else
				return 4;
		}
	case OperandDesc::Size::r:	//finish
	case OperandDesc::Size::v:	//finish
		if (getRexW ())
		{
			assert (is_x64 ());
			return 8;
		}
		else
		{	//x64 or x86
			if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
				return 2;
			else
				return 4;
		}
	case OperandDesc::Size::b:	//finish
		return 1;
	case OperandDesc::Size::w:	//finish
		return 2;
	case OperandDesc::Size::v_d64:	//finish
	case OperandDesc::Size::r_d64:	//finish
		if (getRexW ())
		{
			assert (is_x64 ());
			return 8;
		}
		else
		{	//x64 or x86
			if (is_x86 ())
			{
				if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
					return 2;
				else
					return 4;
			}
			else	//x64
			{
				if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
					return 2;
				else
					return 8;
			}
		}
	case OperandDesc::Size::q:
		return 8;
	case OperandDesc::Size::a:
		if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
			return 4;
		else
			return 8;
	case OperandDesc::Size::p:
		if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
			return 4;
		else
			return 6;
	case OperandDesc::Size::s:
		return 6;
	case OperandDesc::Size::y:
	case OperandDesc::Size::d:
		return 4;
	case OperandDesc::Size::_10:
		return 10;
	case OperandDesc::Size::_14_28:
		if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
			return 14;
		else
			return 28;
	case OperandDesc::Size::_94_108:
		if (_reader.isPrefixExist (Prefix::OPERAND_SIZE))
			return 94;
		else
			return 108;
	}

	throw "not support this desc of operand size";
}
void Disassembler::parseImmOperand (const OperandDesc & desc,
							  Operand* operand)
{
	assert (desc.type == OperandDesc::Type::I ||
			desc.type == OperandDesc::Type::J ||
			desc.type == OperandDesc::Type::A);
	operand->type = OperandType::IMM;

	unsigned size = getOperandSize (desc.size);
	operand->imm.size = size;
	_reader.readImm (
		size, &operand->imm.val, &operand->imm.val_2);
}
RegName Disassembler::getRegNameByBase ()
{
	if (is_x86 ())
		return getRegName (getBase (), 4);
	else
		return getRegName (getBase (), 8, hasRex (), getRexB ());
}
RegName Disassembler::getRegNameByIndex ()
{
	if (is_x86 ())
		return getRegName (getIndex (), 4);
	else
		return getRegName (getIndex (), 8, hasRex (), getRexX ());
}
RegName Disassembler::getRegNameByRM ()
{
	if (is_x86 ())
		return getRegName (getRM (), 4);
	else	//x64
		return getRegName (getRM (), 8, hasRex (), getRexB ());
};
RegName Disassembler::getRegNameByRM (unsigned size)
{
	if (is_x86 ())
		return getRegName (getRM (), size);
	else	//x64
		return getRegName (getRM (), size, hasRex (), getRexB ());
};
RegName Disassembler::getRegNameByReg (unsigned size)
{
	if (is_x86 ())
		return getRegName (getReg (), size);
	else	//x64
		return getRegName (getReg (), size, hasRex (), getRexR ());
};
void Disassembler::parseAddrByModrm (MemAddr* addr)
{
	assert (getMod () != 0b11);

	if (getMod () == 0b00)
	{
		if (getRM () == 0b100)
		{
			addr->displacement = 0;
			parseSIB (addr);
			return;
		}
		if (getRM () == 0b101)
		{
			int disp = _reader.getDisplacement (4);
			if (is_x86 ())
				addr->setByDisplacement (disp);
			else	//x64
				addr->setByRelativeDisplacement (disp);
			return;
		}

		assert (getRM () != 0b100 && getRM () != 0b101);

		addr->setByReg (getRegNameByRM ());
		return;
	}

	assert (getMod () == 0b01 || getMod () == 0b10);

	if (getRM () != 0x4)
		addr->setByReg (getRegNameByRM ());
	else
		parseSIB (addr);

	if (getMod () == 0b01)
		addr->displacement = _reader.getDisplacement (1);
	else
	{
		assert (getMod () == 0b10);
		addr->displacement = _reader.getDisplacement (4);
	}
}
SegName Disassembler::getSegName (RegName base)
{
	if (_reader.isPrefixExist (Prefix::SEG))
	{
		return _reader.getSegPrefix ();
	}

	switch (base)
	{
	case RegName::NONE:
	case RegName::EAX:
	case RegName::ECX:
	case RegName::EDX:
	case RegName::EBX:
	case RegName::ESI:
	case RegName::EDI:
		return SegName::DS;
	case RegName::RAX:
	case RegName::RCX:
	case RegName::RDX:
	case RegName::RBX:
	case RegName::RSI:
	case RegName::RDI:
	case RegName::R8 :
	case RegName::R9 :
	case RegName::R10:
	case RegName::R11:
	case RegName::R12:
	case RegName::R13:
	case RegName::R14:
	case RegName::R15:
		return SegName::DS;	//check its correctness
	case RegName::ESP:
	case RegName::EBP:
		return SegName::SS;
	case RegName::RSP:
	case RegName::RBP:
		return SegName::SS;	//check its correctness
	}

	throw "";
}
void Disassembler::parseMemOperand (const OperandDesc & desc,
							 Operand* operand)
{
	assert (desc.type == OperandDesc::Type::E ||
			desc.type == OperandDesc::Type::M);
	assert (getMod () != 0b11);

	operand->type = OperandType::MEM;
	operand->mem.size = getOperandSize (desc.size, OperandType::MEM);

	parseAddrByModrm (&operand->mem.addr);
	operand->mem.seg = getSegName (operand->mem.addr.base);
}
void Disassembler::parseRMOperand (const OperandDesc & desc,
							 Operand* operand)
{
	assert (desc.type == OperandDesc::Type::E ||
			desc.type == OperandDesc::Type::R && getMod () == 0b11);

	if (getMod () == 0b11)
		return parseRegOperand (desc, operand, true);
	else
		return parseMemOperand (desc, operand);
}
void Disassembler::parseOperand (const OperandDesc & desc,
						   Operand* operand)
{
	switch (desc.type)
	{
	case OperandDesc::Type::D:
		return parseDrOperand (desc, operand);
	case OperandDesc::Type::C:
		return parseCrOperand (desc, operand);
	case OperandDesc::Type::G:
		return parseRegOperand (desc, operand, false);
	case OperandDesc::Type::S:
		return parseSegOperand (desc, operand);
	case OperandDesc::Type::R:
	case OperandDesc::Type::E:
		return parseRMOperand (desc, operand);
	case OperandDesc::Type::M:
		return parseMemOperand (desc, operand);
	case OperandDesc::Type::J:
	case OperandDesc::Type::A:
	case OperandDesc::Type::I:
		return parseImmOperand (desc, operand);
	case OperandDesc::Type::F:
		return parseFixOperand (desc, operand);
	case OperandDesc::Type::O:
		return parseDisplaceOperand (desc, operand);
	case OperandDesc::Type::RegxXX:
		return parseRegxXXOperand (desc, operand);
	case OperandDesc::Type::RegrXXrX:
		return parseRegrXXrXOperand (desc, operand);
	case OperandDesc::Type::X:
		return parseSiOperand (desc, operand);
	case OperandDesc::Type::Y:
		return parseDiOperand (desc, operand);
	}

	throw Exception {"unknown type"};
}
Disassembler::Disassembler (const std::vector<Byte> & binaryCode, InstSet instSet)
	: _reader {binaryCode, instSet}
//	, _instSet {instSet}
{
}
Instruction Disassembler::conv (unsigned begin)
{
	_reader.reset (begin);

	Instruction instruction;

	auto & map = getOpcodeMap ();

	instruction.prefixs = _reader.getPrefixs ();	//directly get from _reader
	instruction.name = map.name;

	assert (map.operands.size () <= 3);
	instruction.operands.resize (map.operands.size ());
	for (unsigned i = 0; i < map.operands.size (); i++)
		parseOperand (map.operands[i], &instruction.operands[i]);

	instruction.size = _reader.getReadedSize ();

	return instruction;
}
void MemAddr::setByRelativeDisplacement (int displacement)
{
	this->scale = 1;
	this->index = RegName::NONE;
	this->base = RegName::NONE;
	this->displacement = displacement;
	this->isRelativeEip = true;
}
void MemAddr::setByReg (RegName name)
{
	this->scale = 1;
	this->index = RegName::NONE;
	this->base = name;
	this->displacement = 0;
	this->isRelativeEip = false;
}
void MemAddr::setByDisplacement (int displacement)
{
	this->scale = 1;
	this->index = RegName::NONE;
	this->base = RegName::NONE;
	this->displacement = displacement;
	this->isRelativeEip = false;
}