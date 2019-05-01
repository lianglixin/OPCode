#include "OpcodeTable.h"


#include "InstructionReader.h"
#include <cassert>


const OpcodeMain & OpcodeTable::getOpcodeMain (
	InstructionReader & reader)
{
	Byte opcode = reader.readOpcode ();
	bool is_x64 = reader.is_x64 ();
	bool hasRexB = reader.hasRexB ();
	bool hasRexW = reader.hasRexW ();
	bool hasPerfixOperandSize = reader.isPrefixExist (Prefix::OPERAND_SIZE);

	switch (reader.getOpcodeReadedSize ())
	{
	case 1:
		return getOpcodeMain_XX (opcode, is_x64, hasRexB, hasRexW, hasPerfixOperandSize);
	case 2:
		assert (reader.getOpcode (0) == 0x0F);
		return getOpcodeMain_0FXX (opcode, is_x64);
	}
	throw "";
}
const OpcodeMap & OpcodeTable::getOpcodeMap_DX_11XXXXXX (Byte opcode, Byte modrm)
{
	assert (opcode >= 0xD8 && opcode <= 0xDF);
	assert (Tools::get67Bits (modrm)== 0b11);

	auto iter = _escape_11XXXXXX.find (opcode);
	if (iter == _escape_11XXXXXX.end ())
		throw "not support this escape opcode";

	auto iter2 = iter->second.find (modrm);
	if (iter2 == iter->second.end ())
		throw "not support this modrm in this escape opcode";

	return iter2->second;
}
const OpcodeMap & OpcodeTable::getOpcodeMapByEscape (
	InstructionReader & reader)
{
	assert (reader.getOpcodeReadedSize () == 1);

	Byte opcode = reader.getOpcode (0);
	assert (opcode >= 0xD8 && opcode <= 0xDF);

	if (reader.getMod () == 0b11)
		return getOpcodeMap_DX_11XXXXXX (opcode, reader.getModrm ());
	else
		return getOpcodeMap_DX_non_11XXXXXX (opcode, reader.getReg ());
}
OpcodeMap OpcodeTable::getOpcodeMapWithout66 (
	InstructionReader & reader)
{
	const OpcodeMain & main = getOpcodeMain (reader);
	OpcodeMap map {};
	switch (main.type)
	{
	case MainEntryType::INSTRUCTION:
		map.name = main.instruction.name;
		map.operands = main.operands;
		return map;
	case MainEntryType::GROUP:
	{
		const OpcodeGroup & group =
			getOpcodeGroup (main.group.name, reader.getReg ());

		map.name = group.name;
		map.operands = main.operands;
		map.operands.insert (
			map.operands.end (),
			group.operands.begin (),
			group.operands.end ());
		return map;
	}
	case MainEntryType::MORE_OPCODE:
		return getOpcodeMapWithout66 (reader);
	case MainEntryType::ESCAPE:
		return getOpcodeMapByEscape (reader);
	case MainEntryType::EMPTY:
		map.name = InstructionName::_INVALID;
		map.operands = {};
		return map;
	}

	throw "";
}
OpcodeMap OpcodeTable::getOpcodeMap (InstructionReader & reader)
{
	OpcodeMap map = getOpcodeMapWithout66 (reader);


	//change instruction name when 0x66 OPERAND_SIZE
	if (reader.isPrefixExist (Prefix::OPERAND_SIZE))
	{
		std::map <InstructionName /*orgin*/, InstructionName /*when66*/>
			changeWhen66
		{
			{InstructionName::INSD , InstructionName::INSW },	//no test
			{InstructionName::OUTSD, InstructionName::OUTSW},	//no test
			{InstructionName::IRETD, InstructionName::IRETW},	//no test
		};


		auto iter = changeWhen66.find (map.name);
		if (iter != changeWhen66.end ())
		{
			// change
			map.name = iter->second;
		}
	}

	//change instruction name when 0x67 ADDRESS_SIZE
	if (reader.isPrefixExist (Prefix::ADDRESS_SIZE))
	{
		std::map <InstructionName /*orgin*/, InstructionName /*when67*/>
			changeWhen67
		{
			{InstructionName::JECXZ, InstructionName::JCXZ },
		};


		auto iter = changeWhen67.find (map.name);
		if (iter != changeWhen67.end ())
		{
			// change
			map.name = iter->second;
		}
	}

	return map;
}
const OpcodeMain & OpcodeTable::getOpcodeMain_XX (
	Byte opcode, bool is_x64, bool hasRexB, bool hasRexW, bool hasPrefixOperandSize)
{
	if (is_x64)
	{
		auto iter = _main_diff_x64.find (opcode);

		if (iter != _main_diff_x64.end ())
			return iter->second;	//found
	}

	if (hasRexB)
	{
		auto iter = _main_diff_RexB.find (opcode);

		if (iter != _main_diff_RexB.end ())
			return iter->second;	//found
	}

	if (hasRexW)
	{
		auto iter = _main_diff_RexW.find (opcode);

		if (iter != _main_diff_RexW.end ())
			return iter->second;	//found
	}

	if (hasPrefixOperandSize)
	{
		auto iter = _main_diff_PrefixOperandSize.find (opcode);

		if (iter != _main_diff_PrefixOperandSize.end ())
			return iter->second;	//found
	}

	auto iter = _main.find (opcode);

	if (iter == _main.end ())
		throw Exception {"not support this single byte opcode"};

	return iter->second;
}
const OpcodeMain & OpcodeTable::getOpcodeMain_0FXX (Byte opcode, bool is_x64)
{
	if (is_x64)
	{
		auto iter = _main_0FXX_diff_x64.find (opcode);

		if (iter != _main_0FXX_diff_x64.end ())
			return iter->second;	//found
	}

	auto iter = _main_0FXX.find (opcode);

	if (iter == _main_0FXX.end ())
		throw Exception {"not support this 0FXX opcode"};

	return iter->second;
}
const OpcodeGroup & OpcodeTable::getOpcodeGroup (GroupName name, Byte item)
{
	auto iter = _group.find (name);
	if (_group.end () == iter)
		throw Exception {"not support this group"};

	auto iter2 = iter->second.find (item);
	if (iter->second.end () == iter2)
		throw Exception {"not support this item in group"};

	return iter2->second;
}
const OpcodeMap & OpcodeTable::getOpcodeMap_DX_non_11XXXXXX (Byte opcode, Byte item)
{
	auto iter = _escape_non_11XXXXXX.find (opcode);
	if (_escape_non_11XXXXXX.end () == iter)
		throw Exception {"not support this escape"};

	auto iter2 = iter->second.find (item);
	if (iter->second.end () == iter2)
		throw Exception {"not support this item in escape"};

	return iter2->second;
}

