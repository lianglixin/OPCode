#include "CppUnitTest.h"
#include "Disassembler.h"
#include <string>
#include "TestData.h"
#include "TestAnalysis.h"
#include "TestDisassembler.h"
#include "TestFunc.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD (testAnalysis)
		{
			TestAnalysis test;
			test.testState (
R"(
					55               
					8B EC            
					83 7D 08 03      
					68 08 21 34 00   
					E8 BD FF FF FF   
					83 C4 04         

					33 C0            

					5D               
					C3               
)"
				,
				{
				}
				);
			test.testState (
R"(
					55               
					8B EC            
					83 7D 08 03      
					75 0D            

					68 08 21 34 00   
					E8 BD FF FF FF   
					83 C4 04         

					33 C0            

					5D               
					C3               
)"
				,
				{
					Note::IF_STATEMENT (4, 7),
				}
				);
			test.testState (
R"(
					55                   
					8B EC                
					83 7D 08 03          
					75 0D                

					68 08 21 EB 00       
					E8 BD FF FF FF       
					83 C4 04             

					8B 45 0C             
					8B 00                
					80 38 04             
					75 0D                

					68 08 21 EB 00       
					E8 A6 FF FF FF       
					83 C4 04             
					33 C0                

					5D                   
					C3                   
)"
				,
				{
					Note::IF_STATEMENT (4, 7),
					Note::IF_STATEMENT (11, 14),
				}
				);
			test.testState (
R"(
55                   

8B EC                
83 7D 08 03          
75 31                

68 08 21 E5 00       
E8 BD FF FF FF       

8B 45 0C             
83 C4 04             
8B 00                
80 38 04             
75 0D                

68 10 21 E5 00       
E8 A6 FF FF FF       
83 C4 04             

68 18 21 E5 00       
E8 99 FF FF FF       
83 C4 04             

33 C0                

5D                   
C3                   


)"
				,
				{
					Note::IF_STATEMENT (4, 17),
					Note::IF_STATEMENT (11, 14),
				}
				);
			test.testState (
R"(
55                
8B EC             
83 7D 08 03       
75 11             

6A 01             
68 08 21 A8 00    
E8 BB FF FF FF    
83 C4 08          

EB 0E             

68 10 21 A8 00    
FF 15 64 20 A8 00 
83 C4 04          

68 18 21 A8 00    
E8 9E FF FF FF    
68 10 21 A8 00    
FF 15 64 20 A8 00 
83 C4 08          
33 C0             
5D                
C3                
)"
				,
				{
					Note::IF_ELSE_STATEMENT (4, 8, 12),
				}
				);
			test.testState (
R"(
55                   
8B EC                

83 7D 08 03          
75 11                

6A 01                
68 08 21 1E 00       
E8 BB FF FF FF       
83 C4 08             


EB 2B                

8B 45 0C             
8B 00                
80 38 04             
75 10                

68 10 21 1E 00       
FF 15 64 20 1E 00    
83 C4 04             

EB 11                

6A 05                
6A 01                
68 08 21 1E 00       
E8 8E FF FF FF       
83 C4 0C             


68 18 21 1E 00       
E8 81 FF FF FF       
68 10 21 1E 00       
FF 15 64 20 1E 00    
83 C4 08             
33 C0                
5D                   
C3                   
)"
				,
				{
					Note::IF_ELSE_STATEMENT (4, 8, 22),
					Note::IF_ELSE_STATEMENT (13, 16, 22),
				}
				);
			test.testState (
R"(
55                  
8B EC               

83 7D 08 03         
75 19               
8B 45 0C            
8B 00               
80 38 04            
75 0F               

6A 01               
68 08 21 95 00      
E8 B1 FF FF FF      
83 C4 08            

68 10 21 95 00      
E8 A4 FF FF FF      
68 18 21 95 00      
FF 15 64 20 95 00   
83 C4 08            
33 C0               
5D                  
C3                  
)"
				,
				{
					Note::IF_STATEMENT (4, 12),
					Note::IF_STATEMENT (8, 12),
				}
				);
			test.testState (
R"(
55                 
8B EC              
83 7D 08 03        
75 1B              
8B 45 0C           
8B 00              
80 38 04           
75 11              

6A 01              
68 08 21 27 00     
E8 B1 FF FF FF     
83 C4 08           


EB 11              

6A 05              
6A 01              
68 08 21 27 00     
E8 9E FF FF FF     
83 C4 0C           

68 10 21 27 00     
E8 91 FF FF FF     
68 18 21 27 00     
FF 15 64 20 27 00  
83 C4 08           
33 C0              
5D                 
C3                 
)"
				,
				{
					Note::MULTI_CONDITION_IF_ELSE_STATEMENT (
						{
							{3, Note::MultiConditionIfElse::JmpTo::ELSE},
							{7, Note::MultiConditionIfElse::JmpTo::ELSE},
						}, 12, 18),
				}
				);

		}
		TEST_METHOD (testDisasm_x86)
		{
			TestData data;
			TestFunc func;
			TestDisassembler func2;

			data.testBinaryCodeToInstruction (
				std::bind (&TestFunc::to_inst,
						   &func,
						   std::placeholders::_1,
						   std::placeholders::_2,
						   InstSet::x86));

			data.testInstructionToString (
				std::bind (&TestFunc::to_string,
						   &func,
						   std::placeholders::_1,
						   std::placeholders::_2,
						   InstSet::x86));

			data.testBinaryCodeToString_MultiInstructions (
				std::bind (&TestDisassembler::testBinaryCodeToString_MultiInstructions,
						   &func2,
						   std::placeholders::_1,
						   std::placeholders::_2));
		}
		TEST_METHOD (testDisasm_x64)
		{
			TestData data;
			TestFunc func;

			data.to_inst_x64 (
				std::bind (&TestFunc::to_inst,
						   &func,
						   std::placeholders::_1,
						   std::placeholders::_2,
						   InstSet::x64));

			data.to_string_x64 (
				std::bind (&TestFunc::to_string,
						   &func,
						   std::placeholders::_1,
						   std::placeholders::_2,
						   InstSet::x64));
		}
	};
}