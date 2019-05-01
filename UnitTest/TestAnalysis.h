#pragma once

#include <string>
#include <vector>
#include "DataType.h"

class TestAnalysis
{
public:
	void testState (const std::string & strOpcode, std::vector <Note> notesExpected);
};