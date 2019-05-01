#include "TestData.h"


const std::vector <TestData::ExpectedInstructions> TestData::_instructions
{{


R"(
F2:AB
F2:AD
F2:A7
F2:AF
F2:A5
)"
,
R"(REPNE STOS DWORD PTR ES:[EDI],EAX
REPNE LODS EAX,DWORD PTR DS:[ESI]
REPNE CMPS DWORD PTR DS:[ESI],DWORD PTR ES:[EDI]
REPNE SCAS EAX,DWORD PTR ES:[EDI]
REPNE MOVS DWORD PTR ES:[EDI],DWORD PTR DS:[ESI]
)"
	},{
R"(
5E               
B8 F9FFFFFF      
5F               
8B4D FC          
33CD             
8BE5             
5D               
C3               
33D2             
33C9             
8D6424 00        
8A043A           
88840D FCFDFFFF  
8D42 01          
99               
888C0D FCFEFFFF  
41               
F7FE             
81F9 00010000    
33C9             
33C0             
53               
8DA424 00000000  
8BFF             
8A9405 FCFEFFFF  
0FB6FA           
03CE             
03CF             
81E1 FF000080    
49               
81C9 00FFFFFF    
41               
8A9C0D FCFEFFFF  
88940D FCFEFFFF  
889C05 FCFEFFFF  
40               
3D 00010000
)"
,
R"(POP ESI
MOV EAX,-7
POP EDI
MOV ECX,DWORD PTR SS:[EBP-4]
XOR ECX,EBP
MOV ESP,EBP
POP EBP
RETN
XOR EDX,EDX
XOR ECX,ECX
LEA ESP,DWORD PTR SS:[ESP]
MOV AL,BYTE PTR DS:[EDX+EDI]
MOV BYTE PTR SS:[EBP+ECX-204],AL
LEA EAX,DWORD PTR DS:[EDX+1]
CDQ
MOV BYTE PTR SS:[EBP+ECX-104],CL
INC ECX
IDIV ESI
CMP ECX,100
XOR ECX,ECX
XOR EAX,EAX
PUSH EBX
LEA ESP,DWORD PTR SS:[ESP]
MOV EDI,EDI
MOV DL,BYTE PTR SS:[EBP+EAX-104]
MOVZX EDI,DL
ADD ECX,ESI
ADD ECX,EDI
AND ECX,800000FF
DEC ECX
OR ECX,FFFFFF00
INC ECX
MOV BL,BYTE PTR SS:[EBP+ECX-104]
MOV BYTE PTR SS:[EBP+ECX-104],DL
MOV BYTE PTR SS:[EBP+EAX-104],BL
INC EAX
CMP EAX,100
)"
	},{
R"(
DBD0
DBD1
DBD2
DBD3
DBD4
DBD5
DBD6
DBD7

DBC8
DBC9
DBCA
DBCB
DBCC
DBCD
DBCE
DBCF

DBD8
DBD9
DBDA
DBDB
DBDC
DBDD
DBDE
DBDF

D800
D808
D810
D818
D820
D828
D830
D838


D900   
D910   
D918   
D920   
D930   
66:D930
D928   
D938   

DA00
DA08
DA10
DA18
DA20
DA28
DA30
DA38


DB00
DB08
DB10
DB18
DB28
DB38


DC00
DC08
DC10
DC18
DC20
DC28
DC30
DC38


DD00   
DD10   
DD18   
DD08   
DD20   
DD30   
66:DD30
DD38   


DE00
DE10
DE18
DE20
DE28
DE08
DE30
DE38


DF00
DF08
DF10
DF18
DF20
DF28
DF30
DF38

DFF0
DFF1
DFF2
DFF3
DFF4
DFF5
DFF6
DFF7

)"
,
R"(FCMOVNBE ST,ST
FCMOVNBE ST,ST(1)
FCMOVNBE ST,ST(2)
FCMOVNBE ST,ST(3)
FCMOVNBE ST,ST(4)
FCMOVNBE ST,ST(5)
FCMOVNBE ST,ST(6)
FCMOVNBE ST,ST(7)
FCMOVNE ST,ST
FCMOVNE ST,ST(1)
FCMOVNE ST,ST(2)
FCMOVNE ST,ST(3)
FCMOVNE ST,ST(4)
FCMOVNE ST,ST(5)
FCMOVNE ST,ST(6)
FCMOVNE ST,ST(7)
FCMOVNU ST,ST
FCMOVNU ST,ST(1)
FCMOVNU ST,ST(2)
FCMOVNU ST,ST(3)
FCMOVNU ST,ST(4)
FCMOVNU ST,ST(5)
FCMOVNU ST,ST(6)
FCMOVNU ST,ST(7)
FADD DWORD PTR DS:[EAX]
FMUL DWORD PTR DS:[EAX]
FCOM DWORD PTR DS:[EAX]
FCOMP DWORD PTR DS:[EAX]
FSUB DWORD PTR DS:[EAX]
FSUBR DWORD PTR DS:[EAX]
FDIV DWORD PTR DS:[EAX]
FDIVR DWORD PTR DS:[EAX]
FLD DWORD PTR DS:[EAX]
FST DWORD PTR DS:[EAX]
FSTP DWORD PTR DS:[EAX]
FLDENV 28BYTE PTR DS:[EAX]
FSTENV 28BYTE PTR DS:[EAX]
FSTENV 14BYTE PTR DS:[EAX]
FLDCW WORD PTR DS:[EAX]
FSTCW WORD PTR DS:[EAX]
FIADD DWORD PTR DS:[EAX]
FIMUL DWORD PTR DS:[EAX]
FICOM DWORD PTR DS:[EAX]
FICOMP DWORD PTR DS:[EAX]
FISUB DWORD PTR DS:[EAX]
FISUBR DWORD PTR DS:[EAX]
FIDIV DWORD PTR DS:[EAX]
FIDIVR DWORD PTR DS:[EAX]
FILD DWORD PTR DS:[EAX]
FISTTP DWORD PTR DS:[EAX]
FIST DWORD PTR DS:[EAX]
FISTP DWORD PTR DS:[EAX]
FLD TBYTE PTR DS:[EAX]
FSTP TBYTE PTR DS:[EAX]
FADD QWORD PTR DS:[EAX]
FMUL QWORD PTR DS:[EAX]
FCOM QWORD PTR DS:[EAX]
FCOMP QWORD PTR DS:[EAX]
FSUB QWORD PTR DS:[EAX]
FSUBR QWORD PTR DS:[EAX]
FDIV QWORD PTR DS:[EAX]
FDIVR QWORD PTR DS:[EAX]
FLD QWORD PTR DS:[EAX]
FST QWORD PTR DS:[EAX]
FSTP QWORD PTR DS:[EAX]
FISTTP QWORD PTR DS:[EAX]
FRSTOR 108BYTE PTR DS:[EAX]
FSAVE 108BYTE PTR DS:[EAX]
FSAVE 94BYTE PTR DS:[EAX]
FSTSW WORD PTR DS:[EAX]
FIADD WORD PTR DS:[EAX]
FICOM WORD PTR DS:[EAX]
FICOMP WORD PTR DS:[EAX]
FISUB WORD PTR DS:[EAX]
FISUBR WORD PTR DS:[EAX]
FIMUL WORD PTR DS:[EAX]
FIDIV WORD PTR DS:[EAX]
FIDIVR WORD PTR DS:[EAX]
FILD WORD PTR DS:[EAX]
FISTTP WORD PTR DS:[EAX]
FIST WORD PTR DS:[EAX]
FISTP WORD PTR DS:[EAX]
FBLD TBYTE PTR DS:[EAX]
FILD QWORD PTR DS:[EAX]
FBSTP TBYTE PTR DS:[EAX]
FISTP QWORD PTR DS:[EAX]
FCOMIP ST,ST
FCOMIP ST,ST(1)
FCOMIP ST,ST(2)
FCOMIP ST,ST(3)
FCOMIP ST,ST(4)
FCOMIP ST,ST(5)
FCOMIP ST,ST(6)
FCOMIP ST,ST(7)
)"
	},{
R"(
D9C0
D9C1
D9C2
D9C3
D9C4
D9C5
D9C6
D9C7

D9D0

D9E0

D9E1

D9E4

D9E5

D9F0

D9F1

D8C0
D8C1
D8C2
D8C3
D8C4
D8C5
D8C6
D8C7

D8D0
D8D1
D8D2
D8D3
D8D4
D8D5
D8D6
D8D7

D8E0
D8E1
D8E2
D8E3
D8E4
D8E5
D8E6
D8E7

D8F0
D8F1
D8F2
D8F3
D8F4
D8F5
D8F6
D8F7

D8C8
D8C9
D8CA
D8CB
D8CC
D8CD
D8CE
D8CF

D8D8
D8D9
D8DA
D8DB
D8DC
D8DD
D8DE
D8DF

D8E8
D8E9
D8EA
D8EB
D8EC
D8ED
D8EE
D8EF

D8F8
D8F9
D8FA
D8FB
D8FC
D8FD
D8FE
D8FF

D9C8
D9C9
D9CA
D9CB
D9CC
D9CD
D9CE
D9CF

DAC0
DAC1
DAC2
DAC3
DAC4
DAC5
DAC6
DAC7

DAD0
DAD1
DAD2
DAD3
DAD4
DAD5
DAD6
DAD7

DAC8
DAC9
DACA
DACB
DACC
DACD
DACE
DACF

DAD8
DAD9
DADA
DADB
DADC
DADD
DADE
DADF

DAE9

DDE0
DDE1
DDE2
DDE3
DDE4
DDE5
DDE6
DDE7

DBC0
DBC1
DBC2
DBC3
DBC4
DBC5
DBC6
DBC7
)",
R"(FLD ST
FLD ST(1)
FLD ST(2)
FLD ST(3)
FLD ST(4)
FLD ST(5)
FLD ST(6)
FLD ST(7)
FNOP
FCHS
FABS
FTST
FXAM
F2XM1
FYL2X
FADD ST,ST
FADD ST,ST(1)
FADD ST,ST(2)
FADD ST,ST(3)
FADD ST,ST(4)
FADD ST,ST(5)
FADD ST,ST(6)
FADD ST,ST(7)
FCOM ST
FCOM ST(1)
FCOM ST(2)
FCOM ST(3)
FCOM ST(4)
FCOM ST(5)
FCOM ST(6)
FCOM ST(7)
FSUB ST,ST
FSUB ST,ST(1)
FSUB ST,ST(2)
FSUB ST,ST(3)
FSUB ST,ST(4)
FSUB ST,ST(5)
FSUB ST,ST(6)
FSUB ST,ST(7)
FDIV ST,ST
FDIV ST,ST(1)
FDIV ST,ST(2)
FDIV ST,ST(3)
FDIV ST,ST(4)
FDIV ST,ST(5)
FDIV ST,ST(6)
FDIV ST,ST(7)
FMUL ST,ST
FMUL ST,ST(1)
FMUL ST,ST(2)
FMUL ST,ST(3)
FMUL ST,ST(4)
FMUL ST,ST(5)
FMUL ST,ST(6)
FMUL ST,ST(7)
FCOMP ST
FCOMP ST(1)
FCOMP ST(2)
FCOMP ST(3)
FCOMP ST(4)
FCOMP ST(5)
FCOMP ST(6)
FCOMP ST(7)
FSUBR ST,ST
FSUBR ST,ST(1)
FSUBR ST,ST(2)
FSUBR ST,ST(3)
FSUBR ST,ST(4)
FSUBR ST,ST(5)
FSUBR ST,ST(6)
FSUBR ST,ST(7)
FDIVR ST,ST
FDIVR ST,ST(1)
FDIVR ST,ST(2)
FDIVR ST,ST(3)
FDIVR ST,ST(4)
FDIVR ST,ST(5)
FDIVR ST,ST(6)
FDIVR ST,ST(7)
FXCH ST
FXCH ST(1)
FXCH ST(2)
FXCH ST(3)
FXCH ST(4)
FXCH ST(5)
FXCH ST(6)
FXCH ST(7)
FCMOVB ST,ST
FCMOVB ST,ST(1)
FCMOVB ST,ST(2)
FCMOVB ST,ST(3)
FCMOVB ST,ST(4)
FCMOVB ST,ST(5)
FCMOVB ST,ST(6)
FCMOVB ST,ST(7)
FCMOVBE ST,ST
FCMOVBE ST,ST(1)
FCMOVBE ST,ST(2)
FCMOVBE ST,ST(3)
FCMOVBE ST,ST(4)
FCMOVBE ST,ST(5)
FCMOVBE ST,ST(6)
FCMOVBE ST,ST(7)
FCMOVE ST,ST
FCMOVE ST,ST(1)
FCMOVE ST,ST(2)
FCMOVE ST,ST(3)
FCMOVE ST,ST(4)
FCMOVE ST,ST(5)
FCMOVE ST,ST(6)
FCMOVE ST,ST(7)
FCMOVU ST,ST
FCMOVU ST,ST(1)
FCMOVU ST,ST(2)
FCMOVU ST,ST(3)
FCMOVU ST,ST(4)
FCMOVU ST,ST(5)
FCMOVU ST,ST(6)
FCMOVU ST,ST(7)
FUCOMPP
FUCOM ST
FUCOM ST(1)
FUCOM ST(2)
FUCOM ST(3)
FUCOM ST(4)
FUCOM ST(5)
FUCOM ST(6)
FUCOM ST(7)
FCMOVNB ST,ST
FCMOVNB ST,ST(1)
FCMOVNB ST,ST(2)
FCMOVNB ST,ST(3)
FCMOVNB ST,ST(4)
FCMOVNB ST,ST(5)
FCMOVNB ST,ST(6)
FCMOVNB ST,ST(7)
)"
	},{

R"(
66:98
98   
99   
9C   
9E   
9F   
AE   
AF   
66:AF
ED    
66:ED 
EE   
EF   
66:EF
F8
F9
FA
FB
FC
FD
FF10
FF18
FF20
FF28
FF08
FF30

0F0000   
0F00C0   
66:0F00C0
66:0F0000

0F0008   
0F00C8   
66:0F00C8

0F00D0

0F0018
0F00D8

0F00E0
0F00E8

0F0100
0F0108


0F0110
0F0118

0F0120   
66:0F01E0
0F01E0   

0F01F0
0F0130

0F0138

0FBA20 0D
0FBA28 0F
0FBA30 00
0FBA38 04

0F20E0
0F21F8
0F22D0
0F23C8

0F30
0F32

0F31

0F33

0F34
0F35

0F37

0F404D 05      
0F41C8         
0F4290 90FF9549
0F4300         
0F4451 05      
0F458D 4577FFE0
0F4672 74      
0F476C41 6C    

0F08
0F09

66:90               
0F1F00              
0F1F40 00           
0F1F4400 00         
66:0F1F4400 00      
0F1F80 00000000     
0F1F8400 00000000   
66:0F1F8400 00000000

0F0B

0F1800
0F1808
0F1810
0F1818

0FA2

0F48740A EB    
0F49E9         
0F4A43 49      
0F4B8B 06EB0080
0F4C75 F3      
0F4DC1         
0F4E2B         
0F4F06         

0F7835 0500008B
0F790400

0F90C0
0F91C0
0F92C0
0F93C0
0F94C0
0F95C0
0F96C0
0F97C0
0F98C0
0F99C0
0F9AC0
0F9BC0
0F9CC0
0F9DC0
0F9EC0
0F9FC0

0FA0
0FA1
0FA2

0FA3C1         
0FB3C1         
0FAB50 6A      
0FBB95 4D050000

0FA400 04
0FA500   

0FAC00 04
0FAD00   

0FB10B
0FB009

0FB290 90000F85
0FB400       
0FB585 2E040000

0FB6CA
0FB700

0FC049 0F
0FC118  

0FC70D 00204000 

0FA8
0FA9

0FAA

0FAB45 65

0FAFD8

0FC8
0FC9
0FCA
0FCB
0FCC
0FCD
0FCE
0FCF

0FBEFF         
0FBF05 00008985

0FBCC3

0FBDC3
)"
,
R"(CBW
CWDE
CDQ
PUSHFD
SAHF
LAHF
SCAS AL,BYTE PTR ES:[EDI]
SCAS EAX,DWORD PTR ES:[EDI]
SCAS AX,WORD PTR ES:[EDI]
IN EAX,DX
IN AX,DX
OUT DX,AL
OUT DX,EAX
OUT DX,AX
CLC
STC
CLI
STI
CLD
STD
CALL DWORD PTR DS:[EAX]
CALL FAR FWORD PTR DS:[EAX]
JMP DWORD PTR DS:[EAX]
JMP FAR FWORD PTR DS:[EAX]
DEC DWORD PTR DS:[EAX]
PUSH DWORD PTR DS:[EAX]
SLDT WORD PTR DS:[EAX]
SLDT EAX
SLDT AX
SLDT WORD PTR DS:[EAX]
STR WORD PTR DS:[EAX]
STR EAX
STR AX
LLDT AX
LTR WORD PTR DS:[EAX]
LTR AX
VERR AX
VERW AX
SGDT FWORD PTR DS:[EAX]
SIDT FWORD PTR DS:[EAX]
LGDT FWORD PTR DS:[EAX]
LIDT FWORD PTR DS:[EAX]
SMSW WORD PTR DS:[EAX]
SMSW AX
SMSW EAX
LMSW AX
LMSW WORD PTR DS:[EAX]
INVLPG BYTE PTR DS:[EAX]
BT DWORD PTR DS:[EAX],0D
BTS DWORD PTR DS:[EAX],0F
BTR DWORD PTR DS:[EAX],0
BTC DWORD PTR DS:[EAX],4
MOV EAX,CR4
MOV EAX,DR7
MOV CR2,EAX
MOV DR1,EAX
WRMSR
RDMSR
RDTSC
RDPMC
SYSENTER
SYSEXIT
GETSEC
CMOVO ECX,DWORD PTR SS:[EBP+5]
CMOVNO ECX,EAX
CMOVB EDX,DWORD PTR DS:[EAX+4995FF90]
CMOVAE EAX,DWORD PTR DS:[EAX]
CMOVE EDX,DWORD PTR DS:[ECX+5]
CMOVNE ECX,DWORD PTR SS:[EBP+E0FF7745]
CMOVBE ESI,DWORD PTR DS:[EDX+74]
CMOVA EBP,DWORD PTR DS:[ECX+EAX*2+6C]
INVD
WBINVD
NOP
NOP DWORD PTR DS:[EAX]
NOP DWORD PTR DS:[EAX]
NOP DWORD PTR DS:[EAX+EAX]
NOP WORD PTR DS:[EAX+EAX]
NOP DWORD PTR DS:[EAX]
NOP DWORD PTR DS:[EAX+EAX]
NOP WORD PTR DS:[EAX+EAX]
UD2
PREFETCHNTA BYTE PTR DS:[EAX]
PREFETCHT0 BYTE PTR DS:[EAX]
PREFETCHT1 BYTE PTR DS:[EAX]
PREFETCHT2 BYTE PTR DS:[EAX]
CPUID
CMOVS ESI,DWORD PTR DS:[EDX+ECX-15]
CMOVNS EBP,ECX
CMOVPE EAX,DWORD PTR DS:[EBX+49]
CMOVPO ECX,DWORD PTR DS:[EBX+8000EB06]
CMOVL ESI,DWORD PTR SS:[EBP-0D]
CMOVGE EAX,ECX
CMOVLE EBP,DWORD PTR DS:[EBX]
CMOVG EAX,DWORD PTR DS:[ESI]
VMREAD DWORD PTR DS:[8B000005],ESI
VMWRITE EAX,DWORD PTR DS:[EAX+EAX]
SETO AL
SETNO AL
SETB AL
SETAE AL
SETE AL
SETNE AL
SETBE AL
SETA AL
SETS AL
SETNS AL
SETPE AL
SETPO AL
SETL AL
SETGE AL
SETLE AL
SETG AL
PUSH FS
POP FS
CPUID
BT ECX,EAX
BTR ECX,EAX
BTS DWORD PTR DS:[EAX+6A],EDX
BTC DWORD PTR SS:[EBP+54D],EDX
SHLD DWORD PTR DS:[EAX],EAX,4
SHLD DWORD PTR DS:[EAX],EAX,CL
SHRD DWORD PTR DS:[EAX],EAX,4
SHRD DWORD PTR DS:[EAX],EAX,CL
CMPXCHG DWORD PTR DS:[EBX],ECX
CMPXCHG BYTE PTR DS:[ECX],CL
LSS EDX,FWORD PTR DS:[EAX+850F0090]
LFS EAX,FWORD PTR DS:[EAX]
LGS EAX,FWORD PTR SS:[EBP+42E]
MOVZX ECX,DL
MOVZX EAX,WORD PTR DS:[EAX]
XADD BYTE PTR DS:[ECX+0F],CL
XADD DWORD PTR DS:[EAX],EBX
CMPXCHG8B QWORD PTR DS:[402000]
PUSH GS
POP GS
RSM
BTS DWORD PTR SS:[EBP+65],EAX
IMUL EBX,EAX
BSWAP EAX
BSWAP ECX
BSWAP EDX
BSWAP EBX
BSWAP ESP
BSWAP EBP
BSWAP ESI
BSWAP EDI
MOVSX EDI,BH
MOVSX EAX,WORD PTR DS:[85890000]
BSF EAX,EBX
BSR EAX,EBX
)"
	},{

#if 0
55                                   PUSH EBP
8BEC                                 MOV EBP, ESP
6A FE                                PUSH - 2
64:A1 00000000                       MOV EAX, DWORD PTR FS:[0]
50                                   PUSH EAX
83C4 D0                              ADD ESP, -30
53                                   PUSH EBX
56                                   PUSH ESI
57                                   PUSH EDI
3145 F8                              XOR DWORD PTR SS:[EBP - 8], EAX
33C5                                 XOR EAX, EBP
50                                   PUSH EAX
8D45 F0                              LEA EAX, DWORD PTR SS:[EBP - 10]
64:A3 00000000                       MOV DWORD PTR FS:[0], EAX
8965 E8                              MOV DWORD PTR SS:[EBP - 18], ESP
6A 01                                PUSH 1
83C4 04                              ADD ESP, 4
0FB6C0                               MOVZX EAX, AL
85C0                                 TEST EAX, EAX
6A 07                                PUSH 7
C645 E7 00                           MOV BYTE PTR SS:[EBP - 19], 0
C745 FC 00000000                     MOV DWORD PTR SS:[EBP - 4], 0
8845 E6                              MOV BYTE PTR SS:[EBP - 1A], AL
6A 07                                PUSH 7
83C4 08                              ADD ESP, 8
85C0                                 TEST EAX, EAX
C745 C8 FF000000                     MOV DWORD PTR SS:[EBP - 38], 0FF
C745 FC FEFFFFFF                     MOV DWORD PTR SS:[EBP - 4], -2
8B45 C8                              MOV EAX, DWORD PTR SS:[EBP - 38]
83C4 08                              ADD ESP, 8
C645 E7 01                           MOV BYTE PTR SS:[EBP - 19], 1
0FB64D E6                            MOVZX ECX, BYTE PTR SS:[EBP - 1A]
51                                   PUSH ECX
83C4 04                              ADD ESP, 4
8945 E0                              MOV DWORD PTR SS:[EBP - 20], EAX
8B55 E0                              MOV EDX, DWORD PTR SS:[EBP - 20]
833A 00                              CMP DWORD PTR DS:[EDX], 0
8B45 E0                              MOV EAX, DWORD PTR SS:[EBP - 20]
50                                   PUSH EAX
83C4 04                              ADD ESP, 4
0FB6C8                               MOVZX ECX, AL
85C9                                 TEST ECX, ECX
6A 00                                PUSH 0
6A 02                                PUSH 2
6A 00                                PUSH 0
8B55 E0                              MOV EDX, DWORD PTR SS:[EBP - 20]
8B02                                 MOV EAX, DWORD PTR DS:[EDX]
8945 D8                              MOV DWORD PTR SS:[EBP - 28], EAX
8B4D D8                              MOV ECX, DWORD PTR SS:[EBP - 28]
FF55 D8                              CALL DWORD PTR SS:[EBP - 28]
8945 DC                              MOV DWORD PTR SS:[EBP - 24], EAX
8B4D DC                              MOV ECX, DWORD PTR SS:[EBP - 24]
8339 00                              CMP DWORD PTR DS:[ECX], 0
8B55 DC                              MOV EDX, DWORD PTR SS:[EBP - 24]
52                                   PUSH EDX
83C4 04                              ADD ESP, 4
0FB6C0                               MOVZX EAX, AL
85C0                                 TEST EAX, EAX
8B4D DC                              MOV ECX, DWORD PTR SS:[EBP - 24]
8B11                                 MOV EDX, DWORD PTR DS:[ECX]
52                                   PUSH EDX
83C4 04                              ADD ESP, 4
6A 00                                PUSH 0
83C4 04                              ADD ESP, 4
8945 D4                              MOV DWORD PTR SS:[EBP - 2C], EAX
6A 00                                PUSH 0
83C4 04                              ADD ESP, 4
0FB6C0                               MOVZX EAX, AL
85C0                                 TEST EAX, EAX
8B4D D4                              MOV ECX, DWORD PTR SS:[EBP - 2C]
51                                   PUSH ECX
0FB655 E7                            MOVZX EDX, BYTE PTR SS:[EBP - 19]
85D2                                 TEST EDX, EDX
6A 00                                PUSH 0
6A 01                                PUSH 1
83C4 08                              ADD ESP, 8
8B45 D4                              MOV EAX, DWORD PTR SS:[EBP - 2C]
8945 C4                              MOV DWORD PTR SS:[EBP - 3C], EAX
C745 FC FEFFFFFF                     MOV DWORD PTR SS:[EBP - 4], -2
8B45 C4                              MOV EAX, DWORD PTR SS:[EBP - 3C]
C745 FC FEFFFFFF                     MOV DWORD PTR SS:[EBP - 4], -2
8B4D EC                              MOV ECX, DWORD PTR SS:[EBP - 14]
8B11                                 MOV EDX, DWORD PTR DS:[ECX]
8B02                                 MOV EAX, DWORD PTR DS:[EDX]
8945 D0                              MOV DWORD PTR SS:[EBP - 30], EAX
8B4D EC                              MOV ECX, DWORD PTR SS:[EBP - 14]
51                                   PUSH ECX
8B55 D0                              MOV EDX, DWORD PTR SS:[EBP - 30]
52                                   PUSH EDX
83C4 08                              ADD ESP, 8
C3                                   RETN
8B65 E8                              MOV ESP, DWORD PTR SS:[EBP - 18]
8B45 D0                              MOV EAX, DWORD PTR SS:[EBP - 30]
8945 CC                              MOV DWORD PTR SS:[EBP - 34], EAX
0FB6C8                               MOVZX ECX, AL
85C9                                 TEST ECX, ECX
8B55 CC                              MOV EDX, DWORD PTR SS:[EBP - 34]
52                                   PUSH EDX
0FB645 E7                            MOVZX EAX, BYTE PTR SS:[EBP - 19]
85C0                                 TEST EAX, EAX
8B4D CC                              MOV ECX, DWORD PTR SS:[EBP - 34]
894D C0                              MOV DWORD PTR SS:[EBP - 40], ECX
C745 FC FEFFFFFF                     MOV DWORD PTR SS:[EBP - 4], -2
8B45 C0                              MOV EAX, DWORD PTR SS:[EBP - 40]
C745 FC FEFFFFFF                     MOV DWORD PTR SS:[EBP - 4], -2
8B4D F0                              MOV ECX, DWORD PTR SS:[EBP - 10]
64:890D 00000000                     MOV DWORD PTR FS:[0], ECX
59                                   POP ECX
5F                                   POP EDI
5E                                   POP ESI
5B                                   POP EBX
8BE5                                 MOV ESP, EBP
5D                                   POP EBP
C3                                   RETN

#endif

R"(
55                                   
8BEC                                 
6A FE                                
64:A1 00000000                       
50                                   
83C4 D0                              
53                                   
56                                   
57                                   
3145 F8                              
33C5                                 
50                                   
8D45 F0                              
64:A3 00000000                       
8965 E8                              
6A 01                                
83C4 04                              
0FB6C0                               
85C0                                 
6A 07                                
C645 E7 00                           
C745 FC 00000000                     
8845 E6                              
6A 07                                
83C4 08                              
85C0                                 
C745 C8 FF000000                     
C745 FC FEFFFFFF                     
8B45 C8                              
83C4 08                              
C645 E7 01                           
0FB64D E6                            
51                                   
83C4 04                              
8945 E0                              
8B55 E0                              
833A 00                              
8B45 E0                              
50                                   
83C4 04                              
0FB6C8                               
85C9                                 
6A 00                                
6A 02                                
6A 00                                
8B55 E0                              
8B02                                 
8945 D8                              
8B4D D8                              
FF55 D8                              
8945 DC                              
8B4D DC                              
8339 00                              
8B55 DC                              
52                                   
83C4 04                              
0FB6C0                               
85C0                                 
8B4D DC                              
8B11                                 
52                                   
83C4 04                              
6A 00                                
83C4 04                              
8945 D4                              
6A 00                                
83C4 04                              
0FB6C0                               
85C0                                 
8B4D D4                              
51                                   
0FB655 E7                            
85D2                                 
6A 00                                
6A 01                                
83C4 08                              
8B45 D4                              
8945 C4                              
C745 FC FEFFFFFF                     
8B45 C4                              
C745 FC FEFFFFFF                     
8B4D EC                              
8B11                                 
8B02                                 
8945 D0                              
8B4D EC                              
51                                   
8B55 D0                              
52                                   
83C4 08                              
C3                                   
8B65 E8                              
8B45 D0                              
8945 CC                              
0FB6C8                               
85C9                                 
8B55 CC                              
52                                   
0FB645 E7                            
85C0                                 
8B4D CC                              
894D C0                              
C745 FC FEFFFFFF                     
8B45 C0                              
C745 FC FEFFFFFF                     
8B4D F0                              
64:890D 00000000                     
59                                   
5F                                   
5E                                   
5B                                   
8BE5                                 
5D                                   
C3                                   
)"
,
R"(PUSH EBP
MOV EBP,ESP
PUSH -2
MOV EAX,DWORD PTR FS:[0]
PUSH EAX
ADD ESP,-30
PUSH EBX
PUSH ESI
PUSH EDI
XOR DWORD PTR SS:[EBP-8],EAX
XOR EAX,EBP
PUSH EAX
LEA EAX,DWORD PTR SS:[EBP-10]
MOV DWORD PTR FS:[0],EAX
MOV DWORD PTR SS:[EBP-18],ESP
PUSH 1
ADD ESP,4
MOVZX EAX,AL
TEST EAX,EAX
PUSH 7
MOV BYTE PTR SS:[EBP-19],0
MOV DWORD PTR SS:[EBP-4],0
MOV BYTE PTR SS:[EBP-1A],AL
PUSH 7
ADD ESP,8
TEST EAX,EAX
MOV DWORD PTR SS:[EBP-38],0FF
MOV DWORD PTR SS:[EBP-4],-2
MOV EAX,DWORD PTR SS:[EBP-38]
ADD ESP,8
MOV BYTE PTR SS:[EBP-19],1
MOVZX ECX,BYTE PTR SS:[EBP-1A]
PUSH ECX
ADD ESP,4
MOV DWORD PTR SS:[EBP-20],EAX
MOV EDX,DWORD PTR SS:[EBP-20]
CMP DWORD PTR DS:[EDX],0
MOV EAX,DWORD PTR SS:[EBP-20]
PUSH EAX
ADD ESP,4
MOVZX ECX,AL
TEST ECX,ECX
PUSH 0
PUSH 2
PUSH 0
MOV EDX,DWORD PTR SS:[EBP-20]
MOV EAX,DWORD PTR DS:[EDX]
MOV DWORD PTR SS:[EBP-28],EAX
MOV ECX,DWORD PTR SS:[EBP-28]
CALL DWORD PTR SS:[EBP-28]
MOV DWORD PTR SS:[EBP-24],EAX
MOV ECX,DWORD PTR SS:[EBP-24]
CMP DWORD PTR DS:[ECX],0
MOV EDX,DWORD PTR SS:[EBP-24]
PUSH EDX
ADD ESP,4
MOVZX EAX,AL
TEST EAX,EAX
MOV ECX,DWORD PTR SS:[EBP-24]
MOV EDX,DWORD PTR DS:[ECX]
PUSH EDX
ADD ESP,4
PUSH 0
ADD ESP,4
MOV DWORD PTR SS:[EBP-2C],EAX
PUSH 0
ADD ESP,4
MOVZX EAX,AL
TEST EAX,EAX
MOV ECX,DWORD PTR SS:[EBP-2C]
PUSH ECX
MOVZX EDX,BYTE PTR SS:[EBP-19]
TEST EDX,EDX
PUSH 0
PUSH 1
ADD ESP,8
MOV EAX,DWORD PTR SS:[EBP-2C]
MOV DWORD PTR SS:[EBP-3C],EAX
MOV DWORD PTR SS:[EBP-4],-2
MOV EAX,DWORD PTR SS:[EBP-3C]
MOV DWORD PTR SS:[EBP-4],-2
MOV ECX,DWORD PTR SS:[EBP-14]
MOV EDX,DWORD PTR DS:[ECX]
MOV EAX,DWORD PTR DS:[EDX]
MOV DWORD PTR SS:[EBP-30],EAX
MOV ECX,DWORD PTR SS:[EBP-14]
PUSH ECX
MOV EDX,DWORD PTR SS:[EBP-30]
PUSH EDX
ADD ESP,8
RETN
MOV ESP,DWORD PTR SS:[EBP-18]
MOV EAX,DWORD PTR SS:[EBP-30]
MOV DWORD PTR SS:[EBP-34],EAX
MOVZX ECX,AL
TEST ECX,ECX
MOV EDX,DWORD PTR SS:[EBP-34]
PUSH EDX
MOVZX EAX,BYTE PTR SS:[EBP-19]
TEST EAX,EAX
MOV ECX,DWORD PTR SS:[EBP-34]
MOV DWORD PTR SS:[EBP-40],ECX
MOV DWORD PTR SS:[EBP-4],-2
MOV EAX,DWORD PTR SS:[EBP-40]
MOV DWORD PTR SS:[EBP-4],-2
MOV ECX,DWORD PTR SS:[EBP-10]
MOV DWORD PTR FS:[0],ECX
POP ECX
POP EDI
POP ESI
POP EBX
MOV ESP,EBP
POP EBP
RETN
)"
	}, {
// mem
R"(
8B7E 0F      
8BBE FF000000
8BBE FF0F0000
8BBE FFFF0000
8BBE FFFFFF00
8BBE FFFFFF0F
8B7E FF      
)"
,
R"(MOV EDI,DWORD PTR DS:[ESI+0F]
MOV EDI,DWORD PTR DS:[ESI+0FF]
MOV EDI,DWORD PTR DS:[ESI+0FFF]
MOV EDI,DWORD PTR DS:[ESI+0FFFF]
MOV EDI,DWORD PTR DS:[ESI+0FFFFFF]
MOV EDI,DWORD PTR DS:[ESI+0FFFFFFF]
MOV EDI,DWORD PTR DS:[ESI-1]
)"
	}, {

#if 0
013D16C0 > 55                    PUSH EBP
013D16C1   8BEC                  MOV EBP, ESP
013D16C3   81EC C0000000         SUB ESP, 0C0
013D16C9   53                    PUSH EBX
013D16CA   56                    PUSH ESI
013D16CB   57                    PUSH EDI
013D16CC   8DBD 40FFFFFF         LEA EDI, DWORD PTR SS:[EBP - C0]
013D16D2   B9 30000000           MOV ECX, 30
013D16D7   B8 CCCCCCCC           MOV EAX, CCCCCCCC
013D16DE   6A 04                 PUSH 4
013D16E0   6A 03                 PUSH 3
013D16E2   6A 02                 PUSH 2
013D16E4   6A 01                 PUSH 1
013D16EB   83C4 10               ADD ESP, 10
013D16EE   33C0                  XOR EAX, EAX
013D16F0   5F                    POP EDI
013D16F1   5E                    POP ESI
013D16F2   5B                    POP EBX
013D16F3   81C4 C0000000         ADD ESP, 0C0
013D16F9   3BEC                  CMP EBP, ESP
013D1700   8BE5                  MOV ESP, EBP
013D1702   5D                    POP EBP
013D1703   C3                    RETN

#endif

R"(
55              
8BEC            
81EC C0000000   
53              
56              
57              
8DBD 40FFFFFF   
B9 30000000     
B8 CCCCCCCC     
6A 04           
6A 03           
6A 02           
6A 01           
83C4 10         
33C0            
5F              
5E              
5B              
81C4 C0000000   
3BEC            
8BE5            
5D              
C3              
)"
,
R"(PUSH EBP
MOV EBP,ESP
SUB ESP,0C0
PUSH EBX
PUSH ESI
PUSH EDI
LEA EDI,DWORD PTR SS:[EBP-0C0]
MOV ECX,30
MOV EAX,CCCCCCCC
PUSH 4
PUSH 3
PUSH 2
PUSH 1
ADD ESP,10
XOR EAX,EAX
POP EDI
POP ESI
POP EBX
ADD ESP,0C0
CMP EBP,ESP
MOV ESP,EBP
POP EBP
RETN
)"
	}, {

//77B901EC   E9 A9900200      JMP ntdll.77BB929A
#if 0
77B901E8   895C24 08        MOV DWORD PTR SS:[ESP + 8], EBX
77B901F1   8DA424 00000000  LEA ESP, DWORD PTR SS:[ESP]
77B901F8   8DA424 00000000  LEA ESP, DWORD PTR SS:[ESP]
77B901FF   90               NOP
77B90200 > 8BD4             MOV EDX, ESP
77B90202   0F34             SYSENTER
77B90204 > C3               RETN
77B90205   8DA424 00000000  LEA ESP, DWORD PTR SS:[ESP]
77B9020C   8D6424 00        LEA ESP, DWORD PTR SS:[ESP]
77B90210 > 8D5424 08        LEA EDX, DWORD PTR SS:[ESP + 8]
77B90214   CD 2E            INT 2E
77B90216   C3               RETN
77B90217   90               NOP
77B90218   0000             ADD BYTE PTR DS:[EAX], AL
77B9021A   0000             ADD BYTE PTR DS:[EAX], AL
77B9021C   AD               LODS DWORD PTR DS:[ESI]
77B9021D   52               PUSH EDX
#endif
R"(
895C24 08        
8DA424 00000000  
8DA424 00000000  
90               
8BD4             
0F34             
C3               
8DA424 00000000  
8D6424 00        
8D5424 08        
CD 2E            
C3               
90               
0000             
0000             
AD               
52               
)"
,
R"(MOV DWORD PTR SS:[ESP+8],EBX
LEA ESP,DWORD PTR SS:[ESP]
LEA ESP,DWORD PTR SS:[ESP]
NOP
MOV EDX,ESP
SYSENTER
RETN
LEA ESP,DWORD PTR SS:[ESP]
LEA ESP,DWORD PTR SS:[ESP]
LEA EDX,DWORD PTR SS:[ESP+8]
INT 2E
RETN
NOP
ADD BYTE PTR DS:[EAX],AL
ADD BYTE PTR DS:[EAX],AL
LODS EAX,DWORD PTR DS:[ESI]
PUSH EDX
)"
	}, {


#if 0
77BB92C7   8365 FC 00       AND DWORD PTR SS:[EBP - 4], 0
77BADF29   64:FF35 00000000 PUSH DWORD PTR FS:[0]
77BADF30   8B4424 10        MOV EAX, DWORD PTR SS:[ESP + 10]
77BADF34   896C24 10        MOV DWORD PTR SS:[ESP + 10], EBP
77BADF38   8D6C24 10        LEA EBP, DWORD PTR SS:[ESP + 10]
77BADF3C   2BE0             SUB ESP, EAX
77BADF3E   53               PUSH EBX
77BADF3F   56               PUSH ESI
77BADF40   57               PUSH EDI
77BADF41   A1 8820C877      MOV EAX, DWORD PTR DS:[77C82088]
77BADF46   3145 FC          XOR DWORD PTR SS:[EBP - 4], EAX
77BADF49   33C5             XOR EAX, EBP
77BADF4B   50               PUSH EAX
77BADF4C   8965 E8          MOV DWORD PTR SS:[EBP - 18], ESP
77BADF4F   FF75 F8          PUSH DWORD PTR SS:[EBP - 8]
77BADF52   8B45 FC          MOV EAX, DWORD PTR SS:[EBP - 4]
77BADF55   C745 FC FEFFFFFF MOV DWORD PTR SS:[EBP - 4], -2
77BADF5C   8945 F8          MOV DWORD PTR SS:[EBP - 8], EAX
77BADF5F   8D45 F0          LEA EAX, DWORD PTR SS:[EBP - 10]
77BADF62   64:A3 00000000   MOV DWORD PTR FS:[0], EAX
77BADF68   C3               RETN

012C1270 > 55                                      PUSH EBP
012C1271   8BEC                                    MOV EBP, ESP
012C1273   6A FE                                   PUSH - 2
012C1275   68 08D82D01                             PUSH demo.012DD808
012C127A   68 F0252C01                             PUSH OFFSET demo._except_handler4
012C127F   64:A1 00000000                          MOV EAX, DWORD PTR FS:[0]
012C1285   50                                      PUSH EAX
012C1286   83C4 D0                                 ADD ESP, -30
012C1289   53                                      PUSH EBX
012C128A   56                                      PUSH ESI
012C128B   57                                      PUSH EDI
012C128C   A1 DCF02D01                             MOV EAX, DWORD PTR DS:[__security_cookie]
012C1291   3145 F8                                 XOR DWORD PTR SS:[EBP - 8], EAX
012C1294   33C5                                    XOR EAX, EBP
012C1296   50                                      PUSH EAX
012C1297   8D45 F0                                 LEA EAX, DWORD PTR SS:[EBP - 10]
012C129A   64:A3 00000000                          MOV DWORD PTR FS:[0], EAX
012C12A0   8965 E8                                 MOV DWORD PTR SS:[EBP - 18], ESP
012C12A3   6A 01                                   PUSH 1
012C12A5   E8 66DFF8FF                             CALL demo.0124F210
012C12AA   83C4 04                                 ADD ESP, 4
012C12AD   0FB6C0                                  MOVZX EAX, AL
012C12B0   85C0                                    TEST EAX, EAX
012C12B2   75 07                                   JNZ SHORT demo.012C12BB
012C12B4   6A 07                                   PUSH 7
012C12B6   E8 F2C4F8FF                             CALL demo.0124D7AD
012C12BB   C645 E7 00                              MOV BYTE PTR SS:[EBP - 19], 0
012C12BF   C745 FC 00000000                        MOV DWORD PTR SS:[EBP - 4], 0
012C12C6   E8 98E6F8FF                             CALL demo.0124F963
012C12CB   8845 E6                                 MOV BYTE PTR SS:[EBP - 1A], AL
012C12CE   833D 64F62D01 01                        CMP DWORD PTR DS:[__scrt_current_native_startup_state], 1
012C12D5   75 09                                   JNZ SHORT demo.012C12E0
012C12D7   6A 07                                   PUSH 7
012C12D9   E8 CFC4F8FF                             CALL demo.0124D7AD
012C12DE   EB 61                                   JMP SHORT demo.012C1341
012C12E0   833D 64F62D01 00                        CMP DWORD PTR DS:[__scrt_current_native_startup_state], 0
012C12E7   75 54                                   JNZ SHORT demo.012C133D
012C12E9   C705 64F62D01 01000000                  MOV DWORD PTR DS:[__scrt_current_native_startup_state], 1
012C12F3   68 30F92C01                             PUSH OFFSET demo.__xi_z
012C12F8   68 20F52C01                             PUSH OFFSET demo.__xi_a
012C12FD   E8 CCC6F8FF                             CALL demo.0124D9CE
012C1302   83C4 08                                 ADD ESP, 8
012C1305   85C0                                    TEST EAX, EAX
012C1307   74 16                                   JE SHORT demo.012C131F
012C1309   C745 C8 FF000000                        MOV DWORD PTR SS:[EBP - 38], 0FF
012C1310   C745 FC FEFFFFFF                        MOV DWORD PTR SS:[EBP - 4], -2
012C1317   8B45 C8                                 MOV EAX, DWORD PTR SS:[EBP - 38]
012C131A   E9 60010000                             JMP demo.012C147F
012C131F   68 1CF42C01                             PUSH OFFSET demo.__xc_z
012C1324   68 00F02C01                             PUSH OFFSET demo.__xc_a
012C1329   E8 2AE2F8FF                             CALL demo.0124F558
012C132E   83C4 08                                 ADD ESP, 8
012C1331   C705 64F62D01 02000000                  MOV DWORD PTR DS:[__scrt_current_native_startup_state], 2
012C133B   EB 04                                   JMP SHORT demo.012C1341
012C133D   C645 E7 01                              MOV BYTE PTR SS:[EBP - 19], 1
012C1341   0FB64D E6                               MOVZX ECX, BYTE PTR SS:[EBP - 1A]
012C1345   51                                      PUSH ECX
012C1346   E8 46E5F8FF                             CALL demo.0124F891
012C134B   83C4 04                                 ADD ESP, 4
012C134E   E8 04DEF8FF                             CALL demo.0124F157
012C1353   8945 E0                                 MOV DWORD PTR SS:[EBP - 20], EAX
012C1356   8B55 E0                                 MOV EDX, DWORD PTR SS:[EBP - 20]
012C1359   833A 00                                 CMP DWORD PTR DS:[EDX], 0
012C135C   74 2C                                   JE SHORT demo.012C138A
012C135E   8B45 E0                                 MOV EAX, DWORD PTR SS:[EBP - 20]
012C1361   50                                      PUSH EAX
012C1362   E8 1CE9F8FF                             CALL demo.0124FC83
012C1367   83C4 04                                 ADD ESP, 4
012C136A   0FB6C8                                  MOVZX ECX, AL
012C136D   85C9                                    TEST ECX, ECX
012C136F   74 19                                   JE SHORT demo.012C138A
012C1371   6A 00                                   PUSH 0
012C1373   6A 02                                   PUSH 2
012C1375   6A 00                                   PUSH 0
012C1377   8B55 E0                                 MOV EDX, DWORD PTR SS:[EBP - 20]
012C137A   8B02                                    MOV EAX, DWORD PTR DS:[EDX]
012C137C   8945 D8                                 MOV DWORD PTR SS:[EBP - 28], EAX
012C137F   8B4D D8                                 MOV ECX, DWORD PTR SS:[EBP - 28]
012C1382   E8 63E1F8FF                             CALL demo.0124F4EA
012C1387   FF55 D8                                 CALL DWORD PTR SS:[EBP - 28]
012C138A   E8 FFC9F8FF                             CALL demo.0124DD8E
012C138F   8945 DC                                 MOV DWORD PTR SS:[EBP - 24], EAX
012C1392   8B4D DC                                 MOV ECX, DWORD PTR SS:[EBP - 24]
012C1395   8339 00                                 CMP DWORD PTR DS:[ECX], 0
012C1398   74 21                                   JE SHORT demo.012C13BB
012C139A   8B55 DC                                 MOV EDX, DWORD PTR SS:[EBP - 24]
012C139D   52                                      PUSH EDX
012C139E   E8 E0E8F8FF                             CALL demo.0124FC83
012C13A3   83C4 04                                 ADD ESP, 4
012C13A6   0FB6C0                                  MOVZX EAX, AL
012C13A9   85C0                                    TEST EAX, EAX
012C13AB   74 0E                                   JE SHORT demo.012C13BB
012C13AD   8B4D DC                                 MOV ECX, DWORD PTR SS:[EBP - 24]
012C13B0   8B11                                    MOV EDX, DWORD PTR DS:[ECX]
012C13B2   52                                      PUSH EDX
012C13B3   E8 98D5F8FF                             CALL demo.0124E950
012C13B8   83C4 04                                 ADD ESP, 4
012C13BB   6A 00                                   PUSH 0
012C13BD   E8 D5CFF8FF                             CALL demo.0124E397
012C13C2   83C4 04                                 ADD ESP, 4
012C13C5   E8 96010000                             CALL demo.invoke_main
012C13CA   8945 D4                                 MOV DWORD PTR SS:[EBP - 2C], EAX
012C13CD   6A 00                                   PUSH 0
012C13CF   E8 83C4F8FF                             CALL demo.0124D857
012C13D4   83C4 04                                 ADD ESP, 4
012C13D7   E8 DACEF8FF                             CALL demo.0124E2B6
012C13DC   0FB6C0                                  MOVZX EAX, AL
012C13DF   85C0                                    TEST EAX, EAX
012C13E1   75 09                                   JNZ SHORT demo.012C13EC
012C13E3   8B4D D4                                 MOV ECX, DWORD PTR SS:[EBP - 2C]
012C13E6   51                                      PUSH ECX
012C13E7   E8 3FE1F8FF                             CALL demo.0124F52B
012C13EC   0FB655 E7                               MOVZX EDX, BYTE PTR SS:[EBP - 19]
012C13F0   85D2                                    TEST EDX, EDX
012C13F2   75 05                                   JNZ SHORT demo.012C13F9
012C13F4   E8 F1C7F8FF                             CALL demo.0124DBEA
012C13F9   6A 00                                   PUSH 0
012C13FB   6A 01                                   PUSH 1
012C13FD   E8 06D2F8FF                             CALL demo.0124E608
012C1402   83C4 08                                 ADD ESP, 8
012C1405   8B45 D4                                 MOV EAX, DWORD PTR SS:[EBP - 2C]
012C1408   8945 C4                                 MOV DWORD PTR SS:[EBP - 3C], EAX
012C140B   C745 FC FEFFFFFF                        MOV DWORD PTR SS:[EBP - 4], -2
012C1412   8B45 C4                                 MOV EAX, DWORD PTR SS:[EBP - 3C]
012C1415   EB 68                                   JMP SHORT demo.012C147F
012C1417   C745 FC FEFFFFFF                        MOV DWORD PTR SS:[EBP - 4], -2
012C141E   EB 5F                                   JMP SHORT demo.012C147F
012C1420   8B4D EC                                 MOV ECX, DWORD PTR SS:[EBP - 14]
012C1423   8B11                                    MOV EDX, DWORD PTR DS:[ECX]
012C1425   8B02                                    MOV EAX, DWORD PTR DS:[EDX]
012C1427   8945 D0                                 MOV DWORD PTR SS:[EBP - 30], EAX
012C142A   8B4D EC                                 MOV ECX, DWORD PTR SS:[EBP - 14]
012C142D   51                                      PUSH ECX
012C142E   8B55 D0                                 MOV EDX, DWORD PTR SS:[EBP - 30]
012C1431   52                                      PUSH EDX
012C1432   E8 8BDBF8FF                             CALL demo.0124EFC2
012C1437   83C4 08                                 ADD ESP, 8
012C143A   C3                                      RETN
012C143B   8B65 E8                                 MOV ESP, DWORD PTR SS:[EBP - 18]
012C143E   8B45 D0                                 MOV EAX, DWORD PTR SS:[EBP - 30]
012C1441   8945 CC                                 MOV DWORD PTR SS:[EBP - 34], EAX
012C1444   E8 6DCEF8FF                             CALL demo.0124E2B6
012C1449   0FB6C8                                  MOVZX ECX, AL
012C144C   85C9                                    TEST ECX, ECX
012C144E   75 09                                   JNZ SHORT demo.012C1459
012C1450   8B55 CC                                 MOV EDX, DWORD PTR SS:[EBP - 34]
012C1453   52                                      PUSH EDX
012C1454   E8 4CD5F8FF                             CALL demo.0124E9A5
012C1459   0FB645 E7                               MOVZX EAX, BYTE PTR SS:[EBP - 19]
012C145D   85C0                                    TEST EAX, EAX
012C145F   75 05                                   JNZ SHORT demo.012C1466
012C1461   E8 A6E6F8FF                             CALL demo.0124FB0C
012C1466   8B4D CC                                 MOV ECX, DWORD PTR SS:[EBP - 34]
012C1469   894D C0                                 MOV DWORD PTR SS:[EBP - 40], ECX
012C146C   C745 FC FEFFFFFF                        MOV DWORD PTR SS:[EBP - 4], -2
012C1473   8B45 C0                                 MOV EAX, DWORD PTR SS:[EBP - 40]
012C1476   EB 07                                   JMP SHORT demo.012C147F
012C1478   C745 FC FEFFFFFF                        MOV DWORD PTR SS:[EBP - 4], -2
012C147F   8B4D F0                                 MOV ECX, DWORD PTR SS:[EBP - 10]
012C1482   64:890D 00000000                        MOV DWORD PTR FS:[0], ECX
012C1489   59                                      POP ECX
012C148A   5F                                      POP EDI
012C148B   5E                                      POP ESI
012C148C   5B                                      POP EBX
012C148D   8BE5                                    MOV ESP, EBP
012C148F   5D                                      POP EBP
012C1490   C3                                      RETN

#endif
R"(
55                              
8BEC                            
6A FE                           
68 08D82D01                     
68 F0252C01                     
64:A1 00000000                  
50                              
83C4 D0                         
53                              
56                              
57                              
A1 DCF02D01                     
3145 F8                         
33C5                            
50                              
8D45 F0                         
64:A3 00000000                  
8965 E8                         
6A 01                           
E8 66DFF8FF                     
83C4 04                         
0FB6C0                          
85C0                            
75 07                           
6A 07                           
E8 F2C4F8FF                     
C645 E7 00                      
C745 FC 00000000                
E8 98E6F8FF                     
8845 E6                         
833D 64F62D01 01                
75 09                           
6A 07                           
E8 CFC4F8FF                     
EB 61                           
833D 64F62D01 00                
75 54                           
C705 64F62D01 01000000          
68 30F92C01                     
68 20F52C01                     
E8 CCC6F8FF                     
83C4 08                         
85C0                            
74 16                           
C745 C8 FF000000                
C745 FC FEFFFFFF                
8B45 C8                         
E9 60010000                     
68 1CF42C01                     
68 00F02C01                     
E8 2AE2F8FF                     
83C4 08                         
C705 64F62D01 02000000          
EB 04                           
C645 E7 01                      
0FB64D E6                       
51                              
E8 46E5F8FF                     
83C4 04                         
E8 04DEF8FF                     
8945 E0                         
8B55 E0                         
833A 00                         
74 2C                           
8B45 E0                         
50                              
E8 1CE9F8FF                     
83C4 04                         
0FB6C8                          
85C9                            
74 19                           
6A 00                           
6A 02                           
6A 00                           
8B55 E0                         
8B02                            
8945 D8                         
8B4D D8                         
E8 63E1F8FF                     
FF55 D8                         
E8 FFC9F8FF                     
8945 DC                         
8B4D DC                         
8339 00                         
74 21                           
8B55 DC                         
52                              
E8 E0E8F8FF                     
83C4 04                         
0FB6C0                          
85C0                            
74 0E                           
8B4D DC                         
8B11                            
52                              
E8 98D5F8FF                     
83C4 04                         
6A 00                           
E8 D5CFF8FF                     
83C4 04                         
E8 96010000                     
8945 D4                         
6A 00                           
E8 83C4F8FF                     
83C4 04                         
E8 DACEF8FF                     
0FB6C0                          
85C0                            
75 09                           
8B4D D4                         
51                              
E8 3FE1F8FF                     
0FB655 E7                       
85D2                            
75 05                           
E8 F1C7F8FF                     
6A 00                           
6A 01                           
E8 06D2F8FF                     
83C4 08                         
8B45 D4                         
8945 C4                         
C745 FC FEFFFFFF                
8B45 C4                         
EB 68                           
C745 FC FEFFFFFF                
EB 5F                           
8B4D EC                         
8B11                            
8B02                            
8945 D0                         
8B4D EC                         
51                              
8B55 D0                         
52                              
E8 8BDBF8FF                     
83C4 08                         
C3                              
8B65 E8                         
8B45 D0                         
8945 CC                         
E8 6DCEF8FF                     
0FB6C8                          
85C9                            
75 09                           
8B55 CC                         
52                              
E8 4CD5F8FF                     
0FB645 E7                       
85C0                            
75 05                           
E8 A6E6F8FF                     
8B4D CC                         
894D C0                         
C745 FC FEFFFFFF                
8B45 C0                         
EB 07                           
C745 FC FEFFFFFF                
8B4D F0                         
64:890D 00000000                
59                              
5F                              
5E                              
5B                              
8BE5                            
5D                              
C3                              
55                                      
8BEC                                    
56                                      
E8 D8CAF8FF                             
50                                      
E8 92D8F8FF                             
83C4 04                                 
E8 73EAF8FF                             
50                                      
E8 94CDF8FF                             
83C4 04                                 
E8 5BC7F8FF                             
8BF0                                    
E8 D3CFF8FF                             
8930                                    
6A 01                                   
E8 CDDBF8FF                             
83C4 04                                 
0FB6C0                                  
85C0                                    
75 07                                   
6A 07                                   
E8 27C6F8FF                             
DBE2                                    
E8 8DCCF8FF                             
68 BCE62401                             
E8 9ECAF8FF                             
83C4 04                                 
E8 92DDF8FF                             
85C0                                    
74 07                                   
6A 07                                   
E8 03C6F8FF                             
E8 C6DAF8FF                             
E8 9FCFF8FF                             
85C0                                    
74 0D                                   
68 4CE82401                             
E8 3FE5F8FF                             
83C4 04                                 
E8 BAD5F8FF                             
E8 BCD8F8FF                             
E8 3FC4F8FF                             
E8 B7C9F8FF                             
50                                      
E8 27C2F8FF                             
83C4 04                                 
E8 69030000                             
E8 37C8F8FF                             
33C0                                    
5E                                      
5D                                      
C3                                      
)"
//55 8B EC 81 EC CC 00 00 00 53 56 57 51 8D BD 34 FF FF FF B9 33 00 00 00 B8 CC CC CC CC F3 AB 59
//89 4D F8 8B 4D F8 E8 87 6E FE FF 5F 5E 5B 81 C4 CC 00 00 00 3B EC E8 D0 74 FE FF 8B E5 5D C3
,
""

}};


#if 0
CPU Disasm
Address   Hex dump            Command                                  Comments
0040505B     /0F80 00000000   JO 00405061
00405061    -\0F81 0F000089   JNO 89405076
00405067    - 0F82 0500008D   JB 8D405072
0040506D    - 0F83 FFE05669   JAE 69973172
00405073    - 0F84 75616C41   JE 41ACB1EE
00405079    - 0F85 6F630056   JNE 5640B3EE
0040507F    - 0F86 7475616C   JBE 6CA1C5F9
00405085    - 0F87 6565008B   JA 8B40B5F0

0F 90 C0
0F 91 C0
0F 92 C0
0F 93 C0
0F 94 C0
0F 95 C0
0F 96 C0
0F 97 C0
0F 98 C0
0F 99 C0
0F 9A C0
0F 9B C0
0F 9C C0
0F 9D C0
0F 9E C0
0F 9F C0
#endif