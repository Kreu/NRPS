#include "stdafx.h"
#include "CppUnitTest.h"
#include "../NRPS/Parser.h"
#include "../NRPS/GenBankParser.h"

class Parser;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(PARSETESTS)
	{
	public:
		
		TEST_METHOD(TESTLOADFILE)
		{
			Parser& parser = GenBankParser();
			Assert::AreEqual(CLOSED, parser.loadFile(""));
		}

	};
}