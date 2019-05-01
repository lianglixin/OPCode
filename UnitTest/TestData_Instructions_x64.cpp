#include "TestData.h"


const std::vector <TestData::ExpectedInstruction> TestData::_instructions_x64
{{
	"4410d3",
	"ADC BL,R10B",
	{
		InstructionName::ADC,
		RegName::BL,
		RegName::R10B,
	}},{

	"10405d",
	"ADC BYTE PTR DS:[RAX+5D],AL",
	{
		InstructionName::ADC,
		{1, RegName::RAX, 0x5D},
		RegName::AL,
	}},{

	"4110405d",
	"ADC BYTE PTR DS:[R8+5D],AL",
	{
		InstructionName::ADC,
		{1, RegName::R8, 0x5D},
		RegName::AL,
	}},{

	"441012",
	"ADC BYTE PTR DS:[RDX],R10B",
	{
		InstructionName::ADC,
		{1, RegName::RDX},
		RegName::R10B,
	}},{

	"411012",
	"ADC BYTE PTR DS:[R10],DL",
	{
		InstructionName::ADC,
		{1, RegName::R10},
		RegName::DL,
	}},{

	"401028",
	"ADC BYTE PTR DS:[RAX],BPL",
	{
		InstructionName::ADC,
		{1, RegName::RAX},
		RegName::BPL,
	}},{

	"41105501",
	"ADC BYTE PTR DS:[R13+1],DL",
	{
		InstructionName::ADC,
		{1, RegName::R13, 1},
		RegName::DL,
	}},{

	"42100c50",
	"ADC BYTE PTR DS:[RAX+R10*2],CL",
	{
		InstructionName::ADC,
		{1, RegName::RAX, RegName::R10, 2, 0},
		RegName::CL,
	}},{

	"42100c20",
	"ADC BYTE PTR DS:[RAX+R12],CL",
	{
		InstructionName::ADC,
		{1, RegName::RAX, RegName::R12},
		RegName::CL,
	}},{

	"10442008",
	"ADC BYTE PTR DS:[RAX+8],AL",
	{
		InstructionName::ADC,
		{1, RegName::RAX, 8},
		RegName::AL,
	}},{

	"42100c0508000000",
	"ADC BYTE PTR DS:[R8+8],CL",
	{
		InstructionName::ADC,
		{1, RegName::NONE, RegName::R8, 8},
		RegName::CL,
	}},{

	"4310440508",
	"ADC BYTE PTR DS:[R13+R8+8],AL",
	{
		InstructionName::ADC,
		{1, RegName::R13, RegName::R8, 8},
		RegName::AL,
	}},{

	"4310042508000000",
	"ADC BYTE PTR DS:[R12+8],AL",
	{
		InstructionName::ADC,
		{1, RegName::NONE, RegName::R12, 8},
		RegName::AL,
	}},{

	"4210042508000000",
	"ADC BYTE PTR DS:[R12+8],AL",
	{
		InstructionName::ADC,
		{1, RegName::NONE, RegName::R12, 8},
		RegName::AL,
	}},{


	"41105dc3",
	"ADC BYTE PTR DS:[R13-3D],BL",
	{
		InstructionName::ADC,
		{1, RegName::R13, -0x3D},
		RegName::BL,
	}},{


	"4110445d08",
	"ADC BYTE PTR DS:[R13+RBX*2+8],AL",
	{
		InstructionName::ADC,
		{1, RegName::R13, RegName::RBX, 2, 8},
		RegName::AL,
	}},{


	"664401c3",
	"ADD BX,R8W",
	{
		InstructionName::ADD,
		RegName::BX,
		RegName::R8W,
	}},{


	"101508000000",
//	"00000000`0428fb19 101508000000    ADC BYTE PTR DS:[00000000`0428FB27],DL",
	"",
	{
		InstructionName::ADC,
		Operand::RELATIVE_MEM (1, 8),
		RegName::DL,
	}},{


	"1015ffffffff",
//	"00000000`0428fb19 1015ffffffff    ADC BYTE PTR DS:[00000000`0428FB1E],DL",
	"",
	{
		InstructionName::ADC,
		Operand::RELATIVE_MEM (1, -1),
		RegName::DL,
	}},{


	"481100",
	"ADC QWORD PTR DS:[RAX],RAX",
	{
		InstructionName::ADC,
		{8, RegName::RAX},
		RegName::RAX,
	}},{


	"66481100",
	"ADC QWORD PTR DS:[RAX],RAX",
	{
		InstructionName::ADC,
		{8, RegName::RAX},
		RegName::RAX,
	}},{


	"114811",
	"ADC DWORD PTR DS:[RAX+11],ECX",
	{
		InstructionName::ADC,
		{4, RegName::RAX, 0x11},
		RegName::ECX,
	}},{


	"661111",
	"ADC WORD PTR DS:[RCX],DX",
	{
		InstructionName::ADC,
		{2, RegName::RCX},
		RegName::DX,
	}},{


	"480511000000",
	"ADD RAX,11",
	{
		InstructionName::ADD,
		RegName::RAX,
		Operand::IMM (4, 0x11),
	}},{


	"e505",
	"IN EAX,5",
	{
		InstructionName::IN,
		RegName::EAX,
		0x5,
	}},{


	"66e505",
	"IN AX,5",
	{
		InstructionName::IN,
		RegName::AX,
		0x5,
	}},{


	"48e505",
	"IN EAX,5",
	{
		InstructionName::IN,
		RegName::EAX,
		0x5,
	}},{


	"6648e500",
	"IN EAX,0",
	{
		InstructionName::IN,
		RegName::EAX,
		0x0,
	}},{


	"004b4c",
	"ADD BYTE PTR DS:[RBX+4C],CL",
	{
		InstructionName::ADD,
		{1, RegName::RBX, 0x4C},
		RegName::CL,
	}},{


	"66004c7700",
	"ADD BYTE PTR DS:[RDI+RSI*2],CL",
	{
		InstructionName::ADD,
		{1, RegName::RDI, RegName::RSI, 2, 0},
		RegName::CL,
	}},{


	"48004c7700",
	"ADD BYTE PTR DS:[RDI+RSI*2],CL",
	{
		InstructionName::ADD,
		{1, RegName::RDI, RegName::RSI, 2, 0},
		RegName::CL,
	}},{


	"6648007700",
	"ADD BYTE PTR DS:[RDI],SIL",
	{
		InstructionName::ADD,
		{1, RegName::RDI},
		RegName::SIL,
	}},{


	"50",
	"PUSH RAX",
	{
		InstructionName::PUSH,
		{
			RegName::RAX,
		}
	}},{


	"6650",
	"PUSH AX",
	{
		InstructionName::PUSH,
		{
			RegName::AX,
		}
	}},{



	"4850",
	"PUSH RAX",
	{
		InstructionName::PUSH,
		{
			RegName::RAX,
		}
	}},{


	"664850",
	"PUSH RAX",
	{
		InstructionName::PUSH,
		{
			RegName::RAX,
		}
	}},{


	"91",
	"XCHG EAX,ECX",
	{
		InstructionName::XCHG,
		{
			RegName::EAX,
			RegName::ECX,
		}
	}},{


	"6691",
	"XCHG AX,CX",
	{
		InstructionName::XCHG,
		{
			RegName::AX,
			RegName::CX,
		}
	}},{

	"4891",
	"XCHG RAX,RCX",
	{
		InstructionName::XCHG,
		{
			RegName::RAX,
			RegName::RCX,
		}
	}},{

	"664891",
	"XCHG RAX,RCX",
	{
		InstructionName::XCHG,
		{
			RegName::RAX,
			RegName::RCX,
		}
	}},{

	"664191",
	"XCHG AX,R9W",
	{
		InstructionName::XCHG,
		{
			RegName::AX,
			RegName::R9W,
		}
	}},{

	"4191",
	"XCHG EAX,R9D",
	{
		InstructionName::XCHG,
		{
			RegName::EAX,
			RegName::R9D,
		}
	}},{

	"4991",
	"XCHG RAX,R9",
	{
		InstructionName::XCHG,
		{
			RegName::RAX,
			RegName::R9,
		}
	}},{

	"664991",
	"XCHG RAX,R9",
	{
		InstructionName::XCHG,
		{
			RegName::RAX,
			RegName::R9,
		}
	}},{

	"41b001",
	"MOV R8B,1",
	{
		InstructionName::MOV,
		{
			RegName::R8B,
			0x1,
		}
	}},{

	"b001",
	"MOV AL,1",
	{
		InstructionName::MOV,
		{
			RegName::AL,
			0x1,
		}
	}},{

	"48b001",
	"MOV AL,1",
	{
		InstructionName::MOV,
		{
			RegName::AL,
			0x1,
		}
	}},{

	"66b001",
	"MOV AL,1",
	{
		InstructionName::MOV,
		{
			RegName::AL,
			0x1,
		}
	}},{

	"c23412",
	"RETN 1234",
	{
		InstructionName::RETN,
		{
			0x1234,
		}
	}},{

	"66c23412",
	"RETN 1234",
	{
		InstructionName::RETN,
		{
			0x1234,
		}
	}},{

	"48c23412",
	"RETN 1234",
	{
		InstructionName::RETN,
		{
			0x1234,
		}
	}},{

	"6648c23412",
	"RETN 1234",
	{
		InstructionName::RETN,
		{
			0x1234,
		}
	}},{

	"480511000000",
	"ADD RAX,11",
	{
		InstructionName::ADD,
		{
			RegName::RAX,
			Operand::IMM (4, 0x11),
		}
	}},{

	"4c0511000000",
	"ADD RAX,11",
	{
		InstructionName::ADD,
		{
			RegName::RAX,
			Operand::IMM (4, 0x11),
		}
	}},{

	"66480500000000",
	"ADD RAX,0",
	{
		InstructionName::ADD,
		{
			RegName::RAX,
			Operand::IMM (4, 0),
		}
	}},{

	"66051100",
	"ADD AX,11",
	{
		InstructionName::ADD,
		{
			RegName::AX,
			Operand::IMM (2, 0x11),
		}
	}},{

	"7063",
//	"00000000`7741c693 7063            jo      00000000`7741c6f8",
	"",
	{
		InstructionName::JO,
		{
			0x63,
		}
	}},{

	"6670cc",
//	"00000000`7741c695 6670cc          jo      00000000`0000c664",
	"",
	{
		InstructionName::JO,
		{
			0xCC,
		}
	}},{

	"4870cc",
//	"00000000`7741c695 4870cc          jo      00000000`7741c664",
	"",
	{
		InstructionName::JO,
		{
			0xCC,
		}
	}},{

	"66487001",
//	"00000000`7741c695 66487001        jo      00000000`7741c69a",
	"",
	{
		InstructionName::JO,
		{
			0x01,
		}
	}},{

	"105208",
	"ADC BYTE PTR DS:[RDX+8],DL",
	{
		InstructionName::ADC,
		{
			{1, RegName::RDX, 0x8},
			RegName::DL,
		}
	}},{

	"109208000000",
	"ADC BYTE PTR DS:[RDX+8],DL",
	{
		InstructionName::ADC,
		{
			{1, RegName::RDX, 0x8},
			RegName::DL,
		}
	}},{

	"100c0508000000",
	"ADC BYTE PTR DS:[RAX+8],CL",
	{
		InstructionName::ADC,
		{
			{1, RegName::NONE, RegName::RAX, 1, 0x8},
			RegName::CL,
		}
	}},{

	"10042508000000",
	"ADC BYTE PTR DS:[8],AL",
	{
		InstructionName::ADC,
		{
			{1, 0x8},
			RegName::AL,
		}
	}},{

	"10045d08000000",
	"ADC BYTE PTR DS:[RBX*2+8],AL",
	{
		InstructionName::ADC,
		{
			{1, RegName::RBX, 2, 0x8},
			RegName::AL,
		}
	}},{

	"10445d08",
	"ADC BYTE PTR SS:[RBP+RBX*2+8],AL",
	{
		InstructionName::ADC,
		{
			{1, RegName::RBP, RegName::RBX, 2, 0x8},
			RegName::AL,
		}
	}},{

	"1100",
	"ADC DWORD PTR DS:[RAX],EAX",
	{
		InstructionName::ADC,
		{
			{4, RegName::RAX},
			RegName::EAX,
		}
	}},{

	"66051100",
	"ADD AX,11",
	{
		InstructionName::ADD,
		{
			RegName::AX,
			Operand::IMM (2, 0x11),
		}
	}},{

	"0505110000",
	"ADD EAX,1105",
	{
		InstructionName::ADD,
		{
			RegName::EAX,
			Operand::IMM (4, 0x1105),
		}
	}},{

	"06",
	"???",
	{
		InstructionName::_INVALID,
	}},{

	"4863c3",
	"MOVSXD RAX,EBX",
	{
		InstructionName::MOVSXD,
		{
			RegName::RAX,
			RegName::EBX,
		}
	}},{

	"4990",
	"XCHG RAX,R8",
	{
		InstructionName::XCHG,
		{
			RegName::RAX,
			RegName::R8,
		}
	}},{

	"a4",
	"MOVS BYTE PTR ES:[RDI],BYTE PTR DS:[RSI]",
	{
		InstructionName::MOVS,
		{
			{1, RegName::RDI},
			{1, RegName::RSI},
		}
	}},{

	"48a5",
	"MOVS QWORD PTR ES:[RDI],QWORD PTR DS:[RSI]",
	{
		InstructionName::MOVS,
		{
			{8, RegName::RDI},
			{8, RegName::RSI},
		}
	}},{

	"8fc5",
	"POP RBP",
	{
		InstructionName::POP,
		{
			RegName::RBP,
		}
	}},{

	"4898",
	"CDQE",
	{
		InstructionName::CDQE,
	}},{

	"4899",
	"CQO",
	{
		InstructionName::CQO,
	}},{

	"0f05",
	"SYSCALL",
	{
		InstructionName::SYSCALL,
	}},{

	"9c",
	"PUSHFQ",
	{
		InstructionName::PUSHFQ,
	}},{

	"41b883c438c3",
	"MOV R8D,C338C483",
	{
		InstructionName::MOV,
		{
			RegName::R8D,
			0xC338C483,
		}
	}},{

	"0f07",
	"SYSRET",
	{
		InstructionName::SYSRET,
	}},{

	"cf",
	"IRETD",
	{
		InstructionName::IRETD,
	}},{

	"48cf",
	"IRETQ",
	{
		InstructionName::IRETQ,
	}},{

	"4110d3",
	"ADC R11B,DL",
	{
		InstructionName::ADC,
		RegName::R11B,
		RegName::DL,
	}},
};

