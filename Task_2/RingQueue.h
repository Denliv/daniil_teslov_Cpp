#pragma once
#include <iostream>
template<typename T>
class RingQueue {
private:
	T* arr = nullptr;
	int head = 0;
	int tail = 0;
	int length;	
public:
	template <typename T>
	friend class Iterator;
	RingQueue(int length) {
		length++;
		this->arr = new T[length];
		this->length = length;
		head = tail = 0;
	}
	~RingQueue() {
		delete[] arr;
		arr = nullptr;
		length = head = tail = 0;
	}
	void push(const T& x) {
		if ((tail + 1) % length == head % length) {
			throw std::overflow_error("Error: Not Enough Place\n");
		}
		this->arr[tail] = x;
		tail = (tail + 1) % length;
	}
	const T& pull() {
		if (head == tail) {
			throw std::overflow_error("Queue Is Empty\n");
		}
		T temp = this->arr[head];
		head = (head + 1) % length;
		return temp;
	}
	const T& get() {
		if (this->arr[head] == this->arr[tail]) {
			throw std::overflow_error("Queue Is Empty\n");
		}
		return this->arr[head];
	}
	int queueLength() {
		return this->length - 1;
	}
	void makeEmpty() {
		while (head != tail) {
			pull();
		}
	}
	bool isEmpty() {
		return head == tail;
	}
};
template <typename T>
class Iterator {
private:
	int current_index;
	RingQueue<T>& iter;
public:
	Iterator(RingQueue<T>& queue) : iter(queue), current_index(queue.head) {}
	void start() {
		if (iter.head == iter.tail) return;
		current_index = iter.head;
	}
	void next() {
		if (current_index != iter.tail % iter.length && iter.head != iter.tail) {
			current_index = (current_index + 1) % iter.length;
		}
	}
	bool finish() {
		if (current_index == iter.tail || iter.head == iter.tail) {
			return true;
		}
		return false;
	}
	const T& getValue() {
		if (current_index == iter.tail || iter.head == iter.tail) {
			throw std::overflow_error("Can not get current element\n");
		}
		return iter.arr[current_index];
	}
};

