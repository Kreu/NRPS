#include "stdafx.h"
#include "CppUnitTest.h"
#include "Parser.h"
#include "GenBankParser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NRPSTests
{		
	TEST_CLASS(ParserTests)
	{
	public:
		
		TEST_METHOD(TestFailedToLoadFile)
		{
			Parser& parser = GenBankParser("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\TestGenBankFile.gbk");
			std::unique_ptr<Header>& header = parser.GetHeader();
			header->PrintHeaderContent();
			const std::vector<std::unique_ptr<Feature>>& features = parser.GetFeatures();
		}

	};
}