#if 0 //x64
            

66a5            MOVS WORD PTR ES:[RDI],WORD PTR DS:[RSI]
a5              MOVS DWORD PTR ES:[RDI],DWORD PTR DS:[RSI]

4190            XCHG EAX,R8D
664190          XCHG AX,R8W
90              NOP

0fbfc3          MOVSX EAX,BX
480fbfc3        MOVSX RAX,BX
660fbec3        MOVSX AX,BL
0fbec3          MOVSX EAX,BL
480fbec3        MOVSX RAX,BL
#endif

#if 0 //x64  和x86一样
#endif

#if 0 //x64  和x86不一样
#endif

#if 0 //x64 多余但不算错

4810d3          ADC     BL,DL
4010d3          ADC     BL,DL
00000000`0428fb18 401015FFFFFFFF  ADC     BYTE PTR [00000000`0428FB1E],DL
00000000`0428fb18 411015FFFFFFFF  ADC     BYTE PTR [00000000`0428FB1E],DL
00000000`0428fb18 41101501000000  ADC     BYTE PTR [00000000`0428FB20],DL
00000000`0428fb18 411005C3080000  ADC     BYTE PTR [00000000`042903E2],AL
401012           ADC BYTE PTR DS:[RDX],DL
40100c20         ADC BYTE PTR DS:[RAX],CL
40100c0508000000 ADC BYTE PTR DS:[RAX+8],CL
41100c0508000000 ADC BYTE PTR DS:[RAX+8],CL
4010042508000000 ADC BYTE PTR DS:[8],AL
4110045d08000000 ADC BYTE PTR DS:[RBX*2+8],AL

#endif
