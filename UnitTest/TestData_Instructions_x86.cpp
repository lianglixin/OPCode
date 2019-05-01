#include "TestData.h"


const std::vector <TestData::ExpectedInstruction> TestData::_instructions_x86
{{
	"1902",
	"SBB DWORD PTR DS:[EDX],EAX",
	InstructionName::SBB,
	{4, RegName::EDX},
	RegName::EAX},{


	"8945E4",
	"MOV DWORD PTR SS:[EBP-1C],EAX",
	InstructionName::MOV,
	{4, SegName::SS, RegName::EBP, -0x1C},
	RegName::EAX},{


	"0900",
	"OR DWORD PTR DS:[EAX],EAX",
	InstructionName::OR,
	{4, RegName::EAX},
	RegName::EAX},{


	"290A",
	"SUB DWORD PTR DS:[EDX],ECX",
	InstructionName::SUB,
	{4, RegName::EDX},
	RegName::ECX},{


	"390A",
	"CMP DWORD PTR DS:[EDX],ECX",
	InstructionName::CMP,
	{4, RegName::EDX},
	RegName::ECX},{


	"39A304005EBF",
	"CMP DWORD PTR DS:[EBX+BF5E0004],ESP",
	InstructionName::CMP,
	{4, RegName::EBX, (int) 0xBF5E0004},
	RegName::ESP},{


	"0B00",
	"OR EAX,DWORD PTR DS:[EAX]",
	InstructionName::OR,
	RegName::EAX,
	{4, RegName::EAX}},{


	"1BE3",
	"SBB ESP,EBX",
	InstructionName::SBB,
	RegName::ESP,
	RegName::EBX},{


	"2B75 06",
	"SUB ESI,DWORD PTR SS:[EBP+6]",
	InstructionName::SUB,
	RegName::ESI,
	{4, SegName::SS, RegName::EBP, 6}},{


	"3BF7",
	"CMP ESI,EDI",
	InstructionName::CMP,
	RegName::ESI,
	RegName::EDI},{


	"8BFF",
	"MOV EDI,EDI",
	InstructionName::MOV,
	RegName::EDI,
	RegName::EDI},{


	"2A2A",
	"SUB CH,BYTE PTR DS:[EDX]",
	InstructionName::SUB,
	RegName::CH,
	{1, RegName::EDX}},{


	"2825 77733A20",
	"SUB BYTE PTR DS:[203A7377],AH",
	InstructionName::SUB,
	{1, 0x203A7377},
	RegName::AH},{


	"8095 77909090 90",
	"ADC BYTE PTR SS:[EBP+90909077],90",
	InstructionName::ADC,
	{1, SegName::SS, RegName::EBP, 0x90909077},
	Operand::IMM (1, 0x90)},{


	"80FF FF",
	"CMP BH,0FF",
	InstructionName::CMP,
	RegName::BH,
	Operand::IMM (1, 0xFF)},{


	"8000 00",
	"ADD BYTE PTR DS:[EAX],0",
	InstructionName::ADD,
	{1, RegName::EAX},
	Operand::IMM (1, 0)},{


	"81C7 20070000",
	"ADD EDI,720",
	InstructionName::ADD,
	RegName::EDI,
	Operand::IMM (4, 0x720)},{


	"81EC 1C020000",
	"SUB ESP,21C",
	InstructionName::SUB,
	RegName::ESP,
	Operand::IMM (4, 0x21C)},{


	"83C4 04",
	"ADD ESP,4",
	InstructionName::ADD,
	RegName::ESP,
	Operand::IMM (1, 0x4)},{


	"83E1 07",
	"AND ECX,7",
	InstructionName::AND,
	RegName::ECX,
	Operand::IMM (1, 0x7)},{


	"C685 ECFEFFFF 00",
	"MOV BYTE PTR SS:[EBP-114],0",
	InstructionName::MOV,
	{1, SegName::SS, RegName::EBP, -0x114},
	Operand::IMM (1, 0x0)},{


	"C785 64FBFFFF 7A33D011",
	"MOV DWORD PTR SS:[EBP-49C],11D0337A",
	InstructionName::MOV,
	{4, SegName::SS, RegName::EBP, -0x49C},
	Operand::IMM (4, 0x11D0337A)},{


	"C082 E69A89BD 70",
	"ROL BYTE PTR DS:[EDX+BD899AE6],70",
	InstructionName::ROL,
	{1, RegName::EDX, 0xBD899AE6},
	Operand::IMM (1, 0x70)},{


	"C0FC FF",
	"SAR AH,0FF",
	InstructionName::SAR,
	RegName::AH,
	0xFF},{


	"C1E8 1F",
	"SHR EAX,1F",
	InstructionName::SHR,
	RegName::EAX,
	0x1F},{


	"D0D1",
	"RCL CL,1",
	InstructionName::RCL,
	RegName::CL,
	0x1},{


	"D1C1",
	"ROL ECX,1",
	InstructionName::ROL,
	RegName::ECX,
	0x1},{


	"D253 89",
	"RCL BYTE PTR DS:[EBX-77],CL",
	InstructionName::RCL,
	{1, RegName::EBX, -0x77},
	RegName::CL},{


	"D38B 4DFC8B91",
	"ROR DWORD PTR DS:[EBX+918BFC4D],CL",
	InstructionName::ROR,
	{4, RegName::EBX, 0x918BFC4D},
	RegName::CL},{


	"F645 08 01",
	"TEST BYTE PTR SS:[EBP+8],1",
	InstructionName::TEST,
	{1, SegName::SS, RegName::EBP, 0x8},
	0x1},{


	"F656 E8",
	"NOT BYTE PTR DS:[ESI-18]",
	InstructionName::NOT,
	{1, RegName::ESI, -0x18}},{


	"F7D0",
	"NOT EAX",
	InstructionName::NOT,
	RegName::EAX},{


	"8F00",
	"POP DWORD PTR DS:[EAX]",
	InstructionName::POP,
	{4, RegName::EAX}},{


	"8FC6",
	"POP ESI",
	InstructionName::POP,
	RegName::ESI},{


	"FE8D 53E08945",
	"DEC BYTE PTR SS:[EBP+4589E053]",
	InstructionName::DEC,
	{1, SegName::SS, RegName::EBP, 0x4589E053}},{


	"FE02",
	"INC BYTE PTR DS:[EDX]",
	InstructionName::INC,
	{1, RegName::EDX}},{


	"FF85 C00F84CD",
	"INC DWORD PTR SS:[EBP+CD840FC0]",
	InstructionName::INC,
	{4, SegName::SS, RegName::EBP, 0xCD840FC0}},{


	"2C 03",
	"SUB AL,3",
	InstructionName::SUB,
	RegName::AL,
	0x3},{


	"2D 760B009F",
	"SUB EAX,9F000B76",
	InstructionName::SUB,
	RegName::EAX,
	0x9F000B76},{


	"0E",
	"PUSH CS",
	InstructionName::PUSH,
	SegName::CS},{


	"1E",
	"PUSH DS",
	InstructionName::PUSH,
	SegName::DS},{


	"40",
	"INC EAX",
	InstructionName::INC,
	RegName::EAX},{


	"A0 01001F90",
	"MOV AL,BYTE PTR DS:[901F0001]",
	InstructionName::MOV,
	RegName::AL,
	{1, 0x901F0001}},{


	"A1 01002EA1",
	"MOV EAX,DWORD PTR DS:[A12E0001]",
	InstructionName::MOV,
	RegName::EAX,
	{4, 0xA12E0001}},{


	"A2 010025A2",
	"MOV BYTE PTR DS:[A2250001],AL",
	InstructionName::MOV,
	{1, 0xA2250001},
	RegName::AL},{


	"A3 01002DA3",
	"MOV DWORD PTR DS:[A32D0001],EAX",
	InstructionName::MOV,
	{4, 0xA32D0001},
	RegName::EAX},{


	"90",
	"NOP",
	InstructionName::NOP},{


	"895C28 08",
	"MOV DWORD PTR DS:[EAX+EBP+8],EBX",
	InstructionName::MOV,
	{4, RegName::EAX, RegName::EBP, 0x8},
	RegName::EBX},{


	"895C05 08",
	"MOV DWORD PTR SS:[EBP+EAX+8],EBX",
	InstructionName::MOV,
	{4, SegName::SS, RegName::EBP, RegName::EAX, 0x8},
	RegName::EBX},{


	"0FB690 908BD40F",
	"MOVZX EDX,BYTE PTR DS:[EAX+0FD48B90]",
	InstructionName::MOVZX,
	RegName::EDX,
	{1, RegName::EAX, 0xFD48B90}},{


	"66:04 01",
	"ADD AL,1",
	InstructionName::ADD,
	RegName::AL,
	0x1},{


	"66:05 00DC",
	"ADD AX,0DC00",
	InstructionName::ADD,
	RegName::AX,
	0xDC00},{


	"66:8B01",
	"MOV AX,WORD PTR DS:[ECX]",
	InstructionName::MOV,
	RegName::AX,
	{2, RegName::ECX}},{


	"66:8B45 FC",
	"MOV AX,WORD PTR SS:[EBP-4]",
	InstructionName::MOV,
	RegName::AX,
	{2, SegName::SS, RegName::EBP, -0x4}},{


	"66:B8 3600",
	"MOV AX,36",
	InstructionName::MOV,
	RegName::AX,
	Operand::IMM (2, 0x36)},{


	"66:A1 DBD40A00",
	"MOV AX,WORD PTR DS:[AD4DB]",
	InstructionName::MOV,
	RegName::AX,
	{2, 0xAD4DB}},{


	"66:40",
	"INC AX",
	InstructionName::INC,
	RegName::AX},{


	"66:2E:A1 DBD40A00",
	"MOV AX,WORD PTR CS:[AD4DB]",
	InstructionName::MOV,
	RegName::AX,
	{2, SegName::CS, 0xAD4DB}},{


	"66:36:A1 DBD40A00",
	"MOV AX,WORD PTR SS:[AD4DB]",
	InstructionName::MOV,
	RegName::AX,
	{2, SegName::SS, 0xAD4DB}},{


	"66:26:A1 DBD40A00",
	"MOV AX,WORD PTR ES:[AD4DB]",
	InstructionName::MOV,
	RegName::AX,
	{2, SegName::ES, 0xAD4DB}},{


	"66:3E:8B45 00",
	"MOV AX,WORD PTR DS:[EBP]",
	InstructionName::MOV,
	RegName::AX,
	{2, SegName::DS, RegName::EBP}},{


	"66:64:8B45 00",
	"MOV AX,WORD PTR FS:[EBP]",
	InstructionName::MOV,
	RegName::AX,
	{2, SegName::FS, RegName::EBP}},{


	"E8 90909083",
	"",
	//				"013D1AE6   CALL 84CDAB7B",
	InstructionName::CALL,
	0x83909090},{


	"66:E8 0FB6",
	"",
	//				"013D1AEB   CALL 0000D0FE",
	InstructionName::CALL,
	0xB60F},{


	"E9 FE6800E0",
	"",
	//				"7715020C             JMP 57156B0F",
	InstructionName::JMP_NEAR,
	0xE00068FE},{


	"66:E9 5500",
	"",
	//				"7715021D              JMP 00000276",
	InstructionName::JMP_NEAR,
	Operand::IMM (2, 0x55)},{


	"EB FF",
	"",
	//				"77150225         JMP SHORT ntdll.77150226",
	InstructionName::JMP_SHORT,
	0xFF},{


	"75 54",
	"",
	//				"013D1B27          JNZ SHORT Project4.013D1B7D",
	InstructionName::JNZ,
	0x54},{


	"74 0E",
	"",
	//				"013D1BEB     JE SHORT Project4.013D1BFB",
	InstructionName::JE,
	0x0E},{


	"AB",
	"STOS DWORD PTR ES:[EDI],EAX",
	InstructionName::STOS,
	{4, SegName::ES, RegName::EDI},
	RegName::EAX,
	},{


	"AA",
	"STOS BYTE PTR ES:[EDI],AL",
	InstructionName::STOS,
	{1, SegName::ES, RegName::EDI},
	RegName::AL,
	},{


	"66:AB",
	"STOS WORD PTR ES:[EDI],AX",
	InstructionName::STOS,
	{2, SegName::ES, RegName::EDI},
	RegName::AX,
	},{


	"66:AD",
	"LODS AX,WORD PTR DS:[ESI]",
	InstructionName::LODS,
	RegName::AX,
	{2, SegName::DS, RegName::ESI}},{


	"AD",
	"LODS EAX,DWORD PTR DS:[ESI]",
	InstructionName::LODS,
	RegName::EAX,
	{4, SegName::DS, RegName::ESI}},{


	"AC",
	"LODS AL,BYTE PTR DS:[ESI]",
	InstructionName::LODS,
	RegName::AL,
	{1, SegName::DS, RegName::ESI}},{


	"DBE2",
	"FCLEX",
	InstructionName::FCLEX},{


	"A5",
	"MOVS DWORD PTR ES:[EDI],DWORD PTR DS:[ESI]",
	InstructionName::MOVS,
	{4, SegName::ES, RegName::EDI},
	{4, SegName::DS, RegName::ESI}},{


	"66:A5",
	"MOVS WORD PTR ES:[EDI],WORD PTR DS:[ESI]",
	InstructionName::MOVS,
	{2, SegName::ES, RegName::EDI},
	{2, SegName::DS, RegName::ESI}},{


	"A4",
	"MOVS BYTE PTR ES:[EDI],BYTE PTR DS:[ESI]",
	InstructionName::MOVS,
	{1, SegName::ES, RegName::EDI},
	{1, SegName::DS, RegName::ESI}},{


	"A7",
	"CMPS DWORD PTR DS:[ESI],DWORD PTR ES:[EDI]",
	InstructionName::CMPS,
	{4, SegName::DS, RegName::ESI},
	{4, SegName::ES, RegName::EDI}},{


	"66:A7",
	"CMPS WORD PTR DS:[ESI],WORD PTR ES:[EDI]",
	InstructionName::CMPS,
	{2, SegName::DS, RegName::ESI},
	{2, SegName::ES, RegName::EDI}},{


	"06",
	"PUSH ES",
	InstructionName::PUSH,
	SegName::ES},{


	"07",
	"POP ES",
	InstructionName::POP,
	SegName::ES},{


	"16",
	"PUSH SS",
	InstructionName::PUSH,
	SegName::SS},{


	"17",
	"POP SS",
	InstructionName::POP,
	SegName::SS},{


	"27",
	"DAA",
	InstructionName::DAA},{


	"60",
	"PUSHAD",
	InstructionName::PUSHA},{


	"61",
	"POPAD",
	InstructionName::POPA},{


	"623D 34120000",
	"BOUND EDI,QWORD PTR DS:[1234]",
	InstructionName::BOUND,
	RegName::EDI,
	{8, 0x1234}},{


	"66:623D 34120000",
	"BOUND DI,DWORD PTR DS:[1234]",
	InstructionName::BOUND,
	RegName::DI,
	{4, 0x1234}},{


	"63EB",
	"ARPL BX,BP",
	InstructionName::ARPL,
	RegName::BX,
	RegName::BP},{


	"70 70",
	"",
	//				"0040500E     70 70             JO SHORT 00405080",
	InstructionName::JO,
	0x70},{


	"71 71",
	"",
	//				"00405010     |71 71             JNO SHORT 00405083",
	InstructionName::JNO,
	0x71},{


	"72 72",
	"",
	//				"00405012     |72 72             JB SHORT 00405086",
	InstructionName::JB,
	0x72},{


	"73 73",
	"",
	//				"00405014     |73 73             JAE SHORT 00405089",
	InstructionName::JAE,
	0x73},{


	"76 00",
	"",
	//				"0040500E     /76 00             JBE SHORT 00405010",
	InstructionName::JBE,
	0x00},{


	"77 01",
	"",
	//				"00405010     \77 01             JA SHORT 00405013",
	InstructionName::JA,
	0x01},{


	"8200 77",
	"ADD BYTE PTR DS:[EAX],77",
	InstructionName::ADD,
	{1, RegName::EAX},
	0x77},{


	"86EB",
	"XCHG BL,CH",
	InstructionName::XCHG,
	RegName::BL,
	RegName::CH},{


	"8750 00",
	"XCHG DWORD PTR DS:[EAX],EDX",
	InstructionName::XCHG,
	{4, RegName::EAX},
	RegName::EDX},{


	"91",
	"XCHG EAX,ECX",
	InstructionName::XCHG,
	RegName::EAX,
	RegName::ECX},{


	"B0 50",
	"MOV AL,50",
	InstructionName::MOV,
	RegName::AL,
	0x50},{


	"C1E0 04",
	"SHL EAX,4",
	InstructionName::SHL,
	RegName::EAX,
	0x4},{


	"C1D8 04",
	"RCR EAX,4",
	InstructionName::RCR,
	RegName::EAX,
	0x4},{


	"C2 EBB0",
	"RETN 0B0EB",
	InstructionName::RETN,
	0xB0EB},{


	"C42D 00010000",
	"LES EBP,FWORD PTR DS:[100]",
	InstructionName::LES,
	RegName::EBP,
	{6, 0x100}},{

	"C52D 00204000",
	"LDS EBP,FWORD PTR DS:[402000]",
	InstructionName::LDS,
	RegName::EBP,
	{6, 0x402000}},{


	"66:C42D 00010000",
	"LES BP,DWORD PTR DS:[100]",
	InstructionName::LES,
	RegName::BP,
	{4, 0x100}},{


	"D4 08",
	"AAM 8",
	InstructionName::AAM,
	0x8},{


	"E7 49",
	"OUT 49,EAX",
	InstructionName::OUT,
	0x49,
	RegName::EAX},{


	"D7",
	"XLAT BYTE PTR DS:[EBX+AL]",
	InstructionName::XLAT},{


	"E0 00",
	"",
//	"0040501F     /E0 00             LOOPNZ SHORT 00405021",
	InstructionName::LOOPNZ,
	0x00},{


	"E3 10",
	"",
//	"00405027     /E3 10             JECXZ SHORT 00405039",
	InstructionName::JECXZ,
	0x10},{


	"67:E3 13",
	"",
//	"0040502C     /67:E3 13          JCXZ SHORT 00405042",
	InstructionName::JCXZ,
	0x13},{


	"F7FF",
	"IDIV EDI",
	InstructionName::IDIV,
	RegName::EDI},{


	"66:F7FF",
	"IDIV DI",
	InstructionName::IDIV,
	RegName::DI},{


	"F6FF",
	"IDIV BH",
	InstructionName::IDIV,
	RegName::BH},{


	"69C3 50555501",
	"IMUL EAX,EBX,1555550",
	InstructionName::IMUL,
	RegName::EAX,
	RegName::EBX,
	0x1555550},{


	"66:69C3 5055",
	"IMUL AX,BX,5550",
	InstructionName::IMUL,
	RegName::AX,
	RegName::BX,
	0x5550},{


	"699458 90909090 90909090",
	"",
//	"IMUL EDX,DWORD PTR DS:[EBX*2+EAX+90909090],-6F6F6F70",
	InstructionName::IMUL,
	RegName::EDX,
	{4, SegName::DS, RegName::EAX, RegName::EBX, 2, 0x90909090},
	-0x6F6F6F70},{


	"6B3E 00",
	"IMUL EDI,DWORD PTR DS:[ESI],0",
	InstructionName::IMUL,
	RegName::EDI,
	{4, RegName::ESI},
	0},{


	"8C00",
	"MOV WORD PTR DS:[EAX],ES",
	InstructionName::MOV,
	{2, RegName::EAX},
	SegName::ES},{


	"C8 2000 00",
	"ENTER 20,0",
	InstructionName::ENTER,
	Operand::IMM (2, 0x20),
	0},{


	"0FC7F0",
	"RDRAND EAX",
	InstructionName::RDRAND,
	RegName::EAX},{


	"EA C390E801 0000",
	"JMP FAR 0000:01E890C3",
	InstructionName::JMP_FAR,
	Operand::IMM (6, 0x01E890C3, 0x0000)},{


	"EC",
	"IN AL,DX",
	InstructionName::IN,
	RegName::AL,
	RegName::DX},{


	"F3:AD",
	"REP LODS EAX,DWORD PTR DS:[ESI]",
	{
		Prefix::REP,
		InstructionName::LODS,
		{
			RegName::EAX,
			{4, SegName::DS, RegName::ESI},
		}
	}},{


	"F3:AB",
	"REP STOS DWORD PTR ES:[EDI],EAX",
	{
		Prefix::REP,
		InstructionName::STOS,
		{
			{4, SegName::ES, RegName::EDI},
			RegName::EAX,
		}
	}},{


	"F3:A7",
	"REPE CMPS DWORD PTR DS:[ESI],DWORD PTR ES:[EDI]",
	{
		Prefix::REPE,
		InstructionName::CMPS,
		{
			{4, SegName::DS, RegName::ESI},
			{4, SegName::ES, RegName::EDI},
		}
	}},{


	"F3:AF",
	"REPE SCAS EAX,DWORD PTR ES:[EDI]",
	{
		Prefix::REPE,
		InstructionName::SCAS,
		{
			RegName::EAX,
			{4, SegName::ES, RegName::EDI},
		}
	}},{


	"F3:A5",
	"REP MOVS DWORD PTR ES:[EDI],DWORD PTR DS:[ESI]",
	{
		Prefix::REP,
		InstructionName::MOVS,
		{
			{4, SegName::ES, RegName::EDI},
			{4, SegName::DS, RegName::ESI},
		}
	}},{


	"F2:AD",
	"REPNE LODS EAX,DWORD PTR DS:[ESI]",
	{
		Prefix::REPNE,
		InstructionName::LODS,
		{
			RegName::EAX,
			{4, SegName::DS, RegName::ESI},
		}
	}},{


	"F0:0105 00204000",
	"LOCK ADD DWORD PTR DS:[402000],EAX",
	{
		Prefix::LOCK,
		InstructionName::ADD,
		{4, 0x402000},
		RegName::EAX,
	}},{


	"65:008B 9D310500",
	"ADD BYTE PTR GS:[EBX+5319D],CL",
	InstructionName::ADD,
	{1, SegName::GS, RegName::EBX, 0x5319D},
	RegName::CL},{


	"A6",
	"CMPS BYTE PTR DS:[ESI],BYTE PTR ES:[EDI]",
	{
		InstructionName::CMPS,
		{
			{1, SegName::DS, RegName::ESI},
			{1, SegName::ES, RegName::EDI},
		}
	}}
};

//not support:
//			77B9021D   F3:36:A7         REPE CMPS DWORD PTR ES:[EDI], DWORD PTR SS:[ESI]