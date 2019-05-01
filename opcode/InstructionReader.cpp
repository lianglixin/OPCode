#include "InstructionReader.h"


#include <cassert>
#include "Tools.h"


InstructionReader::InstructionReader (const std::vector <Byte> & binaryCode, InstSet instSet)
	: _byteReader {binaryCode}
	, _instSet {instSet}
{
}
Byte InstructionReader::readOpcode ()
{
	assert (_modrm.isReaded == false);
	assert (_sib.isReaded == false);
	assert (_displacement.isReaded == false);
	assert (_imm.isReaded == false);

	if (false == _opcode.isReaded)
	{
		Byte b;
		while (1)
		{
			b = readBytes <uint8> ();
			if (trySaveAsPrefix (b))
			{
				// b is prefix
				continue;
			}
			// b is opcode
			break;
		}

		_opcode.isReaded = true;
		_opcode.vec.push_back (b);
		return b;
	}
	
	Byte opcode = readBytes <uint8> ();
	_opcode.vec.push_back (opcode);
	return opcode;
}
size_t InstructionReader::getOpcodeReadedSize ()
{
	return _opcode.vec.size ();
}
Byte InstructionReader::getOpcode (size_t index)
{
	assert (index < _opcode.vec.size ());
	return _opcode.vec[index];
}
bool InstructionReader::hasRex ()
{
	return _prefix.hasRex;
}
bool InstructionReader::hasRexB ()
{
	if (getRexB ())
		return true;
	else
		return false;
}
bool InstructionReader::hasRexW ()
{
	if (getRexW ())
		return true;
	else
		return false;
}
Byte InstructionReader::getRexB ()
{
	if (_prefix.hasRex)
		return Tools::getBit (_prefix.rex, 0);
	else
		return 0;
}
Byte InstructionReader::getRexR ()
{
	if (_prefix.hasRex)
		return Tools::getBit (_prefix.rex, 2);
	else
		return 0;
}
Byte InstructionReader::getRexX ()
{
	if (_prefix.hasRex)
		return Tools::getBit (_prefix.rex, 1);
	else
		return 0;
}
Byte InstructionReader::getRexW ()
{
	if (_prefix.hasRex)
		return Tools::getBit (_prefix.rex, 3);
	else
		return 0;
}
bool InstructionReader::is_x86 ()
{
	if (InstSet::x86 == _instSet)
		return true;
	else
		return false;
}
bool InstructionReader::is_x64 ()
{
	if (InstSet::x64 == _instSet)
		return true;
	else
		return false;
}
Byte InstructionReader::getModrm ()
{
	if (_modrm.isReaded)
		return _modrm.val;

	assert (_sib.isReaded == false);
	assert (_displacement.isReaded == false);
	assert (_imm.isReaded == false);
	_modrm.isReaded = true;
	_modrm.val = readBytes <uint8> ();

	return _modrm.val;
}
std::vector<Prefix> InstructionReader::getPrefixs ()
{
	std::vector<Prefix> re;

	if (_prefix.hasLockRepeat)
	{
		assert (Prefix::REP == _prefix.lockRepeat ||
				Prefix::REPNE == _prefix.lockRepeat ||
				Prefix::LOCK == _prefix.lockRepeat);
		re.push_back (_prefix.lockRepeat);
	}
	return re;
}
#if 0
uint32 InstructionReader::getImm (int size)
{
	assert (size == 1 || size == 2 || size == 4);

	if (_imm.isReaded)
	{
		assert (_imm.size == size);
		return _imm.val;
	}

	//it is ok no matter sib has readed or not 
	//it is ok no matter modrm has readed or not 
	//it is ok no matter displacement has readed or not 

	_imm.isReaded = true;
	_imm.size = size;
	if (size == 1)
		_imm.val = readBytes <uint8> ();
	else if (size == 2)
		_imm.val = readBytes <uint16> ();
	else if (size == 4)
		_imm.val = readBytes <uint32> ();
	else
		assert (0);

	return _imm.val;
}
#endif
void InstructionReader::readImm (int size, uint32* val, uint32* val_2)
{
	assert (size == 1 || size == 2 || size == 4 || size == 6);

	//it is ok no matter sib has readed or not 
	//it is ok no matter modrm has readed or not 
	//it is ok no matter displacement has readed or not 
	//it is ok no matter other imm has readed or not 

	_imm.isReaded = true;

	if (size <= 4)
	{
		if (size == 1)
			*val = readBytes <uint8> ();
		else if (size == 2)
			*val = readBytes <uint16> ();
		else if (size == 4)
			*val = readBytes <uint32> ();
		else
			assert (0);
	}
	else
	{
		if (size == 6)
		{
			*val = readBytes <uint32> ();
			*val_2 = readBytes <uint16> ();
		}
		else
			assert (0);
	}
}
int InstructionReader::getDisplacement (int size, bool noModrm)
{
	assert (size == 1 || size == 4);

	if (_displacement.isReaded)
	{
		assert (_displacement.size == size);
		return _displacement.val;
	}

	if (noModrm)
		assert (false == _modrm.isReaded);
	else
		assert (_modrm.isReaded);
	//it is ok no matter sib has readed or not 
	assert (_imm.isReaded == false);
	_displacement.isReaded = true;
	_displacement.size = size;
	if (size == 1)
		_displacement.val = readBytes <int8> ();
	else if (size == 4)
		_displacement.val = readBytes <int32> ();
	else
		assert (0);

	return _displacement.val;
}
Byte InstructionReader::getBase ()
{
	return Tools::get012Bits (getSib ());
}
Byte InstructionReader::getIndex ()
{
	return Tools::get345Bits (getSib ());
}
Byte InstructionReader::getScale ()
{
	return Tools::get67Bits (getSib ());
}
Byte InstructionReader::getMod ()
{
	return Tools::get67Bits (getModrm ());
}
Byte InstructionReader::getReg ()
{
	return Tools::get345Bits (getModrm ());
}
Byte InstructionReader::getSeg ()
{
	return Tools::get345Bits (getModrm ());
}
Byte InstructionReader::getRM ()
{
	return Tools::get012Bits (getModrm ());
}
bool InstructionReader::trySaveAsPrefix (Byte b)
{
	auto saveSeg = [this] (SegName name) -> bool
	{
		assert (_prefix.hasRex == false);
		assert (_prefix.hasSeg == false);
		_prefix.hasSeg = true;
		_prefix.seg = name;
		return true;
	};
	auto saveLockRepeat = [this] (Prefix name) -> bool
	{
		assert (_prefix.hasRex == false);
		assert (_prefix.hasLockRepeat == false);
		_prefix.hasLockRepeat = true;
		_prefix.lockRepeat = name;
		return true;
	};

	switch (b)
	{
	case 0x66:
		assert (_prefix.hasRex == false);
		assert (_prefix.hasOperandSize == false);
		_prefix.hasOperandSize = true;
		return true;
	case 0x67:
		assert (_prefix.hasRex == false);
		assert (_prefix.hasAddressSize == false);
		_prefix.hasAddressSize = true;
		return true;
	case 0xF0: return saveLockRepeat (Prefix::LOCK);
	case 0xF2: return saveLockRepeat (Prefix::REPNE);
	case 0xF3: return saveLockRepeat (Prefix::REPE);
	case 0x64: return saveSeg (SegName::FS);
	case 0x2E: return saveSeg (SegName::CS);
	case 0x36: return saveSeg (SegName::SS);
	case 0x26: return saveSeg (SegName::ES);
	case 0x3E: return saveSeg (SegName::DS);
	case 0x65: return saveSeg (SegName::GS);
	}

	if (InstSet::x64 == _instSet)
	{
		//treat 0x40 - 0x4F as prefix

		if (0x40 <= b && b <= 0x4F)
		{
			assert (_prefix.hasRex == false);
			_prefix.hasRex = true;
			_prefix.rex = b;
			return true;
		}
	}

	return false;
}
template <typename T>
T InstructionReader::readBytes (bool isReorder)
try
{
	return _byteReader.read <T> (isReorder);
}
catch (const Exception & e)
{
	if (e.is (ByteReader::ExceptionType::TOO_SHORT))
		throw Exception {"opcode too short"};

	throw;
}
size_t InstructionReader::getReadedSize()
{
	return _byteReader.getReadedSize ();
}
bool InstructionReader::isPrefixExist (Prefix prefix)
{
	switch (prefix)
	{
	case Prefix::OPERAND_SIZE:
		return _prefix.hasOperandSize;
	case Prefix::ADDRESS_SIZE:
		return _prefix.hasAddressSize;
	case Prefix::SEG:
		return _prefix.hasSeg;
	}

	return false;
}
SegName InstructionReader::getSegPrefix ()
{
	assert (_prefix.hasSeg);

	return _prefix.seg;
}
void InstructionReader::reset (size_t begin)
{
	_byteReader.reset (begin);
}
Byte InstructionReader::getSib ()
{
	if (_sib.isReaded)
		return _sib.val;

	assert (_modrm.isReaded);
	assert (_displacement.isReaded == false);
	assert (_imm.isReaded == false);
	_sib.isReaded = true;
	_sib.val = readBytes <uint8> ();

	return _sib.val;
}