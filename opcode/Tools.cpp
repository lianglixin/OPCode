#include "Tools.h"

#include <vector>
#include <cassert>
#include <algorithm>
#include "DataType.h"
#include "Disassembler.h"
#include "OpcodeToString.h"
#include "Analysis.h"

std::vector <std::pair <size_t, NoteString>> Tools::toNoteStrings (
	const std::vector <Note> & notes)
{
	std::vector <std::pair <size_t, NoteString>> noteStrings;

	for (auto & note : notes)
	{
		switch (note.type)
		{
		case Note::Type::IF_STATE:
			noteStrings.push_back ({note._if.begin - 1, NoteString::IF});
			noteStrings.push_back ({note._if.begin, NoteString::OPEN_BRACE});
			noteStrings.push_back ({note._if.end, NoteString::CLOSE_BRACE});
			break;
		case Note::Type::IF_ELSE_STATE:
			noteStrings.push_back ({note._if_else.begin - 1, NoteString::IF});
			noteStrings.push_back ({note._if_else.begin, NoteString::OPEN_BRACE});
			noteStrings.push_back ({note._if_else.ifEnd, NoteString::CLOSE_BRACE});
			noteStrings.push_back ({note._if_else.ifEnd, NoteString::ELSE});
			noteStrings.push_back ({note._if_else.ifEnd + 1, NoteString::OPEN_BRACE});
			noteStrings.push_back ({note._if_else.elseEnd, NoteString::CLOSE_BRACE});
			break;
		case Note::Type::MULTI_CONDITION_IF_ELSE_STATEMENT:
		{
			auto & _if_else = note._multi_condition_if_else;
			auto & vec      = note._multi_condition_if_else.vec;

			noteStrings.push_back ({vec[0].pos, NoteString::IF});
			for (size_t i = 0; i < vec.size (); i++)
				noteStrings.push_back ({vec[i].pos, NoteString::JMP_TO_ELSE});
			noteStrings.push_back ({vec[0].pos, NoteString::IF_CONDITION_BLOCK_BEGIN});
			noteStrings.push_back ({vec[vec.size () - 1].pos + 1, NoteString::IF_CONDITION_BLOCK_END});
			noteStrings.push_back ({vec[vec.size () - 1].pos + 1, NoteString::OPEN_BRACE});
			noteStrings.push_back ({_if_else.ifEnd, NoteString::CLOSE_BRACE});
			noteStrings.push_back ({_if_else.ifEnd, NoteString::ELSE});
			noteStrings.push_back ({_if_else.ifEnd + 1, NoteString::OPEN_BRACE});
			noteStrings.push_back ({_if_else.elseEnd, NoteString::CLOSE_BRACE});
			break;
		}
		default:
			throw "";
		}
	}

	auto pred = [] (
		const std::pair <size_t, NoteString> & pair0,
		const std::pair <size_t, NoteString> & pair1)
	{
		return pair0.first < pair1.first;
	};

	std::sort (noteStrings.begin(), noteStrings.end(), pred);

	return noteStrings;
}
std::string Tools::disassemble (std::string binaryCode, bool isNote, InstSet instSet)
{
	std::vector <Byte> opcode = toVecOpcode (binaryCode);
	std::vector <Instruction> insts = toInsts (opcode, instSet);

	std::vector <std::pair <size_t, NoteString>> noteStrings;
	if (isNote)
	{
		Analysis analysis {insts};
		std::vector <Note> notes = analysis.analyse ();
		noteStrings = toNoteStrings (notes);
	}

	std::string re;
	int 缩进 = 0;
	int 微量缩进 = 0;
	int lineNum = 0;
	auto addLine = [&re, &缩进, &微量缩进, &lineNum] (const std::string & str)
	{
		{
			char tmp[10];
			sprintf_s (tmp, 10, "%d\t", lineNum);
			re += tmp;
			lineNum ++;
		}
		for (int i = 0; i < 缩进; i++)
			re += "          ";
		for (int i = 0; i < 微量缩进; i++)
			re += "   ";
		re += str;
		re += '\r';
		re += '\n';
	};
	size_t noteStringIndex {};
	for (size_t i = 0; i < insts.size (); i++)
	{
		std::string addToInst;
		while (1)
		{
			if (false == isNote)
				break;

			if (noteStringIndex >= noteStrings.size ())
				break;

			if (noteStrings[noteStringIndex].first != i)
				break;

			switch (noteStrings[noteStringIndex].second)
			{
			case NoteString::IF:
				addLine ("if");
				break;
			case NoteString::ELSE:
				addLine ("else");
				break;
			case NoteString::OPEN_BRACE:
				addLine ("{");
				缩进 ++;
				break;
			case NoteString::CLOSE_BRACE:
				缩进 --;
				addLine ("}");
				break;
			case NoteString::IF_CONDITION_BLOCK_BEGIN:
				微量缩进 ++;
				break;
			case NoteString::IF_CONDITION_BLOCK_END:
				微量缩进 --;
				break;
			case NoteString::BLANK:
				addLine ("");
				break;
			case NoteString::JMP_TO_ELSE:
				addToInst += "\t(to else)";
				break;
			default:
				throw "";
			}
			noteStringIndex ++;
		}

		OpcodeToString conv2 {insts[i]};
		auto str = conv2.toString ();
		str += addToInst;
		addLine (str);
	}
	assert (isNote == false || noteStringIndex == noteStrings.size ());
	return re;
}
std::vector <Byte> Tools::toVecOpcode (const std::string & strOpcode)
{
	std::vector <unsigned char> vec;
	int index {};

	while (1)
	{
		if (index == strOpcode.length ())
			break;

		if (strOpcode[index] == ' ' ||
			strOpcode[index] == '\n' ||
			strOpcode[index] == '\r' ||
			strOpcode[index] == '\t' ||
			strOpcode[index] == ':')
		{
			index ++;
			continue;
		}

		if (index + 1 == strOpcode.length ())
			throw "";

		union
		{
			struct
			{
				unsigned char low:4;
				unsigned char high:4;
			};

			Byte b;
		} b;

		static_assert (sizeof (b) == 1, "");

		auto get = [] (char c) -> unsigned char
		{
			if (c >= '0' && c <= '9')
				return c - '0';
			if (c >= 'A' && c <= 'F')
				return c - 'A' + 0xA;
			if (c >= 'a' && c <= 'f')
				return c - 'a' + 0xA;

			throw "";
		};

		b.high = get (strOpcode[index]);
		b.low = get (strOpcode[index + 1]);

		vec.push_back (b.b);

		index += 2;
	}

	return vec;
}
std::vector <Instruction> Tools::toInsts (const std::vector <Byte> & opcode, InstSet instSet)
{
	std::vector <Instruction> insts;

	size_t index {};
	while (1)
	{
		if (index == opcode.size ())
			break;
		Disassembler conv {opcode, instSet};
		auto instruction = conv.conv ((unsigned)index);
		index += instruction.size;
		if (index > opcode.size ())
			throw "";
		insts.push_back (instruction);
	}

	return insts;
}