#pragma once



#include <vector>
#include <type_traits>
#include <cassert>

using uint8 = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using int8 = signed char;
using int16 = signed short;
using int32 = signed int;
using Byte = uint8;

enum class RegName
{
	NONE,
	AL, AX, EAX, RAX, R8B , R8W , R8D ,	R8 ,
	CL, CX, ECX, RCX, R9B , R9W , R9D ,	R9 ,
	DL, DX, EDX, RDX, R10B, R10W, R10D,	R10,
	BL, BX, EBX, RBX, R11B, R11W, R11D,	R11,
	AH, SP, ESP, RSP, R12B, R12W, R12D,	R12,
	CH, BP, EBP, RBP, R13B, R13W, R13D,	R13,
	DH, SI, ESI, RSI, R14B, R14W, R14D,	R14,
	BH, DI, EDI, RDI, R15B, R15W, R15D,	R15,
								  
	SPL,						  
	BPL,						  
	SIL,						  
	DIL,						  
};								  
enum class InstructionName
{
	_INVALID   ,		//无效指令
	MOVSXD     ,
	FST        ,
	FLD        ,
	FSTP       ,
	FXAM       ,
	FNOP       ,
	FADD       ,
	FMUL       ,
	FSUB       ,
	FDIV       ,
	FCOM       ,
	FCHS       ,
	FABS       ,
	FTST       ,
	FXCH       ,
	FILD       ,
	FISTTP     ,
	FRSTOR     ,
	FBLD       ,
	FIST       ,
	FBSTP      ,
	FISTP      ,
	FDIVR      ,
	FSUBR      ,
	FCOMP      ,
	FSAVE      ,
	FSTSW      ,
	FUCOM      ,
	FIADD      ,
	FIMUL      ,
	FICOM      ,
	FCOMIP     ,
	FICOMP     ,
	FISUB      ,
	FISUBR     ,
	FIDIV      ,
	FIDIVR     ,
	F2XM1      ,
	FSTCW      ,
	FLDCW      ,
	FYL2X      ,
	FSTENV     ,
	FLDENV     ,
	FCMOVB     ,
	FCMOVE     ,
	FCMOVU     ,
	FCMOVNU    ,
	FCMOVNE    ,
	FCMOVNB    ,
	FUCOMPP    ,
	FCMOVBE    ,
	FCMOVNBE   ,
	PREFETCHNTA,
	PREFETCHT0 , 
	PREFETCHT1 , 
	PREFETCHT2 , 
	RETF       ,
	ENTER      ,
	LEAVE      ,
	INVD       ,
	WBINVD     ,
	AAS        ,
	DAS        ,
	MOV        ,
	SBB        ,
	OR         ,
	SUB        ,
	CMP        ,
	ADC        ,
	ADD        ,
	AND        ,
	ROL        ,
	ROR        ,
	SAR        ,
	SHR        ,
	SHL        ,
	RCL        ,
	RCR        ,
	TEST       ,
	NOT        ,
	NEG        ,
	POP        ,
	DEC        ,
	RSM        ,
	INC        ,
	STR        ,
	SYSRET     ,
	LTR        ,
	BT         ,
	BTS        ,
	BTR        ,
	LSS        ,
	LFS        ,
	LGS        ,
	BTC        ,
	BSF        ,
	BSR        ,
	PUSH       ,
	SLDT       ,
	LLDT       ,
	VERR       ,
	VERW       ,
	SGDT       ,
	SIDT       ,
	LGDT       ,
	LIDT       ,
	LMSW       ,
	SMSW       ,
	UD2        ,
	NOP        ,
	INT        ,
	MOVSX      ,
	INTO       ,
	AAM        ,
	XLAT       ,
	AAD        ,
	XOR        ,
	INT3       ,
	RETN       ,
	LEA        ,
	CWD        ,
	CBW        ,
	CDQE       ,
	CQO        ,
	CWDE       ,
	SYSCALL    ,
	SAHF       ,
	LAHF       ,
	CDQ        ,
	CMPXCHG8B  ,
	RDRAND     ,
	PUSHFD     ,
	POPFD      ,
	PUSHFQ     ,
	POPFQ      ,
	DIV        ,
	IDIV       ,
	MUL        ,
	IMUL       ,
	WRMSR      ,
	RDPMC      ,
	RDTSC      ,
	RDMSR      ,
	CPUID      ,
	MOVZX      ,
	BSWAP      ,
	CALLN      ,
	CALLF      ,
	JMPN       ,
	JMPF       ,
	CALL       ,
	LOOPNZ     ,
	LOOPZ      ,
	IRETW      ,
	IRETD      ,
	IRETQ      ,
	LOOP       ,
	INVLPG     ,
	JMP_NEAR   ,
	JMP_FAR    ,
	JMP_SHORT  ,
	CMOVO      ,
	CMOVNO     ,
	CMOVB      ,
	CMOVAE     ,
	CMOVE      ,
	CMOVNE     ,
	CMOVBE     ,
	CMOVA      ,
	CMOVS      ,
	CMOVNS     ,
	CMOVPE     ,
	CMOVPO     ,
	CMOVL      ,
	CMOVGE     ,
	CMOVLE     ,
	CMOVG      ,
	JO         ,
	JNO        ,
	HLT        ,
	CMC        ,
	JB         ,
	JAE        ,
	JNZ        ,
	JE         ,
	JBE        ,
	JA         ,
	JS         ,
	JNS        ,
	JPE        ,
	JPO        ,
	JL         ,
	JGE        ,
	JLE        ,
	JG         ,
	JECXZ      ,
	JCXZ       ,
	SYSENTER   ,
	SYSEXIT    ,
	GETSEC     ,
	FCLEX      ,
	STOS       ,
	LODS       ,
	SCAS       ,
	MOVS       ,
	CMPS       ,
	DAA        ,
	AAA        ,
	CLC        ,
	STC        ,
	CLI        ,
	STI        ,
	CLD        ,
	STD        ,
	PUSHA      ,
	POPA       ,
	BOUND      ,
	ARPL       ,
	XCHG       ,
	LES        ,
	LDS,
	INX,
	OUTX,
	INSB,
	INSW       ,
	VMREAD     ,
	VMWRITE    ,
	INSD       ,
	OUTSB      ,
	OUTSW      ,
	OUTSD      ,
	SETO       ,
	SETNO      ,
	SETB       ,
	SETAE      ,
	SETE       ,
	SETNZ      ,
	SETBE      ,
	SETA       ,
	SETS       ,
	SETNS      ,
	SETPE      ,
	SETPO      ,
	SETL       ,
	SETGE      ,
	SETLE      ,
	SETG       ,
	SHLD       ,
	SHRD       ,
	XADD       ,
	CMPXCHG    ,
};
enum class OperandType
{
	REG,
	MEM,
	IMM,
	SEG,
	CR,		//control reg
	DR,		//debug reg
	ST,		//x87 data reg
};
enum class SegName
{
	ES,
	CS,
	SS,
	DS,
	FS,
	GS,
};
enum class CrName
{
	CR0,
	CR1,
	CR2,
	CR3,
	CR4,
};
enum class DrName
{
	DR0,
	DR1,
	DR2,
	DR3,
	DR4,
	DR5,
	DR6,
	DR7,
};
enum class StName
{
	ST0,
	ST1,
	ST2,
	ST3,
	ST4,
	ST5,
	ST6,
	ST7,
};
enum class InstSet
{
	x86,
	x64,
};
enum class GroupName
{
	_1,
	_1A,
	_2,
	_3_F6,	// Group 3 when opcode is 0xF6
	_3_F7,	// Group 3 when opcode is 0xF7
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,
	_11,
	_16,
};
enum class Prefix
{
	ADDRESS_SIZE,
	OPERAND_SIZE,
	SEG,
	REP,
	REPE = REP,
	REPNE,
	LOCK,
};
enum class MainEntryType
{
	INSTRUCTION,
	GROUP,
	MORE_OPCODE,
	ESCAPE,
	EMPTY,		//此格为空
};

