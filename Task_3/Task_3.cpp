#include "pch.h"
#include "CppUnitTest.h"
#include "LoopedList.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Task3 {
	TEST_CLASS(Task3) {
	public:
		TEST_METHOD(TestMethod1) {
			//Проверка конструктора, получение итератора на первый элемент, метод put()
			LoopedList<int> list1;
			AbstractIterator<int>& iter1 = list1.headIterator();
			list1.put(1, iter1);
			list1.put(2, iter1);
			list1.put(3, iter1);
			list1.put(4, iter1);
			//Конструктор копирования
			LoopedList<int> list2 = list1;
			AbstractIterator<int>& iter2 = list2.headIterator();
			iter2.start();
			Assert::AreEqual(4, iter2.getElem());
			iter2.next();
			Assert::AreEqual(3, iter2.getElem());
			iter2.next();
			Assert::AreEqual(2, iter2.getElem());
			iter2.next();
			Assert::AreEqual(1, iter2.getElem());
			//Удаление элементов
			iter2.start();
			list2.deleteElem(iter2);
			Assert::AreEqual(3, iter2.getElem());
			iter2.next();
			Assert::AreEqual(2, iter2.getElem());
			iter2.next();
			Assert::AreEqual(1, iter2.getElem());
			//Проверка на пустоту
			list2.makeEmpty();
			Assert::AreEqual(true, list2.isEmpty());
			//Оператор копирования
			LoopedList<int> list4;
			list4 = list1;
			//Конструктор перемещения
			LoopedList<int> list3 = std::move(list1);
			//Поиск первого элемента
			AbstractIterator<int>& iter4 = list4.headIterator();
			list4.put(2, iter4);
			Assert::AreEqual(iter4.getElem(), list4.firstInstanceIterator(2).getElem());
			iter4.next();
			Assert::AreEqual(iter4.getElem(), list4.firstInstanceIterator(4).getElem());
		}
	};
}
