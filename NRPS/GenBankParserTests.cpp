#include "stdafx.h"
#include <cassert>
#include "Parser.h"
#include "GenBankParser.h"
#include "GenBankParserTests.h"


//Tests for loadFile()
void GenBankParserTests::testParseHeader() {
	Parser& parser = GenBankParser();
	parser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\AE000516.2.cluster001.gbk");
	parser.parseHeader();
}

void GenBankParserTests::testParseFeatures() {
	Parser& parser = GenBankParser();
	parser.loadFile("C:\\Users\\Valdeko\\source\\repos\\NRPS\\Debug\\AE000516.2.cluster001.gbk");
	parser.parseFeatures();
}

void GenBankParserTests::testAll() {
	testParseHeader();
	testParseFeatures();
}