class Exception
{
public:
	Exception (const char* str)
		: _str {str}
	{
	}
	Exception (int type)
		: _type {type}
	{
	}
	template <typename T>
	bool is (T type) const
	{
		static_assert (std::is_enum <T>::value, "");
		
		return (int) type == _type;
	}
	const char* getString ()
	{
		return _str;
	}

private:
	const char* _str;
	int _type;
};
struct MemAddr
{
	int scale;
	RegName index;
	RegName base;
	int displacement;
	bool isRelativeEip {false};

	MemAddr ()
	{
	}
	MemAddr (int scale, RegName index, RegName base, int displacement, bool isRelativeEip)
		: scale {scale}, index {index}, base {base}
		, displacement {displacement}, isRelativeEip {isRelativeEip}
	{
	}
	void setByReg (RegName name);
	void setByDisplacement (int displacement);
	void setByRelativeDisplacement (int displacement);
};

struct Operand
{
	OperandType type;

	struct
	{
		RegName name;
	} reg;

	struct
	{
		SegName name;
	} seg;

	struct
	{
		CrName name;
	} cr;

	struct
	{
		DrName name;
	} dr;

	struct
	{
		StName name;
	} st;

	struct
	{
		MemAddr addr;
		SegName seg;
		size_t size;
	} mem {};

	struct
	{
		size_t size;
		uint32 val;
		uint32 val_2;
	} imm;


