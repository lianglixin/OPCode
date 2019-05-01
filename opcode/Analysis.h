#pragma once

#include "DataType.h"
#include <vector>

class Analysis
{
public:
	Analysis (const std::vector <Instruction> & insts);

public:
	std::vector <Note> analyse ();

private:
	enum class InstType
	{
		NO_NEED_ATTENTION,
		CONDITION_JMP,
		DIRECT_JMP,
	};

private:
	template <typename T>
	T getInstImm (const Instruction & inst);
	auto getInstType (const Instruction & inst) -> InstType;
	size_t getInstIndex (size_t i, int offset);
	void noteIf (size_t begin, size_t end);
	void noteIfElse (size_t begin, size_t ifEnd, size_t elseEnd);
	void noteMultiConditionIf_AllJmpToEnd (const std::vector <size_t> & jccs, size_t end);
	void noteMultiConditionIfElse_AllJmpToElse (const std::vector <size_t> & jccs, size_t ifEnd, size_t elseEnd);
	size_t meetConditionJmp (size_t i, size_t begin, size_t end);
	void analyse (size_t begin, size_t end);

private:
	const std::vector <Instruction> & _insts;
	std::vector <Note> _notes;
};