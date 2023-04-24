#include "pch.h"
#include "BinaryTree.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Task5
{
	TEST_CLASS(Task5) {
	public:
		TEST_METHOD(TestMethod1) {
			//Создание дерева
			BinaryTree tree1;
			//Удалять нечего
			tree1.deleteLeaves();
			//Добавление элементов
			tree1.put(2, std::vector<int> {});
			tree1.put(1, std::vector<int> {0});
			tree1.put(3, std::vector<int> {1});
			tree1.put(-1, std::vector<int> {0, 0});
			tree1.put(5, std::vector<int> {1, 1});
			//Проверка числа чётных и положительных элементов
			Assert::AreEqual(1, tree1.numberOfEvenElements(tree1.getRoot()));
			Assert::IsFalse(tree1.isPositive(tree1.getRoot()));
			//Вывод дерева на экран
			Logger::WriteMessage("TREE_WITH_LEAVES\n");
			Logger::WriteMessage(tree1.toString(tree1.getRoot()).c_str());
			//Удаление листьев
			tree1.deleteLeaves();
			//Проверка удаления
			Logger::WriteMessage("\nTREE_WITHOUT_LEAVES\n");
			Logger::WriteMessage(tree1.toString(tree1.getRoot()).c_str());
			//Проверка среднего арифметического
			Assert::AreEqual(2.0, tree1.getAverage());
			//Проверка бинарности дерева
			Logger::WriteMessage("\nBINARY_TREE\n");
			Logger::WriteMessage(tree1.toString(tree1.getRoot()).c_str());
			Assert::IsTrue(tree1.isBinaryTree(tree1.getRoot()));
			tree1.put(10, std::vector<int> {0, 0});
			tree1.put(1, std::vector<int> {1, 1});
			Logger::WriteMessage("\nNON_BINARY_TREE\n");
			Logger::WriteMessage(tree1.toString(tree1.getRoot()).c_str());
			Assert::IsFalse(tree1.isBinaryTree(tree1.getRoot()));
			//Проверка наличия элементов в дереве
			Assert::IsTrue(tree1.inTree(2, tree1.getRoot()));
			Assert::IsTrue(tree1.inTree(1, tree1.getRoot()));
			Assert::IsTrue(tree1.inTree(3, tree1.getRoot()));
			Assert::IsTrue(tree1.inTree(10, tree1.getRoot()));
			Assert::IsFalse(tree1.inTree(22, tree1.getRoot()));
			//Проверка поиска элемента, возвращает путь
			Assert::IsTrue(std::vector<int> {} == tree1.find(2));
			Assert::IsTrue(std::vector<int> {0} == tree1.find(1));
			Assert::IsTrue(std::vector<int> {0, 0} == tree1.find(10));
			Assert::IsTrue(std::vector<int> {1} == tree1.find(3));
			//Проверка операторов
			BinaryTree tree2;
			tree2 = tree1;
			Logger::WriteMessage("\nTREE_2\n");
			Logger::WriteMessage(tree2.toString(tree2.getRoot()).c_str());
			BinaryTree tree3;
			tree3 = std::move(tree2);
			Logger::WriteMessage("\nTREE_2\n");
			Logger::WriteMessage(tree2.toString(tree2.getRoot()).c_str());
			Logger::WriteMessage("\nTREE_3\n");
			Logger::WriteMessage(tree3.toString(tree3.getRoot()).c_str());
			//Проверка вывода дерево по уровням
			Logger::WriteMessage("\nLEVELED_TREE_3\n");
			Logger::WriteMessage(tree3.toLevelString(tree3.getRoot(), 0).c_str());
		}
	};
}