	Operand ()
	{
	}
	Operand (RegName name)
		: type {OperandType::REG}
		, reg {name}
	{
	}
	Operand (StName name)
		: type {OperandType::ST}
		, st {name}
	{
	}
	Operand (SegName name)
		: type {OperandType::SEG}
		, seg {name}
	{
	}
	template <
		typename T0,
		typename T1,
		typename T2,
		typename T3,
		typename T4,
		typename... Args
	>
	Operand (
		size_t size,
		T0 _0,
		T1 _1,
		T2 _2,
		T3 _3,
		T4 _4,
		Args... args)
	{
		static_assert (false, "");
	}
	template <typename... Args>
	Operand (size_t size, Args... args)
		: Operand {size, SegName::DS, args...}
	{

	}
	Operand (size_t size, SegName seg, RegName name)
		: Operand {size, seg, name, 0}
	{
	}
	Operand (size_t size, SegName seg, uint32 displacement)
		: Operand {size, seg, RegName::NONE, displacement}
	{
	}
	Operand (size_t size, SegName seg, int displacement)
		: Operand {size, seg, RegName::NONE, displacement}
	{
	}
	Operand (size_t size, SegName seg, RegName name, uint32 displacement)
		: Operand {size, seg, name, *(int*) &displacement}
	{
	}
	Operand (size_t size, SegName seg, RegName name, int displacement)
		: Operand (size, seg, name, RegName::NONE, displacement)
	{
	}
	Operand (size_t size, SegName seg, RegName index, int scale, int displacement)
		: Operand (size, seg, RegName::NONE, index, scale, displacement)
	{
	}
	Operand (size_t size, SegName seg, RegName base, RegName index)
		: Operand (size, seg, base, index, 1, 0)
	{
	}
	Operand (size_t size, SegName seg, RegName base, RegName index, int displacement)
		: Operand (size, seg, base, index, 1, displacement)
	{
	}
	Operand (size_t size, SegName seg, RegName base, RegName index, int scale, uint32 displacement)
		: Operand (size, seg, base, index, scale, (int) displacement)
	{
	}
	Operand (size_t size, SegName seg, RegName base, RegName index, int scale, int displacement)
		: type {OperandType::MEM}
		, mem {{scale, index, base, displacement, false}, seg, size}
	{
	}
	Operand (uint32 imm)
		: type {OperandType::IMM}
		, imm {0u, imm}
	{
		if (imm > 0xFFFF)
			this->imm.size = 4u;
		else if (imm > 0xFF)
			this->imm.size = 2u;
		else
			this->imm.size = 1u;
	}
	static Operand IMM (size_t size, uint32 val)
	{
		assert (size <= 4);
		Operand re {};
		re.type = OperandType::IMM;
		re.imm.size = size;
		re.imm.val = val;
		return re;
	}
	// Operand::IMM (6, 0x01E890C3, 0x0000)
	static Operand IMM (size_t size, uint32 val, uint32 val_2)
	{
		assert (size <= 8);
		assert (size >= 5);
		Operand re {};
		re.type = OperandType::IMM;
		re.imm.size = size;
		re.imm.val = val;
		re.imm.val_2 = val_2;
		return re;
	}
	// Operand::RELATIVE_MEM (1, 0x8)
	static Operand RELATIVE_MEM (size_t size, int displacement)
	{
		Operand re {};
		re.type = OperandType::MEM;
		re.mem.seg = SegName::DS;
		re.mem.size = size;
		re.mem.addr.setByRelativeDisplacement (displacement);
		return re;
	}
};

struct OperandDesc
{
	enum class Type;
	Type type;
	enum class Size;
	Size size;
	Operand fix;

	struct
	{
		Byte index;
	} regxXX;
};
enum class OperandDesc::Size
{
	d,
	v,
	v_d64,	//default 64-bit operand size
	y,
	w,
	b,
	p,
	q,
	s,
	a,
	z,
	r,
	r_d64,	//default 64-bit operand size
	e,
	unused,
	RvMw,
	_10,		// 10 byte
	_14_28,		// 14 or 28 byte
	_94_108,	// 94 or 108 byte
};
enum class OperandDesc::Type
{
	R,
	C,
	D,
	E,
	M,
	G,
	I,
	O,
	F,
	RegxXX,		//eXX or rXX
	RegrXXrX,	//rXX/rX
	J,
	S,
	A,
	X,
	Y,
};

enum class NoteString
{
	IF,
	ELSE,
	OPEN_BRACE,
	CLOSE_BRACE,
	JMP_TO_ELSE,
	BLANK,
	IF_CONDITION_BLOCK_BEGIN,
	IF_CONDITION_BLOCK_END,
};

struct Note
{
	enum class Type
	{
		IF_STATE,
		IF_ELSE_STATE,
		MULTI_CONDITION_IF_STATEMENT,
		MULTI_CONDITION_IF_ELSE_STATEMENT,
	} type {};

