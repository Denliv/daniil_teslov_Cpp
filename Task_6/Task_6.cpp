#include "pch.h"
#include "Dictionary.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Task6
{
	TEST_CLASS(Task6) {
	public:
		TEST_METHOD(TestMethod1) {
			Dictionary dic1;
			dic1.addWord(dic1.getRoot(), "A");
			dic1.addWord(dic1.getRoot(), "B");
			dic1.addWord(dic1.getRoot(), "C");
			dic1.addWord(dic1.getRoot(), "D");
			dic1.addWord(dic1.getRoot(), "A");
			Logger::WriteMessage((dic1.toString(dic1.getRootCopy()) + "\n").c_str());
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			dic1.deleteWord(dic1.getRoot(), "A");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			dic1.deleteWord(dic1.getRoot(), "D");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			dic1.addWord(dic1.getRoot(), "D");
			dic1.deleteWord(dic1.getRoot(), "C");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			dic1.deleteWord(dic1.getRoot(), "B");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
		}
	};
}
