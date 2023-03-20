#include "pch.h"
#include <iostream>
#include "Box.h"
#include "Container.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1 {
	TEST_CLASS(UnitTest1) {
	public:
		TEST_METHOD(TestBox) {
			Task0::Box box1(1, 1, 1, 1, 1);
			Task0::Box box2(2, 2, 2, 2, 2);
			Task0::Box box3(3, 3, 3, 3, 3);
			Task0::Box box4(4, 4, 4, 4, 4);
			Task0::Box box5(5, 5, 5, 5, 5);
			Task0::Box box6(1, 2, 3, 4, 5);
			Task0::Box box7;
			Task0::Box box8(1, 1, 1, 1, 1);
			Task0::Box boxes1[] = { box1, box2, box3, box4, box5 };
			Task0::Box boxes2[] = { box1, box2, box3, box4, box6 };
			Assert::AreEqual(15, Task0::Box::valueSum(boxes1, 5));
			Assert::AreEqual(true, Task0::Box::correctBoxes(boxes1, 5, 8));
			Assert::AreNotEqual(true, Task0::Box::correctBoxes(boxes1, 5, 1));
			Assert::AreEqual(6.0, Task0::Box::maxCertainBoxesWeight(boxes1, 5, 27));
			Assert::AreEqual(true, Task0::Box::boxesCanBeInserted(boxes1, 5));
			Assert::AreEqual(false, Task0::Box::boxesCanBeInserted(boxes2, 5));
			Assert::AreEqual(1, box1.getLength());
			Assert::AreEqual(1, box1.getWidth());
			Assert::AreEqual(1, box1.getHeight());
			Assert::AreEqual(1.0, box1.getWeight());
			Assert::AreEqual(1, box1.getValue());
			box7.setLength(9);
			box7.setWidth(9);
			box7.setHeight(9);
			box7.setWeight(9);
			box7.setValue(9);
			Assert::AreEqual(9, box7.getLength());
			Assert::AreEqual(9, box7.getWidth());
			Assert::AreEqual(9, box7.getHeight());
			Assert::AreEqual(9.0, box7.getWeight());
			Assert::AreEqual(9, box7.getValue());
			Assert::AreEqual(false, box1 == box2);
			Assert::AreEqual(true, box1 == box8);
			std::ostringstream oss;
			oss << box1;
			Assert::AreEqual(true, "1 1 1 1 1" == oss.str());
			Assert::AreEqual(false, "1 1 1 1 2" == oss.str());
			std::istringstream iss("5 6 5 6 5");
			iss >> box1;
			Assert::AreEqual(5, box1.getLength());
			Assert::AreEqual(6, box1.getWidth());
			Assert::AreEqual(5, box1.getHeight());
			Assert::AreEqual(6.0, box1.getWeight());
			Assert::AreEqual(5, box1.getValue());
		}
		TEST_METHOD(TestContainer) {
			Task0::Box box1(1, 1, 1, 1, 1);
			Task0::Box box2(2, 2, 2, 2, 2);
			Task0::Box box3(3, 3, 3, 3, 3);
			Task0::Box box4(4, 4, 4, 4, 4);
			Task0::Box box5(5, 5, 5, 5, 5);
			Task0::Box box6(6, 6, 6, 4, 5);
			Task0::Container cont1(10, 10, 10, 100);
			cont1.addBox(box1);
			cont1.addBox(box2);
			cont1.addBox(box3);
			cont1.addBox(box4);
			cont1.addBox(box5);
			cont1.addBox(box6);
			Assert::AreEqual(6, cont1.numberOfBoxes());
			Assert::AreEqual(19.0, cont1.getWeight());
			Assert::AreEqual(20, cont1.getValue());
			Assert::AreEqual(true, box1 == cont1.getBox(0));
			Task0::Box box7(9, 9, 9, 9, 9);
			cont1.addBox(box7);
			Assert::AreEqual(true, box7 == cont1.getBox(6));
			cont1.deleteBox(6);
			Assert::AreEqual(6, cont1.numberOfBoxes());
			Assert::AreEqual(true, box1 == cont1[0]);
			std::istringstream iss("5 6 5 6");
			Task0::Container cont2;
			iss >> cont2;
			std::ostringstream oss;
			oss << cont2;
			Assert::AreEqual(true, "5 6 5 6" == oss.str());
			Assert::AreEqual(false, "1 1 1 1" == oss.str());
		}
	};
}
