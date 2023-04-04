#pragma once
#include <iostream>
#include "AbstractList.h"
class looped_list_exception {
private:
	std::string exception;
public:
	looped_list_exception(std::string message) : exception(message) {}
};
template <typename T>
class LoopedList : public AbstractList<T> {
private:
	template <typename K>
	struct Node {
		Node* next;
		Node* prev;
		K value;
	};
	Node<T>* buffer;
	int size;
public:
	template <typename V>
	class ListIterator : public AbstractIterator<V> {
	private:
		Node<V>* current;
		const LoopedList<V>& iterable;
	public:
		ListIterator(const LoopedList<V>& list) : current(list.buffer), iterable(list) {}
		void start() {
			current = iterable.buffer;
		}
		const V& getElem() {
			if (current == iterable.buffer->prev) {
				throw std::overflow_error("Can not get current element\n");
			}
			return current->next->value;
		}
		void next() {
			if (current->next != iterable.buffer) {
				current = current->next;
			}
		}
		bool finish() {
			return current == iterable.buffer->prev;
		}
		Node<V>* getCurrent() {
			return current;
		}
		const LoopedList<V>& getIterable() {
			return iterable;
		}
	};
	LoopedList() {
		buffer = new Node<T>();
		buffer->next = buffer->prev = buffer;
		size = 0;
	}
	LoopedList(const LoopedList<T>& list) : LoopedList() {
		AbstractIterator<T>& iter = list.headIterator();
		iter.start();
		while (!iter.finish()) {
			Node<T>* newElem = nullptr;
			try {
				newElem = new Node<T>();
			}
			catch (std::bad_alloc ex) {
				makeEmpty();
				delete buffer;
				size = 0;
				delete& iter;
				throw looped_list_exception("Error:copy constructor\n");
			}
			newElem->value = iter.getElem();
			Node<T>* current = buffer->prev;
			current->next = newElem;
			newElem->prev = current;
			newElem->next = buffer;
			buffer->prev = newElem;
			this->size++;
			iter.next();
		}
		delete& iter;
	}
	LoopedList(LoopedList<T>&& list) {
		this->size = list.size;
		this->buffer = list.buffer;
		list.buffer = nullptr;
		list.size = 0;
	}
	~LoopedList() {
		makeEmpty();
		delete buffer;
	}
	LoopedList& operator= (const LoopedList& list) {
		if (this == &list) return *this;
		Node<T>* current_buffer = new Node<T>();
		current_buffer->next = current_buffer->prev = current_buffer;
		AbstractIterator<T>& iter = list.headIterator();
		iter.start();
		while (!iter.finish()) {
			Node<T>* newElem = nullptr;
			try {
				newElem = new Node<T>();
			}
			catch (std::bad_alloc ex) {
				makeEmpty();
				delete current_buffer;
				delete& iter;
				throw looped_list_exception("Error:operator =\n");
			}
			newElem->value = iter.getElem();
			Node<T>* current = current_buffer->prev;
			current->next = newElem;
			newElem->prev = current;
			newElem->next = current_buffer;
			current_buffer->prev = newElem;
			iter.next();
		}
		this->makeEmpty();
		this->buffer = current_buffer;
		this->size = list.size;
		delete& iter;
		return *this;
	}
	void put(const T& x, AbstractIterator<T>& iterator) {
		ListIterator<T>* newIterator = dynamic_cast<ListIterator<T>*>(&iterator);
		if (newIterator == nullptr || &(newIterator->getIterable()) != this) {
			throw looped_list_exception("Error:get\n");
		}
		Node<T>* newElem = nullptr;
		try {
			newElem = new Node<T>();
		}
		catch (std::bad_alloc ex) {
			throw looped_list_exception("Error:get\n");
		}
		newElem->value = x;
		Node<T>* current = newIterator->getCurrent();
		Node<T>* current_next = newIterator->getCurrent()->next;
		current->next = newElem;
		current_next->prev = newElem;
		newElem->next = current_next;
		newElem->prev = current;
		this->size++;
	}
	void deleteElem(AbstractIterator<T>& iterator) {
		ListIterator<T>* newIterator = dynamic_cast<ListIterator<T>*>(&iterator);
		if (newIterator == nullptr ||
			&(newIterator->getIterable()) != this || 
			isEmpty()
			|| newIterator->finish()) {
			throw looped_list_exception("Error:deleteElem\n");
		}
		Node<T>* temp = newIterator->getCurrent()->next->next;
		delete newIterator->getCurrent()->next;
		temp->prev = newIterator->getCurrent();
		newIterator->getCurrent()->next = temp;
		size--;
	}
	AbstractIterator<T>& firstInstanceIterator(const T& x) {
		ListIterator<T>* iter = new ListIterator<T>(*this);
		iter->start();
		while (!iter->finish()) {
			if (iter->getElem() == x) {
				return *iter;
			}
			iter->next();
		}
		delete iter;
		throw looped_list_exception("Error:firstInstanceIterator\n");
	}
	void makeEmpty() {
		if (buffer == nullptr) {
			return;
		}
		while (buffer->next != buffer) {
			Node<T>* temp = buffer->next->next;
			delete buffer->next;
			temp->prev = buffer;
			buffer->next = temp;
		}
		size = 0;
	}
	bool isEmpty() {
		return size == 0;
	}
	int length() {
		return size;
	}
	AbstractIterator<T>& headIterator() const {
		ListIterator<T>* temp = new ListIterator<T>(*this);
		return *temp;
	}
};