#define Rd              {OperandDesc::Type::R       , OperandDesc::Size::d    }
#define Rv              {OperandDesc::Type::R       , OperandDesc::Size::v    }
#define Cd              {OperandDesc::Type::C       , OperandDesc::Size::d    }
#define Dd              {OperandDesc::Type::D       , OperandDesc::Size::d    }
#define RvMw            {OperandDesc::Type::E       , OperandDesc::Size::RvMw }
#define Ev              {OperandDesc::Type::E       , OperandDesc::Size::v    }
#define Ev_d64          {OperandDesc::Type::E       , OperandDesc::Size::v_d64}
#define Ey              {OperandDesc::Type::E       , OperandDesc::Size::y    }
#define Ew              {OperandDesc::Type::E       , OperandDesc::Size::w    }
#define Eb              {OperandDesc::Type::E       , OperandDesc::Size::b    }
#define Ep              {OperandDesc::Type::E       , OperandDesc::Size::p    }
#define Ed              {OperandDesc::Type::E       , OperandDesc::Size::d    }
#define Mq              {OperandDesc::Type::M       , OperandDesc::Size::q    }
#define Mb              {OperandDesc::Type::M       , OperandDesc::Size::b    }
#define Ms              {OperandDesc::Type::M       , OperandDesc::Size::s    }
#define MM              {OperandDesc::Type::M       , OperandDesc::Size::d    }		//one M will replace other M
#define Ma              {OperandDesc::Type::M       , OperandDesc::Size::a    }
#define Mp              {OperandDesc::Type::M       , OperandDesc::Size::p    }
#define Mw              {OperandDesc::Type::M       , OperandDesc::Size::w    }
#define Gv              {OperandDesc::Type::G       , OperandDesc::Size::v    }
#define Gy              {OperandDesc::Type::G       , OperandDesc::Size::y    }
#define Gw              {OperandDesc::Type::G       , OperandDesc::Size::w    }
#define Gb              {OperandDesc::Type::G       , OperandDesc::Size::b    }
#define Gz              {OperandDesc::Type::G       , OperandDesc::Size::z    }
#define Iv              {OperandDesc::Type::I       , OperandDesc::Size::v    }
#define Iz              {OperandDesc::Type::I       , OperandDesc::Size::z    }
#define Iw              {OperandDesc::Type::I       , OperandDesc::Size::w    }
#define Ib              {OperandDesc::Type::I       , OperandDesc::Size::b    }
#define Ov              {OperandDesc::Type::O       , OperandDesc::Size::v    }
#define Ob              {OperandDesc::Type::O       , OperandDesc::Size::b    }
#define Jz              {OperandDesc::Type::J       , OperandDesc::Size::z    }
#define Jb              {OperandDesc::Type::J       , OperandDesc::Size::b    }
#define Sw              {OperandDesc::Type::S       , OperandDesc::Size::w    }
#define Ap              {OperandDesc::Type::A       , OperandDesc::Size::p    }
#define Xb              {OperandDesc::Type::X       , OperandDesc::Size::b    }
#define Xv              {OperandDesc::Type::X       , OperandDesc::Size::v    }
#define Yb              {OperandDesc::Type::Y       , OperandDesc::Size::b    }
#define Yv              {OperandDesc::Type::Y       , OperandDesc::Size::v    }
#define F_1             {OperandDesc::Type::F       , OperandDesc::Size::unused, Operand::IMM (1, 0x1)}
#define F_AL            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::AL}}
#define F_CL            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::CL}}
#define F_DL            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::DL}}
#define F_BL            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::BL}}
#define F_AH            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::AH}}
#define F_CH            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::CH}}
#define F_DH            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::DH}}
#define F_BH            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::BH}}
#define F_AL_R8L        {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x0}}
#define F_CL_R9L        {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x1}}
#define F_DL_R10L       {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x2}}
#define F_BL_R11L       {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x3}}
#define F_AH_R12L       {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x4}}
#define F_CH_R13L       {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x5}}
#define F_DH_R14L       {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x6}}
#define F_BH_R15L       {OperandDesc::Type::RegrXXrX, OperandDesc::Size::b    , {}, {0x7}}
#define F_CS            {OperandDesc::Type::F       , OperandDesc::Size::unused, {SegName::CS}}
#define F_DS            {OperandDesc::Type::F       , OperandDesc::Size::unused, {SegName::DS}}
#define F_ES            {OperandDesc::Type::F       , OperandDesc::Size::unused, {SegName::ES}}
#define F_SS            {OperandDesc::Type::F       , OperandDesc::Size::unused, {SegName::SS}}
#define F_FS            {OperandDesc::Type::F       , OperandDesc::Size::unused, {SegName::FS}}
#define F_GS            {OperandDesc::Type::F       , OperandDesc::Size::unused, {SegName::GS}}
#define F_DX            {OperandDesc::Type::F       , OperandDesc::Size::unused, {RegName::DX}}
#define F_ST0           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST0}}
#define F_ST1           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST1}}
#define F_ST2           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST2}}
#define F_ST3           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST3}}
#define F_ST4           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST4}}
#define F_ST5           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST5}}
#define F_ST6           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST6}}
#define F_ST7           {OperandDesc::Type::F       , OperandDesc::Size::unused, {StName::ST7}}
#define rAX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x0}}
#define rCX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x1}}
#define rDX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x2}}
#define rBX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x3}}
#define rSP             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x4}}
#define rBP             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x5}}
#define rSI             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x6}}
#define rDI             {OperandDesc::Type::RegxXX  , OperandDesc::Size::r    , {}, {0x7}}
#define rAX_r8          {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x0}}
#define rCX_r9          {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x1}}
#define rDX_r10         {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x2}}
#define rBX_r11         {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x3}}
#define rSP_r12         {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x4}}
#define rBP_r13         {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x5}}
#define rSI_r14         {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x6}}
#define rDI_r15         {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r    , {}, {0x7}}
#define rAX_r8_d64      {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x0}}
#define rCX_r9_d64      {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x1}}
#define rDX_r10_d64     {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x2}}
#define rBX_r11_d64     {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x3}}
#define rSP_r12_d64     {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x4}}
#define rBP_r13_d64     {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x5}}
#define rSI_r14_d64     {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x6}}
#define rDI_r15_d64     {OperandDesc::Type::RegrXXrX, OperandDesc::Size::r_d64, {}, {0x7}}
#define eAX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x0}}
#define eCX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x1}}
#define eDX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x2}}
#define eBX             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x3}}
#define eSP             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x4}}
#define eBP             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x5}}
#define eSI             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x6}}
#define eDI             {OperandDesc::Type::RegxXX  , OperandDesc::Size::e    , {}, {0x7}}
#define single_real     {OperandDesc::Type::M       , OperandDesc::Size::d      }
#define double_real     {OperandDesc::Type::M       , OperandDesc::Size::q      }
#define extended_real   {OperandDesc::Type::M       , OperandDesc::Size::_10    }
#define word_integer    {OperandDesc::Type::M       , OperandDesc::Size::w      }
#define dword_integer   {OperandDesc::Type::M       , OperandDesc::Size::d      }
#define qword_integer   {OperandDesc::Type::M       , OperandDesc::Size::q      }
#define _14_or_28_byte  {OperandDesc::Type::M       , OperandDesc::Size::_14_28 }
#define _94_or_108_byte {OperandDesc::Type::M       , OperandDesc::Size::_94_108}
#define _2_byte         {OperandDesc::Type::M       , OperandDesc::Size::w      }
#define packed_BCD      {OperandDesc::Type::M       , OperandDesc::Size::_10    }

