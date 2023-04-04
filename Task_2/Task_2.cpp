#include "pch.h"
#include "CppUnitTest.h"
#include "RingQueue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Task2 {
	TEST_CLASS(Task2) {
	public:
		TEST_METHOD(RingQueueTest) {
			RingQueue<int> queue1(10);
			queue1.push(1);
			queue1.push(2);
			queue1.push(3);
			queue1.push(4);
			queue1.push(5);
			queue1.push(6);
			queue1.push(7);
			queue1.push(8);
			queue1.push(9);
			queue1.push(10);
			try {
				queue1.push(11);
			}
			catch (std::overflow_error ex) {
				Assert::AreEqual("Error: Not Enough Place\n", ex.what());
			}
			Assert::AreEqual(10, queue1.queueLength());
			Assert::AreEqual(1, queue1.get());
			Assert::AreEqual(1, queue1.pull());
			queue1.makeEmpty();
			Assert::IsTrue(queue1.isEmpty());
			try {
				queue1.pull();
			}
			catch (std::overflow_error ex) {
				Assert::AreEqual("Queue Is Empty\n", ex.what());
			}
		}

		TEST_METHOD(QueueIteratorTest) {
			RingQueue<int> queue1(10);
			queue1.push(1);
			queue1.push(2);
			queue1.push(3);
			queue1.push(4);
			queue1.push(5);
			queue1.push(6);
			queue1.push(7);
			queue1.push(8);
			queue1.push(9);
			queue1.push(10);
			queue1.pull();
			queue1.pull();
			queue1.pull();
			int sum = 0;
			Iterator<int> queue_iter(queue1);
			queue_iter.start();
			while (!queue_iter.finish()) {
				sum += queue_iter.getValue();
				queue_iter.next();
			}
			Assert::AreEqual(49, sum);
		}
	};
}
