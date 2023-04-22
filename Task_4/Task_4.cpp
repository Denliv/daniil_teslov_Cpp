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
			//Тест на получение несуществующего элемента
			try {
				iter.getElem();
			}
			catch (std::overflow_error ex) {
				Assert::AreEqual("Can not get current element\n", ex.what());
			}
			//Проверка toString()
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
		}
	};
}