const std::map <Byte, OpcodeMain> OpcodeTable::_main_diff_PrefixOperandSize
{
	{0x98,		{InstructionName::CBW      , {                       }}},
	{0x99,		{InstructionName::CWD      , {                       }}},
};
const std::map <Byte, OpcodeMain> OpcodeTable::_main_diff_RexW
{
	{0x98,		{InstructionName::CDQE     , {                       }}},
	{0x99,		{InstructionName::CQO      , {                       }}},
	{0xCF,		{InstructionName::IRETQ    , {                       }}},
};
const std::map <Byte, OpcodeMain> OpcodeTable::_main_diff_RexB
{
	{0x90,		{InstructionName::XCHG     , {rAX        , rAX_r8    }}},
};
const std::map <Byte, OpcodeMain> OpcodeTable::_main_diff_x64
{
	{0x06,		{MainEntryType::EMPTY                                 }},
	{0x07,		{MainEntryType::EMPTY                                 }},	//nt
	{0x0E,		{MainEntryType::EMPTY                                 }},	//nt
	{0x16,		{MainEntryType::EMPTY                                 }},	//nt
	{0x17,		{MainEntryType::EMPTY                                 }},	//nt
	{0x1E,		{MainEntryType::EMPTY                                 }},	//nt
	{0x1F,		{MainEntryType::EMPTY                                 }},	//nt
	{0x27,		{MainEntryType::EMPTY                                 }},	//nt
	{0x2F,		{MainEntryType::EMPTY                                 }},	//nt
	{0x37,		{MainEntryType::EMPTY                                 }},	//nt
	{0x3F,		{MainEntryType::EMPTY                                 }},	//nt
	{0x60,		{MainEntryType::EMPTY                                 }},	//nt
	{0x61,		{MainEntryType::EMPTY                                 }},	//nt
	{0x62,		{MainEntryType::EMPTY                                 }},	//nt
	{0x63,		{InstructionName::MOVSXD   , {Gv         , Ed        }}},	// should Ed ?
	{0x82,		{MainEntryType::EMPTY                                 }},	//nt
	{0x9A,		{MainEntryType::EMPTY                                 }},	//nt
	{0x9C,		{InstructionName::PUSHFQ   , {                       }}},	//nt
	{0x9D,		{InstructionName::POPFQ    , {                       }}},	//nt
	{0xC4,		{MainEntryType::EMPTY                                 }},	//nt
	{0xC5,		{MainEntryType::EMPTY                                 }},	//nt
	{0xCE,		{MainEntryType::EMPTY                                 }},	//nt
	{0xD4,		{MainEntryType::EMPTY                                 }},	//nt
	{0xD5,		{MainEntryType::EMPTY                                 }},	//nt
};
const std::map <Byte, OpcodeMain> OpcodeTable::_main
{
	{0x00,		{InstructionName::ADD      , {Eb         , Gb        }}},
	{0x01,		{InstructionName::ADD      , {Ev         , Gv        }}},
	{0x02,		{InstructionName::ADD      , {Gb         , Eb        }}},
	{0x03,		{InstructionName::ADD      , {Gv         , Ev        }}},
	{0x04,		{InstructionName::ADD      , {F_AL       , Ib        }}},
	{0x05,		{InstructionName::ADD      , {rAX        , Iz        }}},
	{0x06,		{InstructionName::PUSH     , {F_ES                   }}},
	{0x07,		{InstructionName::POP      , {F_ES                   }}},
	{0x08,		{InstructionName::OR       , {Eb         , Gb        }}},
	{0x09,		{InstructionName::OR       , {Ev         , Gv        }}},
	{0x0A,		{InstructionName::OR       , {Gb         , Eb        }}},
	{0x0B,		{InstructionName::OR       , {Gv         , Ev        }}},
	{0x0C,		{InstructionName::OR       , {F_AL       , Ib        }}},
	{0x0D,		{InstructionName::OR       , {rAX        , Iz        }}},
	{0x0E,		{InstructionName::PUSH     , {F_CS                   }}},
	{0x0F,		{MainEntryType::MORE_OPCODE                           }},
	{0x10,		{InstructionName::ADC      , {Eb         , Gb        }}},
	{0x11,		{InstructionName::ADC      , {Ev         , Gv        }}},
	{0x12,		{InstructionName::ADC      , {Gb         , Eb        }}},
	{0x13,		{InstructionName::ADC      , {Gv         , Ev        }}},
	{0x14,		{InstructionName::ADC      , {F_AL       , Ib        }}},
	{0x15,		{InstructionName::ADC      , {rAX        , Iz        }}},
	{0x16,		{InstructionName::PUSH     , {F_SS                   }}},
	{0x17,		{InstructionName::POP      , {F_SS                   }}},
	{0x18,		{InstructionName::SBB      , {Eb         , Gb        }}},
	{0x19,		{InstructionName::SBB      , {Ev         , Gv        }}},
	{0x1A,		{InstructionName::SBB      , {Gb         , Eb        }}},
	{0x1B,		{InstructionName::SBB      , {Gv         , Ev        }}},
	{0x1C,		{InstructionName::SBB      , {F_AL       , Ib        }}},
	{0x1D,		{InstructionName::SBB      , {rAX        , Iz        }}},
	{0x1E,		{InstructionName::PUSH     , {F_DS                   }}},
	{0x1F,		{InstructionName::POP      , {F_DS                   }}},	//no test
	{0x20,		{InstructionName::AND      , {Eb         , Gb        }}},
	{0x21,		{InstructionName::AND      , {Ev         , Gv        }}},
	{0x22,		{InstructionName::AND      , {Gb         , Eb        }}},
	{0x23,		{InstructionName::AND      , {Gv         , Ev        }}},
	{0x24,		{InstructionName::AND      , {F_AL       , Ib        }}},
	{0x25,		{InstructionName::AND      , {rAX        , Iz        }}},
	{0x27,		{InstructionName::DAA      , {                       }}},
	{0x28,		{InstructionName::SUB      , {Eb         , Gb        }}},
	{0x29,		{InstructionName::SUB      , {Ev         , Gv        }}},
	{0x2A,		{InstructionName::SUB      , {Gb         , Eb        }}},
	{0x2B,		{InstructionName::SUB      , {Gv         , Ev        }}},
	{0x2C,		{InstructionName::SUB      , {F_AL       , Ib        }}},
	{0x2D,		{InstructionName::SUB      , {rAX        , Iz        }}},
	{0x2F,		{InstructionName::DAS      , {                       }}},	// no test
	{0x30,		{InstructionName::XOR      , {Eb         , Gb        }}},
	{0x31,		{InstructionName::XOR      , {Ev         , Gv        }}},
	{0x32,		{InstructionName::XOR      , {Gb         , Eb        }}},
	{0x33,		{InstructionName::XOR      , {Gv         , Ev        }}},
	{0x34,		{InstructionName::XOR      , {F_AL       , Ib        }}},
	{0x35,		{InstructionName::XOR      , {rAX        , Iz        }}},
	{0x38,		{InstructionName::CMP      , {Eb         , Gb        }}},
	{0x39,		{InstructionName::CMP      , {Ev         , Gv        }}},
	{0x3A,		{InstructionName::CMP      , {Gb         , Eb        }}},
	{0x3B,		{InstructionName::CMP      , {Gv         , Ev        }}},
	{0x3C,		{InstructionName::CMP      , {F_AL       , Ib        }}},
	{0x3D,		{InstructionName::CMP      , {rAX        , Iz        }}},
	{0x3F,		{InstructionName::AAS      , {                       }}},	// no test
	{0x40,		{InstructionName::INC      , {eAX                    }}},
	{0x41,		{InstructionName::INC      , {eCX                    }}},
	{0x42,		{InstructionName::INC      , {eDX                    }}},
	{0x43,		{InstructionName::INC      , {eBX                    }}},
	{0x44,		{InstructionName::INC      , {eSP                    }}},
	{0x45,		{InstructionName::INC      , {eBP                    }}},
	{0x46,		{InstructionName::INC      , {eSI                    }}},
	{0x47,		{InstructionName::INC      , {eDI                    }}},
	{0x48,		{InstructionName::DEC      , {eAX                    }}},
	{0x49,		{InstructionName::DEC      , {eCX                    }}},
	{0x4A,		{InstructionName::DEC      , {eDX                    }}},
	{0x4B,		{InstructionName::DEC      , {eBX                    }}},
	{0x4C,		{InstructionName::DEC      , {eSP                    }}},
	{0x4D,		{InstructionName::DEC      , {eBP                    }}},
	{0x4E,		{InstructionName::DEC      , {eSI                    }}},
	{0x4F,		{InstructionName::DEC      , {eDI                    }}},
	{0x50,		{InstructionName::PUSH     , {rAX_r8_d64             }}},
	{0x51,		{InstructionName::PUSH     , {rCX_r9_d64             }}},
	{0x52,		{InstructionName::PUSH     , {rDX_r10_d64            }}},
	{0x53,		{InstructionName::PUSH     , {rBX_r11_d64            }}},
	{0x54,		{InstructionName::PUSH     , {rSP_r12_d64            }}},
	{0x55,		{InstructionName::PUSH     , {rBP_r13_d64            }}},
	{0x56,		{InstructionName::PUSH     , {rSI_r14_d64            }}},
	{0x57,		{InstructionName::PUSH     , {rDI_r15_d64            }}},
	{0x58,		{InstructionName::POP      , {rAX_r8_d64             }}},
	{0x59,		{InstructionName::POP      , {rCX_r9_d64             }}},
	{0x5A,		{InstructionName::POP      , {rDX_r10_d64            }}},
	{0x5B,		{InstructionName::POP      , {rBX_r11_d64            }}},
	{0x5C,		{InstructionName::POP      , {rSP_r12_d64            }}},
	{0x5D,		{InstructionName::POP      , {rBP_r13_d64            }}},
	{0x5E,		{InstructionName::POP      , {rSI_r14_d64            }}},
	{0x5F,		{InstructionName::POP      , {rDI_r15_d64            }}},
	{0x60,		{InstructionName::PUSHA    , {                       }}},
	{0x61,		{InstructionName::POPA     , {                       }}},
	{0x62,		{InstructionName::BOUND    , {Gv         , Ma        }}},
	{0x63,		{InstructionName::ARPL     , {Ew         , Gw        }}},
	{0x68,		{InstructionName::PUSH     , {Iz                     }}},
	{0x69,		{InstructionName::IMUL     , {Gv         , Ev  , Iz  }}},
	{0x6A,		{InstructionName::PUSH     , {Ib                     }}},
	{0x6B,		{InstructionName::IMUL     , {Gv         , Ev  , Ib  }}},
	{0x6C,		{InstructionName::INSB     , {                       }}},	//no test
	{0x6D,		{InstructionName::INSD     , {                       }}},	//no test
	{0x6E,		{InstructionName::OUTSB    , {                       }}},	//no test
	{0x6F,		{InstructionName::OUTSD    , {                       }}},	//no test
	{0x70,		{InstructionName::JO       , {Jb                     }}},
	{0x71,		{InstructionName::JNO      , {Jb                     }}},
	{0x72,		{InstructionName::JB       , {Jb                     }}},
	{0x73,		{InstructionName::JAE      , {Jb                     }}},
	{0x74,		{InstructionName::JE       , {Jb                     }}},
	{0x75,		{InstructionName::JNZ      , {Jb                     }}},
	{0x76,		{InstructionName::JBE      , {Jb                     }}},
	{0x77,		{InstructionName::JA       , {Jb                     }}},
	{0x78,		{InstructionName::JS       , {Jb                     }}},	//no test
	{0x79,		{InstructionName::JNS      , {Jb                     }}},	//no test
	{0x7A,		{InstructionName::JPE      , {Jb                     }}},	//no test
	{0x7B,		{InstructionName::JPO      , {Jb                     }}},	//no test
	{0x7C,		{InstructionName::JL       , {Jb                     }}},	//no test
	{0x7D,		{InstructionName::JGE      , {Jb                     }}},	//no test
	{0x7E,		{InstructionName::JLE      , {Jb                     }}},	//no test
	{0x7F,		{InstructionName::JG       , {Jb                     }}},	//no test
	{0x80,		{GroupName::_1             , {Eb         , Ib        }}},
	{0x81,		{GroupName::_1             , {Ev         , Iz        }}},
	{0x82,		{GroupName::_1             , {Eb         , Ib        }}},
	{0x83,		{GroupName::_1             , {Ev         , Ib        }}},
	{0x84,		{InstructionName::TEST     , {Eb         , Gb        }}},
	{0x85,		{InstructionName::TEST     , {Ev         , Gv        }}},
	{0x86,		{InstructionName::XCHG     , {Eb         , Gb        }}},
	{0x87,		{InstructionName::XCHG     , {Ev         , Gv        }}},
	{0x88,		{InstructionName::MOV      , {Eb         , Gb        }}},
	{0x89,		{InstructionName::MOV      , {Ev         , Gv        }}},
	{0x8A,		{InstructionName::MOV      , {Gb         , Eb        }}},
	{0x8B,		{InstructionName::MOV      , {Gv         , Ev        }}},
	{0x8C,		{InstructionName::MOV      , {Ew         , Sw        }}},
	{0x8D,		{InstructionName::LEA      , {Gv         , MM        }}},
	{0x8E,		{InstructionName::MOV      , {Sw         , Ew        }}},	//no test
	{0x8F,		{GroupName::_1A            , {Ev_d64                 }}},
	{0x90,		{InstructionName::NOP      , {                       }}},
	{0x91,		{InstructionName::XCHG     , {rAX        , rCX_r9    }}},
	{0x92,		{InstructionName::XCHG     , {rAX        , rDX_r10   }}},
	{0x93,		{InstructionName::XCHG     , {rAX        , rBX_r11   }}},
	{0x94,		{InstructionName::XCHG     , {rAX        , rSP_r12   }}},
	{0x95,		{InstructionName::XCHG     , {rAX        , rBP_r13   }}},
	{0x96,		{InstructionName::XCHG     , {rAX        , rSI_r14   }}},
	{0x97,		{InstructionName::XCHG     , {rAX        , rDI_r15   }}},
	{0x98,		{InstructionName::CWDE     , {                       }}},
	{0x99,		{InstructionName::CDQ      , {                       }}},
//	{0x9A,		{InstructionName::         , {                       }}},	// wait add
//	{0x9B,		{InstructionName::         , {                       }}},	// wait add
	{0x9C,		{InstructionName::PUSHFD   , {                       }}},
	{0x9D,		{InstructionName::POPFD    , {                       }}},	//no test
	{0x9E,		{InstructionName::SAHF     , {                       }}},
	{0x9F,		{InstructionName::LAHF     , {                       }}},
	{0xA0,		{InstructionName::MOV      , {F_AL       , Ob        }}},
	{0xA1,		{InstructionName::MOV      , {rAX        , Ov        }}},
	{0xA2,		{InstructionName::MOV      , {Ob         , F_AL      }}},
	{0xA3,		{InstructionName::MOV      , {Ov         , rAX       }}},
	{0xA4,		{InstructionName::MOVS     , {Yb         , Xb        }}},
	{0xA5,		{InstructionName::MOVS     , {Yv         , Xv        }}},
	{0xA6,		{InstructionName::CMPS     , {Xb         , Yb        }}},
	{0xA7,		{InstructionName::CMPS     , {Xv         , Yv        }}},
	{0xA8,		{InstructionName::TEST     , {F_AL       , Ib        }}},	//nt
	{0xA9,		{InstructionName::TEST     , {rAX        , Iz        }}},	//nt
	{0xAA,		{InstructionName::STOS     , {Yb         , F_AL      }}},
	{0xAB,		{InstructionName::STOS     , {Yv         , rAX       }}},
	{0xAC,		{InstructionName::LODS     , {F_AL       , Xb        }}},
	{0xAD,		{InstructionName::LODS     , {rAX        , Xv        }}},
	{0xAE,		{InstructionName::SCAS     , {F_AL       , Yb        }}},
	{0xAF,		{InstructionName::SCAS     , {rAX        , Yv        }}},	// should Yv ?
	{0xB0,		{InstructionName::MOV      , {F_AL_R8L   , Ib        }}},
	{0xB1,		{InstructionName::MOV      , {F_CL_R9L   , Ib        }}},
	{0xB2,		{InstructionName::MOV      , {F_DL_R10L  , Ib        }}},
	{0xB3,		{InstructionName::MOV      , {F_BL_R11L  , Ib        }}},
	{0xB4,		{InstructionName::MOV      , {F_AH_R12L  , Ib        }}},
	{0xB5,		{InstructionName::MOV      , {F_CH_R13L  , Ib        }}},
	{0xB6,		{InstructionName::MOV      , {F_DH_R14L  , Ib        }}},
	{0xB7,		{InstructionName::MOV      , {F_BH_R15L  , Ib        }}},
	{0xB8,		{InstructionName::MOV      , {rAX_r8     , Iv        }}},
	{0xB9,		{InstructionName::MOV      , {rCX_r9     , Iv        }}},
	{0xBA,		{InstructionName::MOV      , {rDX_r10    , Iv        }}},
	{0xBB,		{InstructionName::MOV      , {rBX_r11    , Iv        }}},
	{0xBC,		{InstructionName::MOV      , {rSP_r12    , Iv        }}},
	{0xBD,		{InstructionName::MOV      , {rBP_r13    , Iv        }}},
	{0xBE,		{InstructionName::MOV      , {rSI_r14    , Iv        }}},
	{0xBF,		{InstructionName::MOV      , {rDI_r15    , Iv        }}},
	{0xC0,		{GroupName::_2             , {Eb         , Ib        }}},
	{0xC1,		{GroupName::_2             , {Ev         , Ib        }}},
	{0xC2,		{InstructionName::RETN     , {Iw                     }}},
	{0xC3,		{InstructionName::RETN     , {                       }}},
	{0xC4,		{InstructionName::LES      , {Gz         , Mp        }}},
	{0xC5,		{InstructionName::LDS      , {Gz         , Mp        }}},
	{0xC6,		{GroupName::_11            , {Eb         , Ib        }}},
	{0xC7,		{GroupName::_11            , {Ev         , Iz        }}},
	{0xC8,		{InstructionName::ENTER    , {Iw         , Ib        }}},
	{0xC9,		{InstructionName::LEAVE    , {                       }}},
	{0xCA,		{InstructionName::RETF     , {Iw                     }}},	// no test
	{0xCB,		{InstructionName::RETF     , {                       }}},	// no test
	{0xCC,		{InstructionName::INT3     , {                       }}},
	{0xCD,		{InstructionName::INT      , {Ib                     }}},
	{0xCE,		{InstructionName::INTO     , {                       }}},	// no test
	{0xCF,		{InstructionName::IRETD    , {                       }}},
	{0xD0,		{GroupName::_2             , {Eb         , F_1       }}},
	{0xD1,		{GroupName::_2             , {Ev         , F_1       }}},
	{0xD2,		{GroupName::_2             , {Eb         , F_CL      }}},
	{0xD3,		{GroupName::_2             , {Ev         , F_CL      }}},
	{0xD4,		{InstructionName::AAM      , {Ib                     }}},
	{0xD5,		{InstructionName::AAD      , {Ib                     }}},	// no test
	{0xD7,		{InstructionName::XLAT     , {                       }}},
	{0xD8,		{MainEntryType::ESCAPE                                }},
	{0xD9,		{MainEntryType::ESCAPE                                }},
	{0xDA,		{MainEntryType::ESCAPE                                }},
	{0xDB,		{MainEntryType::ESCAPE                                }},
	{0xDC,		{MainEntryType::ESCAPE                                }},
	{0xDD,		{MainEntryType::ESCAPE                                }},
	{0xDE,		{MainEntryType::ESCAPE                                }},
	{0xDF,		{MainEntryType::ESCAPE                                }},
	{0xE0,		{InstructionName::LOOPNZ   , {Jb                     }}},
	{0xE1,		{InstructionName::LOOPZ    , {Jb                     }}},	// no test
	{0xE2,		{InstructionName::LOOP     , {Jb                     }}},	// no test
	{0xE3,		{InstructionName::JECXZ    , {Jb                     }}},
	{0xE4,		{InstructionName::INX       , {F_AL       , Ib        }}},	// no test
	{0xE5,		{InstructionName::INX       , {eAX        , Ib        }}},	// no test
	{0xE6,		{InstructionName::OUTX      , {Ib         , F_AL      }}},	// no test
	{0xE7,		{InstructionName::OUTX      , {Ib         , eAX       }}},
	{0xE8,		{InstructionName::CALL     , {Jz                     }}},
	{0xE9,		{InstructionName::JMP_NEAR , {Jz                     }}},
	{0xEA,		{InstructionName::JMP_FAR  , {Ap                     }}},
	{0xEB,		{InstructionName::JMP_SHORT, {Jb                     }}},
	{0xEC,		{InstructionName::INX       , {F_AL       , F_DX      }}},
	{0xED,		{InstructionName::INX       , {eAX        , F_DX      }}},
	{0xEE,		{InstructionName::OUTX      , {F_DX       , F_AL      }}},
	{0xEF,		{InstructionName::OUTX      , {F_DX       , eAX       }}},
	{0xF4,		{InstructionName::HLT      , {                       }}},	// no test
	{0xF5,		{InstructionName::CMC      , {                       }}},	// no test
	{0xF6,		{GroupName::_3_F6          , {Eb                     }}},
	{0xF7,		{GroupName::_3_F7          , {Ev                     }}},
	{0xF8,		{InstructionName::CLC      , {                       }}},
	{0xF9,		{InstructionName::STC      , {                       }}},
	{0xFA,		{InstructionName::CLI      , {                       }}},
	{0xFB,		{InstructionName::STI      , {                       }}},
	{0xFC,		{InstructionName::CLD      , {                       }}},
	{0xFD,		{InstructionName::STD      , {                       }}},
	{0xFE,		{GroupName::_4             , {                       }}},
	{0xFF,		{GroupName::_5             , {                       }}},
};

