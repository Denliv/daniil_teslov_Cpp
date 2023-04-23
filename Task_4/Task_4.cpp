#include "pch.h"
#include "HashTable.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Task4 {
	TEST_CLASS(Task4) {
	public:
		TEST_METHOD(TestMethod1) {
			//Проверка создания таблицы и заполнения её элементами
			HashTable<int> table1(5);
			table1.push(1);
			table1.push(2);
			table1.push(3);
			table1.push(4);
			table1.push(5);
			//Проверка итератора
			auto& iter = table1.headIterator();
			iter.start();
			Assert::AreEqual(4, iter.getElem());
			iter.next();
			Assert::AreEqual(1, iter.getElem());
			iter.next();
			Assert::AreEqual(2, iter.getElem());
			iter.next();
			Assert::AreEqual(3, iter.getElem());
			iter.next();
			Assert::AreEqual(5, iter.getElem());
			iter.next();
			//Проверка итератора LinkedHashTable
			iter.startList();
			Assert::AreEqual(1, iter.getListElem());
			iter.nextList();
			Assert::AreEqual(2, iter.getListElem());
			iter.nextList();
			Assert::AreEqual(3, iter.getListElem());
			iter.nextList();
			Assert::AreEqual(4, iter.getListElem());
			iter.nextList();
			Assert::AreEqual(5, iter.getListElem());
			iter.nextList();
			//Проверка итератора LinkedHashTable выводом
			Logger::WriteMessage("LIST_ITERATOR\n");
			iter.startList();
			while (!iter.finishList()) {
				std::string temp = std::to_string(iter.getListElem()) + "\n";
				Logger::WriteMessage(temp.c_str());
				iter.nextList();
			}
			//Тест на получение несуществующего элемента
			try {
				iter.getElem();
			}
			catch (std::overflow_error ex) {
				Assert::AreEqual("Can not get current element\n", ex.what());
			}
			//Проверка toString()
			Logger::WriteMessage("\nNOT_EMPTY_TABLE:\n");
			Logger::WriteMessage(table1.toString().c_str());
			//Поиск элементов
			Assert::IsTrue(table1.searchElem(1));
			Assert::IsTrue(table1.searchElem(2));
			Assert::IsTrue(table1.searchElem(3));
			Assert::IsTrue(table1.searchElem(4));
			Assert::IsTrue(table1.searchElem(5));
			//Удаление элементов
			table1.deleteElem(1);
			Assert::IsFalse(table1.searchElem(1));
			Assert::IsTrue(table1.searchElem(2));
			Assert::IsTrue(table1.searchElem(3));
			Assert::IsTrue(table1.searchElem(4));
			Assert::IsTrue(table1.searchElem(5));
			table1.deleteElem(2);
			table1.deleteElem(3);
			table1.deleteElem(4);
			table1.deleteElem(5);
			//Проверка пустоты
			Assert::IsTrue(table1.isEmpty());
			table1.push(1);
			table1.push(2);
			table1.push(3);
			table1.push(4);
			table1.push(5);
			table1.makeEmpty();
			Logger::WriteMessage("\nEMPTY_TABLE:\n");
			Logger::WriteMessage(table1.toString().c_str());
			Assert::IsTrue(table1.isEmpty());
		}
	};
}