	struct
	{
		size_t begin;
		size_t end;
	} _if {};

	struct
	{
		size_t begin;
		size_t ifEnd;
		size_t elseEnd;
	} _if_else {};

	struct MultiConditionIf
	{
		struct EachIf
		{
			size_t pos;
			bool isJmpToEnd;
		};
		std::vector <EachIf> vec;
		size_t end;
	} _multi_condition_if {};

	struct MultiConditionIfElse
	{
		enum class JmpTo
		{
			IF,
			ELSE,
		};

		struct EachIf
		{
			size_t pos;
			JmpTo jmpTo;
		};
		std::vector <EachIf> vec;
		size_t ifEnd;
		size_t elseEnd;
	} _multi_condition_if_else {};

	static Note IF_STATEMENT (
		size_t begin,
		size_t end)
	{
		Note note {};
		note.type = Type::IF_STATE;
		note._if.begin = begin;
		note._if.end = end;
		return note;
	}
	static Note IF_ELSE_STATEMENT (
		size_t begin,
		size_t ifEnd,
		size_t elseEnd)
	{
		Note note {};
		note.type = Type::IF_ELSE_STATE;
		note._if_else.begin = begin;
		note._if_else.ifEnd = ifEnd;
		note._if_else.elseEnd = elseEnd;
		return note;
	}
	static Note MULTI_CONDITION_IF_STATEMENT (
		decltype (_multi_condition_if.vec) vec,
		size_t end)
	{
		Note note {};
		note.type = Type::MULTI_CONDITION_IF_STATEMENT;
		note._multi_condition_if.vec = vec;
		note._multi_condition_if.end = end;
		return note;
	}
	static Note MULTI_CONDITION_IF_ELSE_STATEMENT (
		decltype (_multi_condition_if_else.vec) vec,
		size_t ifEnd,
		size_t elseEnd)
	{
		Note note {};
		note.type = Type::MULTI_CONDITION_IF_ELSE_STATEMENT;
		note._multi_condition_if_else.vec = vec;
		note._multi_condition_if_else.ifEnd = ifEnd;
		note._multi_condition_if_else.elseEnd = elseEnd;
		return note;
	}

private:
	Note ()
	{
	};
};

struct OpcodeGroup
{
	InstructionName name;
	std::vector <OperandDesc> operands;
};
struct OpcodeMap
{
	InstructionName name;
	std::vector <OperandDesc> operands;
};
struct OpcodeMain
{
	MainEntryType type;

	struct 
	{
		InstructionName name;
	} instruction {};

	struct
	{
		GroupName name;
	} group {};

	std::vector <OperandDesc> operands;

	OpcodeMain (InstructionName name, std::vector <OperandDesc> operands)
		: type {MainEntryType::INSTRUCTION}
		, instruction {name}
		, operands {operands}
	{
	}

	OpcodeMain (GroupName name, std::vector <OperandDesc> operands)
		: type {MainEntryType::GROUP}
		, group {name}
		, operands {operands}
	{
	}

	OpcodeMain (MainEntryType type)
		: type {type}
	{
	}
};



struct Instruction
{
	size_t size {};
	std::vector <Prefix> prefixs;
	InstructionName name {};
	std::vector <Operand> operands;

#if 0
	size_t nOperand;		//operands.size ()
	Operand & operand_0;
	Operand & operand_1;
#endif

	Instruction ()
	{
	}
	Instruction (InstructionName name)
		: Instruction (std::vector <Prefix> {}, name, std::vector <Operand> {})
	{
	}
	Instruction (
		Prefix prefix,
		InstructionName name)
		: Instruction (std::vector <Prefix> {prefix}, name, std::vector <Operand> {})
	{
	}
	Instruction (
		std::vector <Prefix> prefixs,
		InstructionName name)
		: Instruction (prefixs, name, std::vector <Operand> {})
	{
	}
	Instruction (
		Prefix prefix,
		InstructionName name,
		Operand operand_0,
		Operand operand_1)
		: Instruction (std::vector <Prefix> {prefix}, name, {operand_0, operand_1})
	{
	}
	Instruction (
		Prefix prefix,
		InstructionName name,
		std::vector <Operand> operands)
		: Instruction (std::vector <Prefix> {prefix}, name, {operands})
	{
	}
	Instruction (
		InstructionName name,
		std::vector <Operand> operands)
		: Instruction (std::vector <Prefix> {}, name, operands)
	{
	}
	Instruction (
		InstructionName name,
		Operand operand_0,
		Operand operand_1)
		: Instruction (std::vector <Prefix> {}, name, {operand_0, operand_1})
	{
	}
	Instruction (
		std::vector <Prefix> prefixs,
		InstructionName name,
		std::vector <Operand> operands)
		: prefixs {prefixs}
		, name {name}
		, operands {operands}
	{
	}
};