const std::map <Byte, OpcodeMain> OpcodeTable::_main_0FXX_diff_x64
{
	{0x05,		{InstructionName::SYSCALL  , {                }}},
	{0x07,		{InstructionName::SYSRET   , {                }}},
};
const std::map <Byte, OpcodeMain> OpcodeTable::_main_0FXX
{
	{0x00,		{GroupName::_6             , {                }}},
	{0x01,		{GroupName::_7             , {                }}},
	{0x08,		{InstructionName::INVD     , {                }}},
	{0x09,		{InstructionName::WBINVD   , {                }}},
	{0x0B,		{InstructionName::UD2      , {                }}},
	{0x18,		{GroupName::_16            , {                }}},
	{0x1F,		{InstructionName::NOP      , {Ev              }}},
	{0x20,		{InstructionName::MOV      , {Rd  , Cd        }}},
	{0x21,		{InstructionName::MOV      , {Rd  , Dd        }}},
	{0x22,		{InstructionName::MOV      , {Cd  , Rd        }}},
	{0x23,		{InstructionName::MOV      , {Dd  , Rd        }}},
	{0x30,		{InstructionName::WRMSR    , {                }}},
	{0x31,		{InstructionName::RDTSC    , {                }}},
	{0x32,		{InstructionName::RDMSR    , {                }}},
	{0x33,		{InstructionName::RDPMC    , {                }}},
	{0x34,		{InstructionName::SYSENTER , {                }}},
	{0x35,		{InstructionName::SYSEXIT  , {                }}},
	{0x37,		{InstructionName::GETSEC   , {                }}},
	{0x40,		{InstructionName::CMOVO    , {Gv  , Ev        }}},
	{0x41,		{InstructionName::CMOVNO   , {Gv  , Ev        }}},
	{0x42,		{InstructionName::CMOVB    , {Gv  , Ev        }}},
	{0x43,		{InstructionName::CMOVAE   , {Gv  , Ev        }}},
	{0x44,		{InstructionName::CMOVE    , {Gv  , Ev        }}},
	{0x45,		{InstructionName::CMOVNE   , {Gv  , Ev        }}},
	{0x46,		{InstructionName::CMOVBE   , {Gv  , Ev        }}},
	{0x47,		{InstructionName::CMOVA    , {Gv  , Ev        }}},
	{0x48,		{InstructionName::CMOVS    , {Gv  , Ev        }}},
	{0x49,		{InstructionName::CMOVNS   , {Gv  , Ev        }}},
	{0x4A,		{InstructionName::CMOVPE   , {Gv  , Ev        }}},
	{0x4B,		{InstructionName::CMOVPO   , {Gv  , Ev        }}},
	{0x4C,		{InstructionName::CMOVL    , {Gv  , Ev        }}},
	{0x4D,		{InstructionName::CMOVGE   , {Gv  , Ev        }}},
	{0x4E,		{InstructionName::CMOVLE   , {Gv  , Ev        }}},
	{0x4F,		{InstructionName::CMOVG    , {Gv  , Ev        }}},
	{0x78,		{InstructionName::VMREAD   , {Ey  , Gy        }}},
	{0x79,		{InstructionName::VMWRITE  , {Gy  , Ey        }}},
	{0x80,		{InstructionName::JO       , {Jz              }}},	// no test
	{0x81,		{InstructionName::JNO      , {Jz              }}},	// no test
	{0x82,		{InstructionName::JB       , {Jz              }}},	// no test
	{0x83,		{InstructionName::JAE      , {Jz              }}},	// no test
	{0x84,		{InstructionName::JE       , {Jz              }}},	// no test
	{0x85,		{InstructionName::JNZ      , {Jz              }}},	// no test
	{0x86,		{InstructionName::JBE      , {Jz              }}},	// no test
	{0x87,		{InstructionName::JA       , {Jz              }}},	// no test
	{0x88,		{InstructionName::JS       , {Jz              }}},	// no test
	{0x89,		{InstructionName::JNS      , {Jz              }}},	// no test
	{0x8A,		{InstructionName::JPE      , {Jz              }}},	// no test
	{0x8B,		{InstructionName::JPO      , {Jz              }}},	// no test
	{0x8C,		{InstructionName::JL       , {Jz              }}},	// no test
	{0x8D,		{InstructionName::JGE      , {Jz              }}},	// no test
	{0x8E,		{InstructionName::JLE      , {Jz              }}},	// no test
	{0x8F,		{InstructionName::JG       , {Jz              }}},	// no test
	{0x90,		{InstructionName::SETO     , {Eb              }}},
	{0x91,		{InstructionName::SETNO    , {Eb              }}},
	{0x92,		{InstructionName::SETB     , {Eb              }}},
	{0x93,		{InstructionName::SETAE    , {Eb              }}},
	{0x94,		{InstructionName::SETE     , {Eb              }}},
	{0x95,		{InstructionName::SETNZ    , {Eb              }}},
	{0x96,		{InstructionName::SETBE    , {Eb              }}},
	{0x97,		{InstructionName::SETA     , {Eb              }}},
	{0x98,		{InstructionName::SETS     , {Eb              }}},
	{0x99,		{InstructionName::SETNS    , {Eb              }}},
	{0x9A,		{InstructionName::SETPE    , {Eb              }}},
	{0x9B,		{InstructionName::SETPO    , {Eb              }}},
	{0x9C,		{InstructionName::SETL     , {Eb              }}},
	{0x9D,		{InstructionName::SETGE    , {Eb              }}},
	{0x9E,		{InstructionName::SETLE    , {Eb              }}},
	{0x9F,		{InstructionName::SETG     , {Eb              }}},
	{0xA0,		{InstructionName::PUSH     , {F_FS            }}},
	{0xA1,		{InstructionName::POP      , {F_FS            }}},
	{0xA2,		{InstructionName::CPUID    , {                }}},
	{0xA3,		{InstructionName::BT       , {Ev  , Gv        }}},
	{0xA4,		{InstructionName::SHLD     , {Ev  , Gv  , Ib  }}},
	{0xA5,		{InstructionName::SHLD     , {Ev  , Gv  , F_CL}}},
	{0xA8,		{InstructionName::PUSH     , {F_GS            }}},
	{0xA9,		{InstructionName::POP      , {F_GS            }}},
	{0xAA,		{InstructionName::RSM      , {                }}},
	{0xAB,		{InstructionName::BTS      , {Ev  , Gv        }}},
	{0xAC,		{InstructionName::SHRD     , {Ev  , Gv  , Ib  }}},
	{0xAD,		{InstructionName::SHRD     , {Ev  , Gv  , F_CL}}},
	{0xAF,		{InstructionName::IMUL     , {Gv  , Ev        }}},
	{0xB0,		{InstructionName::CMPXCHG  , {Eb  , Gb        }}},
	{0xB1,		{InstructionName::CMPXCHG  , {Ev  , Gv        }}},
	{0xB2,		{InstructionName::LSS      , {Gv  , Mp        }}},
	{0xB3,		{InstructionName::BTR      , {Ev  , Gv        }}},
	{0xB4,		{InstructionName::LFS      , {Gv  , Mp        }}},
	{0xB5,		{InstructionName::LGS      , {Gv  , Mp        }}},
	{0xB6,		{InstructionName::MOVZX    , {Gv  , Eb        }}},
	{0xB7,		{InstructionName::MOVZX    , {Gv  , Ew        }}},
	{0xBA,		{GroupName::_8             , {Ev  , Ib        }}},
	{0xBB,		{InstructionName::BTC      , {Ev  , Gv        }}},
	{0xBC,		{InstructionName::BSF      , {Gv  , Ev        }}},
	{0xBD,		{InstructionName::BSR      , {Gv  , Ev        }}},
	{0xBE,		{InstructionName::MOVSX    , {Gv  , Eb        }}},
	{0xBF,		{InstructionName::MOVSX    , {Gv  , Ew        }}},
	{0xC0,		{InstructionName::XADD     , {Eb  , Gb        }}},
	{0xC1,		{InstructionName::XADD     , {Ev  , Gv        }}},
	{0xC7,		{GroupName::_9             , {                }}},
	{0xC8,		{InstructionName::BSWAP    , {rAX_r8          }}},	//nt
	{0xC9,		{InstructionName::BSWAP    , {rCX_r9          }}},	//nt
	{0xCA,		{InstructionName::BSWAP    , {rDX_r10         }}},	//nt
	{0xCB,		{InstructionName::BSWAP    , {rBX_r11         }}},	//nt
	{0xCC,		{InstructionName::BSWAP    , {rSP_r12         }}},	//nt
	{0xCD,		{InstructionName::BSWAP    , {rBP_r13         }}},	//nt
	{0xCE,		{InstructionName::BSWAP    , {rSI_r14         }}},	//nt
	{0xCF,		{InstructionName::BSWAP    , {rDI_r15         }}},	//nt
};

