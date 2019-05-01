#include "TestAnalysis.h"


#include "CppUnitTest.h"
#include "Tools.h"
#include "Analysis.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
#define SS(A)	template<> inline std::wstring ToString <A> (const A & t) { return L""; }
			SS (Note::Type);
			SS (Note::MultiConditionIfElse::JmpTo);
#undef SS
		}
	}
}

void TestAnalysis::testState (
	const std::string & strOpcode,
	std::vector <Note> notesExpected)
{
	std::vector <Byte> vecOpcode = Tools::toVecOpcode (strOpcode);
	std::vector <Instruction> insts = Tools::toInsts (vecOpcode);
	Analysis analysis {insts};
	std::vector <Note> notes = analysis.analyse ();

	Assert::AreEqual (notesExpected.size (), notes.size ());
	for (unsigned i = 0; i < notesExpected.size (); i++)
	{
		Assert::AreEqual (notesExpected[i].type, notes[i].type);

		switch (notesExpected[i].type)
		{
		case Note::Type::IF_STATE:
			Assert::AreEqual (notesExpected[i]._if.begin, notes[i]._if.begin);
			Assert::AreEqual (notesExpected[i]._if.end, notes[i]._if.end);
			break;
		case Note::Type::IF_ELSE_STATE:
			Assert::AreEqual (notesExpected[i]._if_else.begin, notes[i]._if_else.begin);
			Assert::AreEqual (notesExpected[i]._if_else.ifEnd, notes[i]._if_else.ifEnd);
			Assert::AreEqual (notesExpected[i]._if_else.elseEnd, notes[i]._if_else.elseEnd);
			break;
		case Note::Type::MULTI_CONDITION_IF_STATEMENT:
			Assert::AreEqual (
				notesExpected[i]._multi_condition_if.vec.size (),
				notes[i]._multi_condition_if.vec.size ());
			for (
				unsigned j = 0;
				j < notesExpected[i]._multi_condition_if.vec.size ();
				j ++)
			{
				Assert::AreEqual (
					notesExpected[i]._multi_condition_if.vec[j].pos,
					notes[i]._multi_condition_if.vec[j].pos);
				Assert::AreEqual (
					notesExpected[i]._multi_condition_if.vec[j].isJmpToEnd,
					notes[i]._multi_condition_if.vec[j].isJmpToEnd);
			}

			break;
		case Note::Type::MULTI_CONDITION_IF_ELSE_STATEMENT:
			Assert::AreEqual (
				notesExpected[i]._multi_condition_if_else.vec.size (),
				notes[i]._multi_condition_if_else.vec.size ());
			for (
				unsigned j = 0;
				j < notesExpected[i]._multi_condition_if_else.vec.size ();
				j ++)
			{
				Assert::AreEqual (
					notesExpected[i]._multi_condition_if_else.vec[j].pos,
					notes[i]._multi_condition_if_else.vec[j].pos);
				Assert::AreEqual (
					notesExpected[i]._multi_condition_if_else.vec[j].jmpTo,
					notes[i]._multi_condition_if_else.vec[j].jmpTo);
			}

			break;
		default:
			Assert::Fail ();
		}
	}
}