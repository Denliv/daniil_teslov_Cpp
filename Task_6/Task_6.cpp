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
			Assert::AreEqual(5, dic1.numberOfWords(dic1.getRootCopy()));
			Assert::AreEqual(1, dic1.findWord("D"));
			Logger::WriteMessage((dic1.toString(dic1.getRootCopy()) + "\n").c_str());
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("DELETE A =>\n");
			dic1.deleteWord(dic1.getRoot(), "A");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("DELETE D =>\n");
			dic1.deleteWord(dic1.getRoot(), "D");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("ADD D =>\n");
			dic1.addWord(dic1.getRoot(), "D");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("DELETE C =>\n");
			dic1.deleteWord(dic1.getRoot(), "C");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("DELETE B =>\n");
			dic1.deleteWord(dic1.getRoot(), "B");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("ADD A LOT OF WORDS =>\n");
			dic1.addWord(dic1.getRoot(), "E");
			dic1.addWord(dic1.getRoot(), "F");
			dic1.addWord(dic1.getRoot(), "G");
			dic1.addWord(dic1.getRoot(), "B");
			dic1.addWord(dic1.getRoot(), "H");
			dic1.addWord(dic1.getRoot(), "I");
			dic1.addWord(dic1.getRoot(), "J");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("DELETE H =>\n");
			dic1.deleteWord(dic1.getRoot(), "H");
			Logger::WriteMessage((dic1.toLevelString(dic1.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("DICTIONARY_2\n");
			Dictionary dic2;
			dic2.addWord(dic2.getRoot(), "E");
			dic2.addWord(dic2.getRoot(), "B");
			dic2.addWord(dic2.getRoot(), "F");
			dic2.addWord(dic2.getRoot(), "C");
			dic2.addWord(dic2.getRoot(), "A");
			Logger::WriteMessage((dic2.toLevelString(dic2.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("ADD D =>\n");
			dic2.addWord(dic2.getRoot(), "D");
			Logger::WriteMessage((dic2.toLevelString(dic2.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("DICTIONARY_3\n");
			Dictionary dic3;
			dic3.addWord(dic3.getRoot(), "D");
			dic3.addWord(dic3.getRoot(), "C");
			dic3.addWord(dic3.getRoot(), "E");
			dic3.addWord(dic3.getRoot(), "A");
			Logger::WriteMessage((dic3.toLevelString(dic3.getRootCopy(), 0) + "\n").c_str());
			Logger::WriteMessage("ADD B =>\n");
			dic3.addWord(dic3.getRoot(), "B");
			Logger::WriteMessage((dic3.toLevelString(dic3.getRootCopy(), 0) + "\n").c_str());
		}
	};
}
