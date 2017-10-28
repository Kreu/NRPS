#pragma once

class ParserTests {
public:
	void testLoadFileNotFound();
	void testLoadFileOpenARealFile();
	void testLoadFileFileAlreadyOpen();

	void testcloseFileCloseAnOpenFile();
	void testcloseFileNoFileIsOpen();


	void testAll();
};