#include "OpcodeToString.h"

#include <map>
#include <set>
#include <cassert>

OpcodeToString::OpcodeToString (const Instruction & instruction)
	: _instruction {instruction}
{
}

std::string OpcodeToString::toString ()
{
	std::string re;

	re += toString (_instruction.prefixs, _instruction.name);

	re += toString (_instruction.name);

	for (size_t i = 0; i < _instruction.operands.size(); i++)
	{
		if (0 == i)
			re += ' ';
		else
			re += ',';

		re += toString (_instruction.name, _instruction.operands[i]);
	}
	return re;
}
std::string OpcodeToString::toString (
	const std::vector <Prefix> & prefixs,
	InstructionName name)
{
	if (prefixs.empty ())
		return "";

	assert (prefixs.size () == 1);

	switch (prefixs[0])
	{
	case Prefix::LOCK:
		return "LOCK ";
	case Prefix::REP:
		switch (name)
		{
		case InstructionName::MOVS:
		case InstructionName::LODS:
		case InstructionName::STOS:
//		case InstructionName::MOVSD:
//		case InstructionName::LODSD:
//		case InstructionName::STOSD:
			return "REP ";
		case InstructionName::SCAS:
		case InstructionName::CMPS:
			return "REPE ";
		default:
			throw "";
		}
	case Prefix::REPNE:
		return "REPNE ";
	}

	throw "";
}
std::string OpcodeToString::toString (const InstructionName & name)
{
	static const std::map <InstructionName, std::string> maps
	{
		{InstructionName::_INVALID   , "???"                                        },
		{InstructionName::MOVSXD     , "MOVSXD"                                     },
		{InstructionName::RETF       , "RETF"                                       },
		{InstructionName::MOV        , "MOV"                                        },
		{InstructionName::SBB        , "SBB"                                        },
		{InstructionName::OR         , "OR"                                         },
		{InstructionName::SUB        , "SUB"                                        },
		{InstructionName::CMP        , "CMP"                                        },
		{InstructionName::ADC        , "ADC"                                        },
		{InstructionName::ADD        , "ADD"                                        },
		{InstructionName::AND        , "AND"                                        },
		{InstructionName::ROL        , "ROL"                                        },
		{InstructionName::SAR        , "SAR"                                        },
		{InstructionName::SHR        , "SHR"                                        },
		{InstructionName::RCL        , "RCL"                                        },
		{InstructionName::ROR        , "ROR"                                        },
		{InstructionName::TEST       , "TEST"                                       },
		{InstructionName::NOT        , "NOT"                                        },
		{InstructionName::POP        , "POP"                                        },
		{InstructionName::DEC        , "DEC"                                        },
		{InstructionName::INC        , "INC"                                        },
		{InstructionName::PUSH       , "PUSH"                                       },
		{InstructionName::NOP        , "NOP"                                        },
		{InstructionName::INT        , "INT"                                        },
		{InstructionName::XOR        , "XOR"                                        },
		{InstructionName::STR        , "STR"                                        },
		{InstructionName::LTR        , "LTR"                                        },
		{InstructionName::SYSRET     , "SYSRET"                                     },
		{InstructionName::VERR       , "VERR"                                       },
		{InstructionName::VERW       , "VERW"                                       },
		{InstructionName::LLDT       , "LLDT"                                       },
		{InstructionName::INT3       , "INT3"                                       },
		{InstructionName::RETN       , "RETN"                                       },
		{InstructionName::LEA        , "LEA"                                        },
		{InstructionName::NEG        , "NEG"                                        },
		{InstructionName::CWD        , "CWD"                                        },
		{InstructionName::CDQ        , "CDQ"                                        },
		{InstructionName::BT         , "BT"                                         },
		{InstructionName::BTS        , "BTS"                                        },
		{InstructionName::BTR        , "BTR"                                        },
		{InstructionName::UD2        , "UD2"                                        },
								     
		{InstructionName::CMOVO      , "CMOVO"                                      },
		{InstructionName::CMOVNO     , "CMOVNO"                                     },
		{InstructionName::CMOVB      , "CMOVB"                                      },
		{InstructionName::CMOVAE     , "CMOVAE"                                     },
		{InstructionName::CMOVE      , "CMOVE"                                      },
		{InstructionName::CMOVNE     , "CMOVNE"                                     },
		{InstructionName::CMOVBE     , "CMOVBE"                                     },
		{InstructionName::CMOVA      , "CMOVA"                                      },
								     
		{InstructionName::CMOVS      , "CMOVS"                                      },
		{InstructionName::CMOVNS     , "CMOVNS"                                     },
		{InstructionName::CMOVPE     , "CMOVPE"                                     },
		{InstructionName::CMOVPO     , "CMOVPO"                                     },
		{InstructionName::CMOVL      , "CMOVL"                                      },
		{InstructionName::CMOVGE     , "CMOVGE"                                     },
		{InstructionName::CMOVLE     , "CMOVLE"                                     },
		{InstructionName::CMOVG      , "CMOVG"                                      },

		{InstructionName::CPUID      , "CPUID"                                      },
		{InstructionName::INVD       , "INVD"                                       },
		{InstructionName::WBINVD     , "WBINVD"                                     },
		{InstructionName::BTC        , "BTC"                                        },
		{InstructionName::DAS        , "DAS"                                        },
		{InstructionName::RSM        , "RSM"                                        },
		{InstructionName::AAS        , "AAS"                                        },
		{InstructionName::MUL        , "MUL"                                        },
		{InstructionName::IMUL       , "IMUL"                                       },
		{InstructionName::DIV        , "DIV"                                        },
		{InstructionName::IDIV       , "IDIV"                                       },
		{InstructionName::GETSEC     , "GETSEC"                                     },
		{InstructionName::RDPMC      , "RDPMC"                                      },
		{InstructionName::RDTSC      , "RDTSC"                                      },
		{InstructionName::WRMSR      , "WRMSR"                                      },
		{InstructionName::RDMSR      , "RDMSR"                                      },
		{InstructionName::MOVZX      , "MOVZX"                                      },
		{InstructionName::CALLN      , "CALL"                                       },
		{InstructionName::SHLD       , "SHLD"                                       },
		{InstructionName::INVLPG     , "INVLPG"                                     },
		{InstructionName::SYSEXIT    , "SYSEXIT"                                    },
		{InstructionName::LEAVE      , "LEAVE"                                      },
		{InstructionName::CALL       , "CALL"                                       },
		{InstructionName::CALLF      , "CALL FAR"                                   },
		{InstructionName::JMPN       , "JMP"                                        },
		{InstructionName::JMPF       , "JMP FAR"                                    },
		{InstructionName::SHRD       , "SHRD"                                       },
		{InstructionName::SLDT       , "SLDT"                                       },
		{InstructionName::SAHF       , "SAHF"                                       },
		{InstructionName::SGDT       , "SGDT"                                       },
		{InstructionName::SIDT       , "SIDT"                                       },
		{InstructionName::LGDT       , "LGDT"                                       },
		{InstructionName::LIDT       , "LIDT"                                       },
		{InstructionName::CMPXCHG    , "CMPXCHG"                                    },
		{InstructionName::SMSW       , "SMSW"                                       },
		{InstructionName::LMSW       , "LMSW"                                       },
		{InstructionName::LAHF       , "LAHF"                                       },
		{InstructionName::JMP_NEAR   , "JMP"                                        },
		{InstructionName::JMP_FAR    , "JMP FAR"                                    },
		{InstructionName::JMP_SHORT  , "JMP SHORT"                                  },
		{InstructionName::PUSHFD     , "PUSHFD"                                     },
		{InstructionName::POPFD      , "POPFD"                                      },
		{InstructionName::JO         , "JO SHORT"                                   },
		{InstructionName::JNO        , "JNO SHORT"                                  },
		{InstructionName::JB         , "JB SHORT"                                   },
		{InstructionName::JAE        , "JAE SHORT"                                  },
		{InstructionName::JE         , "JE SHORT"                                   },
		{InstructionName::JNZ        , "JNZ SHORT"                                  },
		{InstructionName::JBE        , "JBE SHORT"                                  },
		{InstructionName::JA         , "JA SHORT"                                   },
		{InstructionName::JS         , "JS SHORT"                                   },
		{InstructionName::JNS        , "JNS SHORT"                                  },
		{InstructionName::JPE        , "JPE SHORT"                                  },
		{InstructionName::JPO        , "JPO SHORT"                                  },
		{InstructionName::JL         , "JL SHORT"                                   },
		{InstructionName::JGE        , "JGE SHORT"                                  },
		{InstructionName::JLE        , "JLE SHORT"                                  },
		{InstructionName::JG         , "JG SHORT"                                   },
		{InstructionName::SETO       , "SETO"                                       },
		{InstructionName::SETNO      , "SETNO"                                      },
		{InstructionName::SETB       , "SETB"                                       },
		{InstructionName::SETAE      , "SETAE"                                      },
		{InstructionName::SETE       , "SETE"                                       },
		{InstructionName::SETNZ      , "SETNE"                                      },
		{InstructionName::SETBE      , "SETBE"                                      },
		{InstructionName::SETA       , "SETA"                                       },
		{InstructionName::SETS       , "SETS"                                       },
		{InstructionName::SETNS      , "SETNS"                                      },
		{InstructionName::SETPE      , "SETPE"                                      },
		{InstructionName::SETPO      , "SETPO"                                      },
		{InstructionName::SETL       , "SETL"                                       },
		{InstructionName::SETGE      , "SETGE"                                      },
		{InstructionName::SETLE      , "SETLE"                                      },
		{InstructionName::SETG       , "SETG"                                       },
		{InstructionName::JECXZ      , "JECXZ SHORT"                                },
		{InstructionName::JCXZ       , "JCXZ SHORT"                                 },
		{InstructionName::ENTER      , "ENTER"                                      },
		{InstructionName::LOOPNZ     , "LOOPNZ SHORT"                               },
		{InstructionName::LOOPZ      , "LOOPZ SHORT"                                },
		{InstructionName::LOOP       , "LOOP SHORT"                                 },
		{InstructionName::PUSHFQ     , "PUSHFQ"                                     },
		{InstructionName::POPFQ      , "POPFQ"                                      },
		{InstructionName::CDQE       , "CDQE"                                       },
		{InstructionName::CQO        , "CQO"                                        },
		{InstructionName::SYSENTER   , "SYSENTER"                                   },
		{InstructionName::SYSCALL    , "SYSCALL"                                    },
		{InstructionName::FCLEX      , "FCLEX"                                      },
		{InstructionName::IRETQ      , "IRETQ"                                      },
		{InstructionName::STOS       , "STOS"		                                },
//		{InstructionName::STOSD      , "STOS DWORD PTR ES:[EDI]"                    },
//		{InstructionName::STOSW      , "STOS WORD PTR ES:[EDI]"                     },
//		{InstructionName::STOSB      , "STOS BYTE PTR ES:[EDI]"                     },
		{InstructionName::SCAS       , "SCAS"                                       },
//		{InstructionName::SCASD      , "SCAS DWORD PTR ES:[EDI]"                    },
//		{InstructionName::SCASW      , "SCAS WORD PTR ES:[EDI]"                     },
//		{InstructionName::SCASB      , "SCAS BYTE PTR ES:[EDI]"                     },
		{InstructionName::LODS       , "LODS"                                       },
//		{InstructionName::LODSD      , "LODS DWORD PTR DS:[ESI]"                    },
//		{InstructionName::LODSW      , "LODS WORD PTR DS:[ESI]"                     },
//		{InstructionName::LODSB      , "LODS BYTE PTR DS:[ESI]"                     },
		{InstructionName::MOVS       , "MOVS"                                       },
//		{InstructionName::MOVSD      , "MOVS DWORD PTR ES:[EDI],DWORD PTR DS:[ESI]" },
//		{InstructionName::MOVSW      , "MOVS WORD PTR ES:[EDI],WORD PTR DS:[ESI]"   },
//		{InstructionName::MOVSB      , "MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]"   },
		{InstructionName::CMPS       , "CMPS"                                       },
//		{InstructionName::CMPSD      , "CMPS DWORD PTR DS:[ESI],DWORD PTR ES:[EDI]" },
//		{InstructionName::CMPSW      , "CMPS WORD PTR DS:[ESI],WORD PTR ES:[EDI]"   },
//		{InstructionName::CMPSB      , "CMPS BYTE PTR DS:[ESI],BYTE PTR ES:[EDI]"   },
		{InstructionName::DAA        , "DAA"                                        },
		{InstructionName::AAA        , "AAA"                                        },
		{InstructionName::PUSHA      , "PUSHAD"                                     },
		{InstructionName::POPA       , "POPAD"                                      },
		{InstructionName::BOUND      , "BOUND"                                      },
		{InstructionName::ARPL       , "ARPL"                                       },
		{InstructionName::XCHG       , "XCHG"                                       },
		{InstructionName::SHL        , "SHL"                                        },
		{InstructionName::RCR        , "RCR"                                        },
		{InstructionName::LES        , "LES"                                        },
		{InstructionName::LDS        , "LDS"                                        },
		{InstructionName::LSS        , "LSS"                                        },
		{InstructionName::LFS        , "LFS"                                        },
		{InstructionName::LGS        , "LGS"                                        },
		{InstructionName::AAM        , "AAM"                                        },
		{InstructionName::HLT        , "HLT"                                        },
		{InstructionName::CMC        , "CMC"                                        },
		{InstructionName::OUTX        , "OUT"                                        },
		{InstructionName::CBW        , "CBW"                                        },
		{InstructionName::CLC        , "CLC"                                        },
		{InstructionName::STC        , "STC"                                        },
		{InstructionName::CLI        , "CLI"                                        },
		{InstructionName::STI        , "STI"                                        },
		{InstructionName::CLD        , "CLD"                                        },
		{InstructionName::BSF        , "BSF"                                        },
		{InstructionName::BSR        , "BSR"                                        },
		{InstructionName::STD        , "STD"                                        },
		{InstructionName::FST        , "FST"                                        },
		{InstructionName::FLD        , "FLD"                                        },
		{InstructionName::FSTP       , "FSTP"                                       },
		{InstructionName::FXAM       , "FXAM"                                       },
		{InstructionName::FSUB       , "FSUB"                                       },
		{InstructionName::FMUL       , "FMUL"                                       },
		{InstructionName::FDIV       , "FDIV"                                       },
		{InstructionName::FCOM       , "FCOM"                                       },
		{InstructionName::FADD       , "FADD"                                       },
		{InstructionName::FXCH       , "FXCH"                                       },
		{InstructionName::FNOP       , "FNOP"                                       },
		{InstructionName::FILD       , "FILD"                                       },
		{InstructionName::FRSTOR     , "FRSTOR"                                     },
		{InstructionName::FISTTP     , "FISTTP"                                     },
		{InstructionName::FBLD       , "FBLD"                                       },
		{InstructionName::FIST       , "FIST"                                       },
		{InstructionName::FCOMIP     , "FCOMIP"                                     },
		{InstructionName::FBSTP      , "FBSTP"                                      },
		{InstructionName::FSAVE      , "FSAVE"                                      },
		{InstructionName::FSTSW      , "FSTSW"                                      },
		{InstructionName::FISTP      , "FISTP"                                      },
		{InstructionName::FIADD      , "FIADD"                                      },
		{InstructionName::FIMUL      , "FIMUL"                                      },
		{InstructionName::FICOM      , "FICOM"                                      },
		{InstructionName::FICOMP     , "FICOMP"                                     },
		{InstructionName::FISUB      , "FISUB"                                      },
		{InstructionName::FISUBR     , "FISUBR"                                     },
		{InstructionName::FIDIV      , "FIDIV"                                      },
		{InstructionName::FIDIVR     , "FIDIVR"                                     },
		{InstructionName::FUCOM      , "FUCOM"                                      },
		{InstructionName::FDIVR      , "FDIVR"                                      },
		{InstructionName::FSUBR      , "FSUBR"                                      },
		{InstructionName::FCOMP      , "FCOMP"                                      },
		{InstructionName::FYL2X      , "FYL2X"                                      },
		{InstructionName::FSTCW      , "FSTCW"                                      },
		{InstructionName::FLDCW      , "FLDCW"                                      },
		{InstructionName::F2XM1      , "F2XM1"                                      },
		{InstructionName::FSTENV     , "FSTENV"                                     },
		{InstructionName::FLDENV     , "FLDENV"                                     },
		{InstructionName::FCMOVB     , "FCMOVB"                                     },
		{InstructionName::FCMOVE     , "FCMOVE"                                     },
		{InstructionName::FCMOVU     , "FCMOVU"                                     },
		{InstructionName::FCMOVNU    , "FCMOVNU"                                    },
		{InstructionName::FCMOVNE    , "FCMOVNE"                                    },
		{InstructionName::FCMOVNB    , "FCMOVNB"                                    },
		{InstructionName::FCMOVBE    , "FCMOVBE"                                    },
		{InstructionName::FUCOMPP    , "FUCOMPP"                                    },
		{InstructionName::FCMOVNBE   , "FCMOVNBE"                                   },
		{InstructionName::FTST       , "FTST"                                       },
		{InstructionName::FCHS       , "FCHS"                                       },
		{InstructionName::FABS       , "FABS"                                       },
		{InstructionName::XADD       , "XADD"                                       },
		{InstructionName::CWDE       , "CWDE"                                       },
		{InstructionName::MOVSX      , "MOVSX"                                      },
		{InstructionName::INX         , "IN"                                         },
		{InstructionName::XLAT       , "XLAT BYTE PTR DS:[EBX+AL]"                  },
		{InstructionName::INSB       , "INS BYTE PTR ES:[EDI],DX"                   },
		{InstructionName::INSW       , "INS WORD PTR ES:[EDI],DX"                   },
		{InstructionName::INSD       , "INS DWORD PTR ES:[EDI],DX"                  },
		{InstructionName::OUTSB      , "OUTS DX,BYTE PTR DS:[ESI]"                  },
		{InstructionName::OUTSW      , "OUTS DX,WORD PTR DS:[ESI]"                  },
		{InstructionName::OUTSD      , "OUTS DX,DWORD PTR DS:[ESI]"                 },
		{InstructionName::PREFETCHNTA, "PREFETCHNTA"                                },
		{InstructionName::PREFETCHT0 , "PREFETCHT0"                                 },
		{InstructionName::PREFETCHT1 , "PREFETCHT1"                                 },
		{InstructionName::PREFETCHT2 , "PREFETCHT2"                                 },
		{InstructionName::RDRAND     , "RDRAND"                                     },
		{InstructionName::VMREAD     , "VMREAD"                                     },
		{InstructionName::BSWAP      , "BSWAP"                                      },
		{InstructionName::VMWRITE    , "VMWRITE"                                    },
		{InstructionName::CMPXCHG8B  , "CMPXCHG8B"                                  },
		{InstructionName::IRETW      , "IRETW"                                      },
		{InstructionName::IRETD      , "IRETD"                                      },
	};

	auto iter = maps.find (name);
	if (maps.end () == iter)
		throw "OpcodeToString::toString (InstructionName)";

	return iter->second;
}
std::string OpcodeToString::toString (const SegName & name)
{
	static const std::map <SegName, std::string> maps
	{
		{SegName::CS, "CS"},
		{SegName::DS, "DS"},
		{SegName::SS, "SS"},
		{SegName::ES, "ES"},
		{SegName::FS, "FS"},
		{SegName::GS, "GS"},
	};

	auto iter = maps.find (name);
	if (maps.end () == iter)
		throw "OpcodeToString::toString (SegName)";

	return iter->second;
}
std::string OpcodeToString::toString (const CrName & name)
{
	static const std::map <CrName, std::string> maps
	{
		{CrName::CR0, "CR0"},
		{CrName::CR1, "CR1"},
		{CrName::CR2, "CR2"},
		{CrName::CR3, "CR3"},
		{CrName::CR4, "CR4"},
	};

	auto iter = maps.find (name);
	if (maps.end () == iter)
		throw "OpcodeToString::toString (CrName)";

	return iter->second;
}
std::string OpcodeToString::toString (const DrName & name)
{
	static const std::map <DrName, std::string> maps
	{
		{DrName::DR0, "DR0"},
		{DrName::DR1, "DR1"},
		{DrName::DR2, "DR2"},
		{DrName::DR3, "DR3"},
		{DrName::DR4, "DR4"},
		{DrName::DR5, "DR5"},
		{DrName::DR6, "DR6"},
		{DrName::DR7, "DR7"},
	};

	auto iter = maps.find (name);
	if (maps.end () == iter)
		throw "OpcodeToString::toString (DrName)";

	return iter->second;
}
std::string OpcodeToString::toString (const StName & name)
{
	static const std::map <StName, std::string> maps
	{
		{StName::ST0, "ST"},
		{StName::ST1, "ST(1)"},
		{StName::ST2, "ST(2)"},
		{StName::ST3, "ST(3)"},
		{StName::ST4, "ST(4)"},
		{StName::ST5, "ST(5)"},
		{StName::ST6, "ST(6)"},
		{StName::ST7, "ST(7)"},
	};

	auto iter = maps.find (name);
	if (maps.end () == iter)
		throw "OpcodeToString::toString (StName)";

	return iter->second;
}
std::string OpcodeToString::toString (const RegName & name)
{
	static const std::map <RegName, std::string> maps
	{
		{RegName::AL, "AL"},
		{RegName::CL, "CL"},
		{RegName::DL, "DL"},
		{RegName::BL, "BL"},
		{RegName::AH, "AH"},
		{RegName::CH, "CH"},
		{RegName::DH, "DH"},
		{RegName::BH, "BH"},

		{RegName::AX, "AX"},
		{RegName::CX, "CX"},
		{RegName::DX, "DX"},
		{RegName::BX, "BX"},
		{RegName::SP, "SP"},
		{RegName::BP, "BP"},
		{RegName::SI, "SI"},
		{RegName::DI, "DI"},

		{RegName::SPL, "SPL"},
		{RegName::BPL, "BPL"},
		{RegName::SIL, "SIL"},
		{RegName::DIL, "DIL"},

		{RegName::EAX, "EAX"},
		{RegName::ECX, "ECX"},
		{RegName::EDX, "EDX"},
		{RegName::EBX, "EBX"},
		{RegName::ESP, "ESP"},
		{RegName::EBP, "EBP"},
		{RegName::ESI, "ESI"},
		{RegName::EDI, "EDI"},

		{RegName::RAX, "RAX"},
		{RegName::RCX, "RCX"},
		{RegName::RDX, "RDX"},
		{RegName::RBX, "RBX"},
		{RegName::RSP, "RSP"},
		{RegName::RBP, "RBP"},
		{RegName::RSI, "RSI"},
		{RegName::RDI, "RDI"},

		{RegName::R8B , "R8B" },
		{RegName::R9B , "R9B" },
		{RegName::R10B, "R10B"},
		{RegName::R11B, "R11B"},
		{RegName::R12B, "R12B"},
		{RegName::R13B, "R13B"},
		{RegName::R14B, "R14B"},
		{RegName::R15B, "R15B"},

		{RegName::R8W , "R8W" },
		{RegName::R9W , "R9W" },
		{RegName::R10W, "R10W"},
		{RegName::R11W, "R11W"},
		{RegName::R12W, "R12W"},
		{RegName::R13W, "R13W"},
		{RegName::R14W, "R14W"},
		{RegName::R15W, "R15W"},

		{RegName::R8D , "R8D" },
		{RegName::R9D , "R9D" },
		{RegName::R10D, "R10D"},
		{RegName::R11D, "R11D"},
		{RegName::R12D, "R12D"},
		{RegName::R13D, "R13D"},
		{RegName::R14D, "R14D"},
		{RegName::R15D, "R15D"},

		{RegName::R8 , "R8" },
		{RegName::R9 , "R9" },
		{RegName::R10, "R10"},
		{RegName::R11, "R11"},
		{RegName::R12, "R12"},
		{RegName::R13, "R13"},
		{RegName::R14, "R14"},
		{RegName::R15, "R15"},
	};

	auto iter = maps.find (name);
	if (maps.end () == iter)
		throw "OpcodeToString::toString (RegName)";

	return iter->second;
}
std::string OpcodeToString::getMemSizeString (int size)
{
	switch (size)
	{
	case 1:   return "BYTE PTR";
	case 2:   return "WORD PTR";
	case 4:   return "DWORD PTR";
	case 6:   return "FWORD PTR";
	case 8:   return "QWORD PTR";
	case 10:  return "TBYTE PTR";
	case 14:  return "14BYTE PTR";
	case 28:  return "28BYTE PTR";
	case 94:  return "94BYTE PTR";
	case 108: return "108BYTE PTR";
	}

	throw "";
}
std::string OpcodeToString::getScaleString (int scale)
{
	switch (scale)
	{
	case 1: return "";
	case 2: return "*2";
	case 4: return "*4";
	case 8: return "*8";
	}

	throw "";
}
int OpcodeToString::extendSignBit (
	size_t size,
	uint32 val)
{
	if (size == 1)
	{
		if (val & 0x80)
			return val | 0xFFFFFF00;
		else
			return val;
	}
	if (size == 2)
	{
		if (val & 0x8000)
			return val | 0xFFFF0000;
		else
			return val;
	}
	if (size == 4)
	{
		return val;
	}

	throw "";
}
std::string OpcodeToString::getImm6String (
	InstructionName instructionName,
	uint32 val,
	uint32 val_2)
{
	char num[14] {};
	sprintf_s (num, 14, "%04X:%08X", val_2, val);
	return num;
}
std::string add_0 (char* num)
{
	if (num[0] >= 'A' && num[0] <= 'F')
		if (strlen (num) < 8)
			return std::string {'0'} + num;

	return num;
}
std::string OpcodeToString::getImmString (
	InstructionName instructionName,
	size_t meanSize,
	size_t storeSize,
	uint32 val)
{
	assert (meanSize >= storeSize);

	// show -
	if (meanSize == 4)
	{
		int val3 = extendSignBit (storeSize, val);
		if (val3 < 0 && val3 >= -0x4000)
		{
			std::set <InstructionName> sets
			{
				InstructionName::MOV ,
				InstructionName::PUSH,
				InstructionName::ADD ,
			};

			if (sets.end () != sets.find (instructionName))
			{
				char num[10] {};
				sprintf_s (num, 10, "-%X", abs (val3));
				return num;
			}
		}
	}

	char num[9] {};
	sprintf_s (num, 9, "%X", val);

	return add_0 (num);
}
std::string OpcodeToString::getDisplacementString (
	int displacement,
	bool isOnlyDisplace)
{
	if (isOnlyDisplace)
	{
		// treat disp as uint32
		char num[9] {};
		sprintf_s (num, 9, "%X", displacement);
		return num;
	}

	std::string re;

	if (displacement <= -0x4000 || displacement >= 0)
	{
		// treat disp as uint32 even if disp < 0
		re += '+';

		char num[9] {};
		sprintf_s (num, 9, "%X", displacement);
		re += add_0 (num);
		return re;
	}

	re += '-';

	displacement = abs (displacement);

	char num[9] {};
	sprintf_s (num, 9, "%X", displacement);
	re += add_0 (num);

	return re;
}
std::string OpcodeToString::toString (const MemAddr & addr)
{
	std::string re;

	if (addr.base != RegName::NONE)
		re += toString (addr.base);

	if (addr.index != RegName::NONE)
	{
		if (false == re.empty ())
			re += '+';
		re += toString (addr.index);
		re += getScaleString (addr.scale);
	}

	if (addr.displacement != 0)
	{
		bool isOnlyDisplace = re.empty ();
		re += getDisplacementString (
			addr.displacement, isOnlyDisplace);
	}

	if (re.empty ())
		re += '0';

	return re;
}
size_t OpcodeToString::getRegSize (RegName name)
{
	switch (name)
	{
	case RegName::RAX:
	case RegName::RCX:
	case RegName::RDX:
	case RegName::RBX:
	case RegName::RSP:
	case RegName::RBP:
	case RegName::RSI:
	case RegName::RDI:
		return 8;
	case RegName::EAX:
	case RegName::ECX:
	case RegName::EDX:
	case RegName::EBX:
	case RegName::ESP:
	case RegName::EBP:
	case RegName::ESI:
	case RegName::EDI:
	case RegName::R8D:
	case RegName::R9D:
	case RegName::R10D:
	case RegName::R11D:
	case RegName::R12D:
	case RegName::R13D:
	case RegName::R14D:
	case RegName::R15D:
		return 4;
	case RegName::AX:
	case RegName::CX:
	case RegName::DX:
	case RegName::BX:
	case RegName::SP:
	case RegName::BP:
	case RegName::SI:
	case RegName::DI:
		return 2;
	case RegName::R8B :
	case RegName::R9B :
	case RegName::R10B:
	case RegName::R11B:
	case RegName::R12B:
	case RegName::R13B:
	case RegName::R14B:
	case RegName::R15B:
	case RegName::AL:
	case RegName::CL:
	case RegName::DL:
	case RegName::BL:
	case RegName::AH:
	case RegName::CH:
	case RegName::DH:
	case RegName::BH:
		return 1;
	}

	throw "";
}
size_t OpcodeToString::getFirstOperandSize ()
{
	assert (_instruction.operands.size () >= 1);

	switch (_instruction.operands[0].type)
	{
	case OperandType::MEM:
		return _instruction.operands[0].mem.size;
	case OperandType::REG:
		return getRegSize (_instruction.operands[0].reg.name);
	case OperandType::IMM:
		if (_instruction.operands[0].imm.size == 6)
			return 6;
		else
			return 4;
	}

	throw "";
}
std::string OpcodeToString::toString (
	InstructionName instructionName,
	const Operand & operand)
{
	if (operand.type == OperandType::REG)
		return toString (operand.reg.name);

	if (operand.type == OperandType::CR)
		return toString (operand.cr.name);

	if (operand.type == OperandType::DR)
		return toString (operand.dr.name);

	if (operand.type == OperandType::ST)
		return toString (operand.st.name);

	if (operand.type == OperandType::SEG)
		return toString (operand.seg.name);

	if (operand.type == OperandType::MEM)
	{
		std::string re;
		re += getMemSizeString ((int)operand.mem.size);
		re += " ";
		re += toString (operand.mem.seg);
		re += ":[";
		re += toString (operand.mem.addr);
		re += "]";
		return re;
	}

	if (operand.type == OperandType::IMM)
	{
		if (operand.imm.size == 6)
		{
			return getImm6String (instructionName, operand.imm.val, operand.imm.val_2);
		}
		else
		{
			size_t meanSize = getFirstOperandSize ();
			return getImmString (instructionName, meanSize, operand.imm.size, operand.imm.val);
		}
	}

	throw "OpcodeToString::toString (Operand)";
}
