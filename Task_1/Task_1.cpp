#include "pch.h"
#include "CppUnitTest.h"
#include "DynamicArray.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2 {
	TEST_CLASS(UnitTest2) {
	public:
		DynamicArray& f(DynamicArray& arr) {
			return arr;
		}
		TEST_METHOD(TestMethod1) {
			DynamicArray arr1;
			DynamicArray arr2(15, 12);
			DynamicArray arr3(8, 1);
			DynamicArray arr4(3, 1, 4);
			DynamicArray arr5 = arr3;
			DynamicArray arr6 = f(DynamicArray(5, 5, 5));
			DynamicArray arr7;
			arr7 = DynamicArray(1, 2, 3);
			Assert::IsTrue(arr3 == arr5);
			Assert::AreEqual(15, arr2.length());
			Assert::AreEqual(1, arr3[0]);
			arr3[0] = 8;
			Assert::AreEqual(8, arr3[0]);
			arr2.resize(11);
			Assert::AreEqual(11, arr2.length());
			arr1.reserve(123);
			Assert::AreEqual(123, arr1.capacity());
			arr2.pushBack(123);
			Assert::AreEqual(12, arr2.length());
			Assert::AreEqual(123, arr2[arr2.length() - 1]);
			Assert::AreEqual(123, arr2.popBack());
			Assert::AreEqual(11, arr2.length());
			arr1 = arr2;
			Assert::IsTrue(arr1 == arr2);
			Assert::IsFalse(arr1 != arr2);
			arr1 = f(DynamicArray(5, 5, 5));
			arr2 = f(DynamicArray(10, 7, 5));
			Assert::IsTrue(arr1 < arr2);
			Assert::IsTrue(arr2 > arr1);
			Assert::IsTrue(arr2 <= arr2);
			Assert::IsTrue(arr2 >= arr2);
			arr2 = f(DynamicArray(10, 5, 5));
			Assert::IsTrue(arr1 <= arr2);
			arr1 = f(DynamicArray(5, 5, 5));
			arr2 = f(DynamicArray(10, 5, 5));
			DynamicArray arr8 = arr1 + arr2;
			DynamicArray arr9(15, 5, 0);
			Assert::IsTrue(arr9 == arr8);
			std::istringstream iss("3 3 4 5 5");
			DynamicArray arr10;
			iss >> arr10;
			std::ostringstream oss;
			oss << arr10;
			Assert::AreEqual(true, "3 3 4 5 5" == oss.str());
			Assert::AreEqual(false, "1 1 1 1" == oss.str());
		}
	};
}