const std::map <
	GroupName,
	std::map <Byte, OpcodeGroup>> OpcodeTable::_group
{
	{GroupName::_1, {
		{0b000, {InstructionName::ADD  , {}}},
		{0b001, {InstructionName::OR   , {}}},
		{0b010, {InstructionName::ADC  , {}}},
		{0b011, {InstructionName::SBB  , {}}},
		{0b100, {InstructionName::AND  , {}}},
		{0b101, {InstructionName::SUB  , {}}},
		{0b110, {InstructionName::XOR  , {}}},
		{0b111, {InstructionName::CMP  , {}}},
	}},
	{GroupName::_1A, {
		{0b000, {InstructionName::POP  , {}}},
	}},
	{GroupName::_2, {
		{0b000, {InstructionName::ROL  , {}}},
		{0b001, {InstructionName::ROR  , {}}},
		{0b010, {InstructionName::RCL  , {}}},
		{0b011, {InstructionName::RCR  , {}}},
		{0b100, {InstructionName::SHL  , {}}},
		{0b101, {InstructionName::SHR  , {}}},
		{0b111, {InstructionName::SAR  , {}}},
	}},
	{GroupName::_3_F6, {
		{0b000, {InstructionName::TEST , {Ib}}},
		{0b010, {InstructionName::NOT  , {}}},
		{0b011, {InstructionName::NEG  , {}}},			// no test
		{0b100, {InstructionName::MUL  , {}}},			// no test
		{0b101, {InstructionName::IMUL , {}}},			// no test
		{0b110, {InstructionName::DIV  , {}}},			// no test
		{0b111, {InstructionName::IDIV , {}}},
	}},
	{GroupName::_3_F7, {
		{0b000, {InstructionName::TEST , {Iz}}},
		{0b010, {InstructionName::NOT  , {}}},
		{0b011, {InstructionName::NEG  , {}}},			// no test
		{0b100, {InstructionName::MUL  , {}}},			// no test
		{0b101, {InstructionName::IMUL , {}}},			// no test
		{0b110, {InstructionName::DIV  , {}}},			// no test
		{0b111, {InstructionName::IDIV , {}}},
	}},
	{GroupName::_4, {
		{0b000, {InstructionName::INC  , {Eb}}},
		{0b001, {InstructionName::DEC  , {Eb}}},
	}},
	{GroupName::_5, {
		{0b000, {InstructionName::INC  , {Ev}}},
		{0b001, {InstructionName::DEC  , {Ev}}},
		{0b010, {InstructionName::CALLN, {Ev}}},
		{0b011, {InstructionName::CALLF, {Ep}}},			// should Mp ?
		{0b100, {InstructionName::JMPN , {Ev}}},
		{0b101, {InstructionName::JMPF , {Mp}}},
		{0b110, {InstructionName::PUSH , {Ev}}},
	}},
	{GroupName::_6, {
		{0b000, {InstructionName::SLDT , {RvMw}}},
		{0b001, {InstructionName::STR  , {RvMw}}},
		{0b010, {InstructionName::LLDT , {Ew}}},
		{0b011, {InstructionName::LTR  , {Ew}}},
		{0b100, {InstructionName::VERR , {Ew}}},
		{0b101, {InstructionName::VERW , {Ew}}},
	}},
	{GroupName::_7, {
		{0b000, {InstructionName::SGDT  , {Ms}}},
		{0b001, {InstructionName::SIDT  , {Ms}}},
		{0b010, {InstructionName::LGDT  , {Ms}}},
		{0b011, {InstructionName::LIDT  , {Ms}}},
		{0b100, {InstructionName::SMSW  , {RvMw}}},
		{0b110, {InstructionName::LMSW  , {Ew}}},
		{0b111, {InstructionName::INVLPG, {Mb}}},
	}},
	{GroupName::_8, {
		{0b100, {InstructionName::BT    , {}}},
		{0b101, {InstructionName::BTS   , {}}},
		{0b110, {InstructionName::BTR   , {}}},
		{0b111, {InstructionName::BTC   , {}}},
	}},
	{GroupName::_9, {
		{0b001, {InstructionName::CMPXCHG8B, {Mq}}},
		{0b110, {InstructionName::RDRAND   , {Rv}}},
	}},
	{GroupName::_11, {
		{0b000, {InstructionName::MOV  , {}}},
	}},
	{GroupName::_16, {
		{0b000, {InstructionName::PREFETCHNTA, {Mb}}},
		{0b001, {InstructionName::PREFETCHT0 , {Mb}}},
		{0b010, {InstructionName::PREFETCHT1 , {Mb}}},
		{0b011, {InstructionName::PREFETCHT2 , {Mb}}},
	}},
};
const std::map <Byte /*opcode*/,
	std::map <Byte /*modrm*/, OpcodeMap>> OpcodeTable::_escape_11XXXXXX
{
	{0xD8, {
		{0xC0, {InstructionName::FADD , {F_ST0, F_ST0}}},
		{0xC1, {InstructionName::FADD , {F_ST0, F_ST1}}},
		{0xC2, {InstructionName::FADD , {F_ST0, F_ST2}}},
		{0xC3, {InstructionName::FADD , {F_ST0, F_ST3}}},
		{0xC4, {InstructionName::FADD , {F_ST0, F_ST4}}},
		{0xC5, {InstructionName::FADD , {F_ST0, F_ST5}}},
		{0xC6, {InstructionName::FADD , {F_ST0, F_ST6}}},
		{0xC7, {InstructionName::FADD , {F_ST0, F_ST7}}},
		{0xC8, {InstructionName::FMUL , {F_ST0, F_ST0}}},
		{0xC9, {InstructionName::FMUL , {F_ST0, F_ST1}}},
		{0xCA, {InstructionName::FMUL , {F_ST0, F_ST2}}},
		{0xCB, {InstructionName::FMUL , {F_ST0, F_ST3}}},
		{0xCC, {InstructionName::FMUL , {F_ST0, F_ST4}}},
		{0xCD, {InstructionName::FMUL , {F_ST0, F_ST5}}},
		{0xCE, {InstructionName::FMUL , {F_ST0, F_ST6}}},
		{0xCF, {InstructionName::FMUL , {F_ST0, F_ST7}}},
		{0xD0, {InstructionName::FCOM , {F_ST0       }}},
		{0xD1, {InstructionName::FCOM , {F_ST1       }}},
		{0xD2, {InstructionName::FCOM , {F_ST2       }}},
		{0xD3, {InstructionName::FCOM , {F_ST3       }}},
		{0xD4, {InstructionName::FCOM , {F_ST4       }}},
		{0xD5, {InstructionName::FCOM , {F_ST5       }}},
		{0xD6, {InstructionName::FCOM , {F_ST6       }}},
		{0xD7, {InstructionName::FCOM , {F_ST7       }}},
		{0xD8, {InstructionName::FCOMP, {F_ST0       }}},
		{0xD9, {InstructionName::FCOMP, {F_ST1       }}},
		{0xDA, {InstructionName::FCOMP, {F_ST2       }}},
		{0xDB, {InstructionName::FCOMP, {F_ST3       }}},
		{0xDC, {InstructionName::FCOMP, {F_ST4       }}},
		{0xDD, {InstructionName::FCOMP, {F_ST5       }}},
		{0xDE, {InstructionName::FCOMP, {F_ST6       }}},
		{0xDF, {InstructionName::FCOMP, {F_ST7       }}},
		{0xE0, {InstructionName::FSUB , {F_ST0, F_ST0}}},
		{0xE1, {InstructionName::FSUB , {F_ST0, F_ST1}}},
		{0xE2, {InstructionName::FSUB , {F_ST0, F_ST2}}},
		{0xE3, {InstructionName::FSUB , {F_ST0, F_ST3}}},
		{0xE4, {InstructionName::FSUB , {F_ST0, F_ST4}}},
		{0xE5, {InstructionName::FSUB , {F_ST0, F_ST5}}},
		{0xE6, {InstructionName::FSUB , {F_ST0, F_ST6}}},
		{0xE7, {InstructionName::FSUB , {F_ST0, F_ST7}}},
		{0xE8, {InstructionName::FSUBR, {F_ST0, F_ST0}}},
		{0xE9, {InstructionName::FSUBR, {F_ST0, F_ST1}}},
		{0xEA, {InstructionName::FSUBR, {F_ST0, F_ST2}}},
		{0xEB, {InstructionName::FSUBR, {F_ST0, F_ST3}}},
		{0xEC, {InstructionName::FSUBR, {F_ST0, F_ST4}}},
		{0xED, {InstructionName::FSUBR, {F_ST0, F_ST5}}},
		{0xEE, {InstructionName::FSUBR, {F_ST0, F_ST6}}},
		{0xEF, {InstructionName::FSUBR, {F_ST0, F_ST7}}},
		{0xF0, {InstructionName::FDIV , {F_ST0, F_ST0}}},
		{0xF1, {InstructionName::FDIV , {F_ST0, F_ST1}}},
		{0xF2, {InstructionName::FDIV , {F_ST0, F_ST2}}},
		{0xF3, {InstructionName::FDIV , {F_ST0, F_ST3}}},
		{0xF4, {InstructionName::FDIV , {F_ST0, F_ST4}}},
		{0xF5, {InstructionName::FDIV , {F_ST0, F_ST5}}},
		{0xF6, {InstructionName::FDIV , {F_ST0, F_ST6}}},
		{0xF7, {InstructionName::FDIV , {F_ST0, F_ST7}}},
		{0xF8, {InstructionName::FDIVR, {F_ST0, F_ST0}}},
		{0xF9, {InstructionName::FDIVR, {F_ST0, F_ST1}}},
		{0xFA, {InstructionName::FDIVR, {F_ST0, F_ST2}}},
		{0xFB, {InstructionName::FDIVR, {F_ST0, F_ST3}}},
		{0xFC, {InstructionName::FDIVR, {F_ST0, F_ST4}}},
		{0xFD, {InstructionName::FDIVR, {F_ST0, F_ST5}}},
		{0xFE, {InstructionName::FDIVR, {F_ST0, F_ST6}}},
		{0xFF, {InstructionName::FDIVR, {F_ST0, F_ST7}}},
	}},
	{0xD9, {
		{0xC0, {InstructionName::FLD  , {F_ST0}}},
		{0xC1, {InstructionName::FLD  , {F_ST1}}},
		{0xC2, {InstructionName::FLD  , {F_ST2}}},
		{0xC3, {InstructionName::FLD  , {F_ST3}}},
		{0xC4, {InstructionName::FLD  , {F_ST4}}},
		{0xC5, {InstructionName::FLD  , {F_ST5}}},
		{0xC6, {InstructionName::FLD  , {F_ST6}}},
		{0xC7, {InstructionName::FLD  , {F_ST7}}},
		{0xC8, {InstructionName::FXCH , {F_ST0}}},
		{0xC9, {InstructionName::FXCH , {F_ST1}}},
		{0xCA, {InstructionName::FXCH , {F_ST2}}},
		{0xCB, {InstructionName::FXCH , {F_ST3}}},
		{0xCC, {InstructionName::FXCH , {F_ST4}}},
		{0xCD, {InstructionName::FXCH , {F_ST5}}},
		{0xCE, {InstructionName::FXCH , {F_ST6}}},
		{0xCF, {InstructionName::FXCH , {F_ST7}}},
		{0xD0, {InstructionName::FNOP , {     }}},
		{0xE0, {InstructionName::FCHS , {     }}},
		{0xE1, {InstructionName::FABS , {     }}},
		{0xE4, {InstructionName::FTST , {     }}},
		{0xE5, {InstructionName::FXAM , {     }}},
		{0xF0, {InstructionName::F2XM1, {     }}},
		{0xF1, {InstructionName::FYL2X, {     }}},
	}},
	{0xDA, {
		{0xC0, {InstructionName::FCMOVB , {F_ST0, F_ST0}}},
		{0xC1, {InstructionName::FCMOVB , {F_ST0, F_ST1}}},
		{0xC2, {InstructionName::FCMOVB , {F_ST0, F_ST2}}},
		{0xC3, {InstructionName::FCMOVB , {F_ST0, F_ST3}}},
		{0xC4, {InstructionName::FCMOVB , {F_ST0, F_ST4}}},
		{0xC5, {InstructionName::FCMOVB , {F_ST0, F_ST5}}},
		{0xC6, {InstructionName::FCMOVB , {F_ST0, F_ST6}}},
		{0xC7, {InstructionName::FCMOVB , {F_ST0, F_ST7}}},
		{0xC8, {InstructionName::FCMOVE , {F_ST0, F_ST0}}},
		{0xC9, {InstructionName::FCMOVE , {F_ST0, F_ST1}}},
		{0xCA, {InstructionName::FCMOVE , {F_ST0, F_ST2}}},
		{0xCB, {InstructionName::FCMOVE , {F_ST0, F_ST3}}},
		{0xCC, {InstructionName::FCMOVE , {F_ST0, F_ST4}}},
		{0xCD, {InstructionName::FCMOVE , {F_ST0, F_ST5}}},
		{0xCE, {InstructionName::FCMOVE , {F_ST0, F_ST6}}},
		{0xCF, {InstructionName::FCMOVE , {F_ST0, F_ST7}}},
		{0xD0, {InstructionName::FCMOVBE, {F_ST0, F_ST0}}},
		{0xD1, {InstructionName::FCMOVBE, {F_ST0, F_ST1}}},
		{0xD2, {InstructionName::FCMOVBE, {F_ST0, F_ST2}}},
		{0xD3, {InstructionName::FCMOVBE, {F_ST0, F_ST3}}},
		{0xD4, {InstructionName::FCMOVBE, {F_ST0, F_ST4}}},
		{0xD5, {InstructionName::FCMOVBE, {F_ST0, F_ST5}}},
		{0xD6, {InstructionName::FCMOVBE, {F_ST0, F_ST6}}},
		{0xD7, {InstructionName::FCMOVBE, {F_ST0, F_ST7}}},
		{0xD8, {InstructionName::FCMOVU , {F_ST0, F_ST0}}},
		{0xD9, {InstructionName::FCMOVU , {F_ST0, F_ST1}}},
		{0xDA, {InstructionName::FCMOVU , {F_ST0, F_ST2}}},
		{0xDB, {InstructionName::FCMOVU , {F_ST0, F_ST3}}},
		{0xDC, {InstructionName::FCMOVU , {F_ST0, F_ST4}}},
		{0xDD, {InstructionName::FCMOVU , {F_ST0, F_ST5}}},
		{0xDE, {InstructionName::FCMOVU , {F_ST0, F_ST6}}},
		{0xDF, {InstructionName::FCMOVU , {F_ST0, F_ST7}}},
		{0xE9, {InstructionName::FUCOMPP, {            }}},
	}},
	{0xDB, {
		{0xC0, {InstructionName::FCMOVNB , {F_ST0, F_ST0}}},
		{0xC1, {InstructionName::FCMOVNB , {F_ST0, F_ST1}}},
		{0xC2, {InstructionName::FCMOVNB , {F_ST0, F_ST2}}},
		{0xC3, {InstructionName::FCMOVNB , {F_ST0, F_ST3}}},
		{0xC4, {InstructionName::FCMOVNB , {F_ST0, F_ST4}}},
		{0xC5, {InstructionName::FCMOVNB , {F_ST0, F_ST5}}},
		{0xC6, {InstructionName::FCMOVNB , {F_ST0, F_ST6}}},
		{0xC7, {InstructionName::FCMOVNB , {F_ST0, F_ST7}}},
		{0xC8, {InstructionName::FCMOVNE , {F_ST0, F_ST0}}},
		{0xC9, {InstructionName::FCMOVNE , {F_ST0, F_ST1}}},
		{0xCA, {InstructionName::FCMOVNE , {F_ST0, F_ST2}}},
		{0xCB, {InstructionName::FCMOVNE , {F_ST0, F_ST3}}},
		{0xCC, {InstructionName::FCMOVNE , {F_ST0, F_ST4}}},
		{0xCD, {InstructionName::FCMOVNE , {F_ST0, F_ST5}}},
		{0xCE, {InstructionName::FCMOVNE , {F_ST0, F_ST6}}},
		{0xCF, {InstructionName::FCMOVNE , {F_ST0, F_ST7}}},
		{0xD0, {InstructionName::FCMOVNBE, {F_ST0, F_ST0}}},
		{0xD1, {InstructionName::FCMOVNBE, {F_ST0, F_ST1}}},
		{0xD2, {InstructionName::FCMOVNBE, {F_ST0, F_ST2}}},
		{0xD3, {InstructionName::FCMOVNBE, {F_ST0, F_ST3}}},
		{0xD4, {InstructionName::FCMOVNBE, {F_ST0, F_ST4}}},
		{0xD5, {InstructionName::FCMOVNBE, {F_ST0, F_ST5}}},
		{0xD6, {InstructionName::FCMOVNBE, {F_ST0, F_ST6}}},
		{0xD7, {InstructionName::FCMOVNBE, {F_ST0, F_ST7}}},
		{0xD8, {InstructionName::FCMOVNU , {F_ST0, F_ST0}}},
		{0xD9, {InstructionName::FCMOVNU , {F_ST0, F_ST1}}},
		{0xDA, {InstructionName::FCMOVNU , {F_ST0, F_ST2}}},
		{0xDB, {InstructionName::FCMOVNU , {F_ST0, F_ST3}}},
		{0xDC, {InstructionName::FCMOVNU , {F_ST0, F_ST4}}},
		{0xDD, {InstructionName::FCMOVNU , {F_ST0, F_ST5}}},
		{0xDE, {InstructionName::FCMOVNU , {F_ST0, F_ST6}}},
		{0xDF, {InstructionName::FCMOVNU , {F_ST0, F_ST7}}},
		{0xE2, {InstructionName::FCLEX   , {            }}},
	}},
	{0xDD, {
		{0xE0, {InstructionName::FUCOM, {F_ST0}}},
		{0xE1, {InstructionName::FUCOM, {F_ST1}}},
		{0xE2, {InstructionName::FUCOM, {F_ST2}}},
		{0xE3, {InstructionName::FUCOM, {F_ST3}}},
		{0xE4, {InstructionName::FUCOM, {F_ST4}}},
		{0xE5, {InstructionName::FUCOM, {F_ST5}}},
		{0xE6, {InstructionName::FUCOM, {F_ST6}}},
		{0xE7, {InstructionName::FUCOM, {F_ST7}}},
	}},
	{0xDF, {
		{0xF0, {InstructionName::FCOMIP, {F_ST0, F_ST0}}},
		{0xF1, {InstructionName::FCOMIP, {F_ST0, F_ST1}}},
		{0xF2, {InstructionName::FCOMIP, {F_ST0, F_ST2}}},
		{0xF3, {InstructionName::FCOMIP, {F_ST0, F_ST3}}},
		{0xF4, {InstructionName::FCOMIP, {F_ST0, F_ST4}}},
		{0xF5, {InstructionName::FCOMIP, {F_ST0, F_ST5}}},
		{0xF6, {InstructionName::FCOMIP, {F_ST0, F_ST6}}},
		{0xF7, {InstructionName::FCOMIP, {F_ST0, F_ST7}}},
	}},
};
const std::map <
	Byte /*opcode*/,
	std::map <Byte /*item*/, OpcodeMap>> OpcodeTable::_escape_non_11XXXXXX
{
	{0xD8, {
		{0b000, {InstructionName::FADD , {single_real}}},
		{0b001, {InstructionName::FMUL , {single_real}}},
		{0b010, {InstructionName::FCOM , {single_real}}},
		{0b011, {InstructionName::FCOMP, {single_real}}},
		{0b100, {InstructionName::FSUB , {single_real}}},
		{0b101, {InstructionName::FSUBR, {single_real}}},
		{0b110, {InstructionName::FDIV , {single_real}}},
		{0b111, {InstructionName::FDIVR, {single_real}}},
	}},
	{0xD9, {
		{0b000, {InstructionName::FLD   , {single_real   }}},
		{0b010, {InstructionName::FST   , {single_real   }}},
		{0b011, {InstructionName::FSTP  , {single_real   }}},
		{0b100, {InstructionName::FLDENV, {_14_or_28_byte}}},
		{0b101, {InstructionName::FLDCW , {_2_byte       }}},
		{0b110, {InstructionName::FSTENV, {_14_or_28_byte}}},
		{0b111, {InstructionName::FSTCW , {_2_byte       }}},
	}},
	{0xDA, {
		{0b000, {InstructionName::FIADD , {dword_integer}}},
		{0b001, {InstructionName::FIMUL , {dword_integer}}},
		{0b010, {InstructionName::FICOM , {dword_integer}}},
		{0b011, {InstructionName::FICOMP, {dword_integer}}},
		{0b100, {InstructionName::FISUB , {dword_integer}}},
		{0b101, {InstructionName::FISUBR, {dword_integer}}},
		{0b110, {InstructionName::FIDIV , {dword_integer}}},
		{0b111, {InstructionName::FIDIVR, {dword_integer}}},
	}},
	{0xDB, {
		{0b000, {InstructionName::FILD  , {dword_integer}}},
		{0b001, {InstructionName::FISTTP, {dword_integer}}},
		{0b010, {InstructionName::FIST  , {dword_integer}}},
		{0b011, {InstructionName::FISTP , {dword_integer}}},
		{0b101, {InstructionName::FLD   , {extended_real}}},
		{0b111, {InstructionName::FSTP  , {extended_real}}},
	}},
	{0xDC, {
		{0b000, {InstructionName::FADD , {double_real}}},
		{0b001, {InstructionName::FMUL , {double_real}}},
		{0b010, {InstructionName::FCOM , {double_real}}},
		{0b011, {InstructionName::FCOMP, {double_real}}},
		{0b100, {InstructionName::FSUB , {double_real}}},
		{0b101, {InstructionName::FSUBR, {double_real}}},
		{0b110, {InstructionName::FDIV , {double_real}}},
		{0b111, {InstructionName::FDIVR, {double_real}}},
	}},
	{0xDD, {
		{0b000, {InstructionName::FLD   , {double_real    }}},
		{0b001, {InstructionName::FISTTP, {qword_integer  }}},
		{0b010, {InstructionName::FST   , {double_real    }}},
		{0b011, {InstructionName::FSTP  , {double_real    }}},
		{0b100, {InstructionName::FRSTOR, {_94_or_108_byte}}},
		{0b110, {InstructionName::FSAVE , {_94_or_108_byte}}},
		{0b111, {InstructionName::FSTSW , {_2_byte        }}},
	}},
	{0xDE, {
		{0b000, {InstructionName::FIADD , {word_integer}}},
		{0b001, {InstructionName::FIMUL , {word_integer}}},
		{0b010, {InstructionName::FICOM , {word_integer}}},
		{0b011, {InstructionName::FICOMP, {word_integer}}},
		{0b100, {InstructionName::FISUB , {word_integer}}},
		{0b101, {InstructionName::FISUBR, {word_integer}}},
		{0b110, {InstructionName::FIDIV , {word_integer}}},
		{0b111, {InstructionName::FIDIVR, {word_integer}}},
	}},
	{0xDF, {
		{0b000, {InstructionName::FILD  , {word_integer }}},
		{0b001, {InstructionName::FISTTP, {word_integer }}},
		{0b010, {InstructionName::FIST  , {word_integer }}},
		{0b011, {InstructionName::FISTP , {word_integer }}},
		{0b100, {InstructionName::FBLD  , {packed_BCD   }}},
		{0b101, {InstructionName::FILD  , {qword_integer}}},
		{0b110, {InstructionName::FBSTP , {packed_BCD   }}},
		{0b111, {InstructionName::FISTP , {qword_integer}}},
	}},
};