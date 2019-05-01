#include "Analysis.h"

#include <cassert>

Analysis::Analysis (const std::vector <Instruction> & insts)
	: _insts {insts}
{
}
std::vector <Note> Analysis::analyse ()
{
	analyse (0, _insts.size ());
	return _notes;
}
auto Analysis::getInstType (const Instruction & inst) -> InstType
{
	switch (inst.name)
	{
	case InstructionName::JE:
	case InstructionName::JNZ:
	case InstructionName::JL:
	case InstructionName::JAE:
		return InstType::CONDITION_JMP;
	case InstructionName::JMP_SHORT:
		return InstType::DIRECT_JMP;
	}
	return InstType::NO_NEED_ATTENTION;
}
template <typename T>
T Analysis::getInstImm (const Instruction & inst)
{
	assert (inst.operands.size () == 1);
	assert (inst.operands[0].type == OperandType::IMM);
	assert (inst.operands[0].imm.size == sizeof (T));

	return * (T*) & inst.operands[0].imm.val;
}
size_t Analysis::getInstIndex (size_t index, int offset)
{
	assert (index < _insts.size ());
	assert (offset >= 0);

	size_t i = index + 1;
	long long off = offset;
	while (1)
	{
		if (off == 0)
			break;

		if (i >= _insts.size ())
			throw "";

		off -= _insts[i].size;
		if (off < 0)
			throw "";

		i++;
	}

	return i;
}
void Analysis::noteIf (size_t begin, size_t end)
{
	_notes.push_back (Note::IF_STATEMENT (begin, end));
}
void Analysis::noteIfElse (size_t begin, size_t ifEnd, size_t elseEnd)
{
	_notes.push_back (Note::IF_ELSE_STATEMENT (begin, ifEnd, elseEnd));
}
void Analysis::noteMultiConditionIf_AllJmpToEnd (
	const std::vector <size_t> & jccs,
	size_t end)
{
	std::vector <Note::MultiConditionIf::EachIf> vec;
	for (auto jcc : jccs)
	{
		vec.push_back ({jcc, true});
	}

	_notes.push_back (Note::MULTI_CONDITION_IF_STATEMENT (vec, end));
}
void Analysis::noteMultiConditionIfElse_AllJmpToElse (
	const std::vector <size_t> & jccs,
	size_t ifEnd,
	size_t elseEnd)
{
	std::vector <Note::MultiConditionIfElse::EachIf> vec;
	for (auto jcc : jccs)
	{
		vec.push_back ({jcc, Note::MultiConditionIfElse::JmpTo::ELSE});
	}

	_notes.push_back (Note::MULTI_CONDITION_IF_ELSE_STATEMENT (vec, ifEnd, elseEnd));
}
size_t Analysis::meetConditionJmp (size_t i, size_t begin, size_t end)
{
	assert (InstType::CONDITION_JMP == getInstType (_insts[i]));

	int offset = getInstImm <int8> (_insts[i]);
	assert (offset >= 0);
	size_t index = getInstIndex (i, offset);

	//check whether is a if-else statement
	if (i + 1 < index)
	{
		if (InstType::DIRECT_JMP == getInstType (_insts[index - 1]))
		{
			int offsetElse = getInstImm <int8> (_insts[index - 1]);
			assert (offsetElse >= 0);

			//this is a if-else state

			size_t elseEnd = getInstIndex (index - 1, offsetElse);

			//check whether has multi conditions
			{
				std::vector <size_t> jccs {i};
				for (size_t j = i + 1; j < index - 1; j++)
				{
					switch (getInstType (_insts[j]))
					{
					case InstType::NO_NEED_ATTENTION:
						continue;
					case InstType::DIRECT_JMP:
						break;		// stop search
					case InstType::CONDITION_JMP:
					{
						int offset = getInstImm <int8> (_insts[j]);
						if (offset < 0)
							break;	// stop search
						size_t index2 = getInstIndex (j, offset);
						if (index2 != index)
							break;	// stop search
						//found multi condition
						jccs.push_back (j);
						continue;
					}
					default:
						throw "";
					}
					break;
				}
				if (jccs.size () > 1)
				{
					// this is a multi condition if else
					noteMultiConditionIfElse_AllJmpToElse (jccs, index - 1, elseEnd);
					analyse (jccs[jccs.size () - 1] + 1, index - 1);
					analyse (index, elseEnd);
					return elseEnd;
				}
			}

			noteIfElse (i + 1, index - 1, elseEnd);
			analyse (i + 1, index - 1);
			analyse (index, elseEnd);
			return elseEnd;
		}
	}

	//this is a if state

#if 0
	//check whether has multi conditions
	{
		std::vector <size_t> jccs {i};
		for (size_t j = i + 1; j < index; j++)
		{
			switch (getInstType (_insts[j]))
			{
			case InstType::NO_NEED_ATTENTION:
				continue;
			case InstType::DIRECT_JMP:
				break;		// stop while
			case InstType::CONDITION_JMP:
			{
				int offset = getInstImm <int8> (_insts[j]);
				if (offset < 0)
					break;	// stop while
				size_t index2 = getInstIndex (j, offset);
				if (index2 != index)
					break;	// stop while
				//found multi condition
				jccs.push_back (j);
				continue;
			}
			default:
				throw "";
			}
			break;
		}
		if (jccs.size() > 1)
		{
			// this is a multi condition if 
			noteMultiConditionIf_AllJmpToEnd (jccs, index);
			analyse (jccs[jccs.size() - 1] + 1, index);
			return index;
		}
	}
#endif

	noteIf (i + 1, index);
	analyse (i + 1, index);
	return index;
}
void Analysis::analyse (size_t begin, size_t end)
{
	for (size_t i = begin; i < end; )
	{
		switch (getInstType (_insts[i]))
		{
		case InstType::NO_NEED_ATTENTION:
		{
			i++;
			break;
		}
		case InstType::CONDITION_JMP:
		{
			i = meetConditionJmp (i, begin, end);
			break;
		}
		default:
			throw "";
		}
	}
}