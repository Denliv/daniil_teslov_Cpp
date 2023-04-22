#pragma once
#include <iostream>
class hash_table_exception {
private:
	std::string exception;
public:
	hash_table_exception(std::string message) : exception(message) {}
};
template <typename T>
class HashTable {
private:
	template <typename K>
	struct Node {
		Node<K>* next;
		Node<K>* prev;
		K* value;
	};
	Node<T>* arr = nullptr;
	int size = 0;
	int number_of_elements = 0;
public:
	template <typename V>
	class TableIterator {
	private:
		Node<V>* current;
		int arr_index;
		const HashTable<V>& iterable;
	public:
		TableIterator(const HashTable<V>& table) : current(&table.arr[0]), arr_index(0), iterable(table) {}
		void start() {
			arr_index = 0;
			current = &iterable.arr[0];
		}
		const V& getElem() {
			if (finish()) {
				throw std::overflow_error("Can not get current element\n");
			}
			if (current->next->value == nullptr) {
				int next_index = arr_index + 1;
				Node<T>* temp = &(iterable.arr[next_index]);
				while (temp->next->value == nullptr && !finish()) {
					next_index++;
					temp = &(iterable.arr[next_index]);
				}
				return *(temp->next->value);
			}
			return *(current->next->value);
		}
		void next() {
			while (current->next->value == nullptr && !finish()) {
				arr_index++;
				current = &iterable.arr[arr_index];
			}
			if (!finish()) {
				current = current->next;
			}
		}
		bool finish() {
			return current->next == &iterable.arr[iterable.size - 1];
		}
		Node<V>* getCurrent() {
			return current;
		}
		int getArrIndex() {
			return arr_index;
		}
		const HashTable<V>& getIterable() {
			return iterable;
		}
	};
	HashTable() : HashTable(10) {}
	HashTable(int size) {
		arr = new Node<T>[size];
		this->size = size;
		this->number_of_elements = 0;
		for (int i = 0; i < this->size; ++i) {
			Node<T>* temp = &(this->arr[i]);
			temp->next = temp->prev = temp;
			temp->value = nullptr;
		}
	}
	HashTable(const HashTable<T>& table) : HashTable(table.size) {
		TableIterator<T>& iter = table.headIterator();
		iter.start();
		while (!iter.finish()) {
			this->push(iter.getElem());
			iter.next();
		}
		delete& iter;
	}
	~HashTable() {
		makeEmpty();
		delete[] arr;
	}
	void push(const T& obj) {
		T* elem = new T(obj);
		Node<T>* newElem = nullptr;
		try {
			newElem = new Node<T>();
		}
		catch (std::bad_alloc ex) {
			throw hash_table_exception("Error:push\n");
		}
		Node<T>* temp = &(this->arr[hash(*elem)]);
		newElem->value = elem;
		newElem->next = temp;
		newElem->prev = temp->prev;
		temp->prev->next = newElem;
		temp->prev = newElem;
		this->number_of_elements++;
	}
	void deleteElem(const T& obj) {
		if (!searchElem(obj)) {
			throw hash_table_exception("Error:delete element\n");
		}
		auto& iter = headIterator();
		iter.start();
		while (!iter.finish()) {
			if (iter.getElem() == obj) {
				iter.next();
				Node<T>* temp = iter.getCurrent();
				Node<T>* temp_prev = temp->prev;
				Node<T>* temp_next = temp->next;
				temp_prev->next = temp_next;
				temp_next->prev = temp_prev;
				this->number_of_elements--;
				break;
			}
			iter.next();
		}
		delete& iter;
	}
	bool searchElem(const T& obj) {
		if (this->number_of_elements == 0) {
			return false;
		}
		auto& iter = headIterator();
		iter.start();
		while (!iter.finish()) {
			if (iter.getElem() == obj) {
				delete& iter;
				return true;
			}
			iter.next();
		}
		delete& iter;
		return false;
	}
	int getSize() {
		return size;
	}
	int getNumberOfElements() {
		return number_of_elements;
	}
	Node<T>* getArr() {
		return arr;
	}
	void makeEmpty() {
		if (this->arr == nullptr) {
			return;
		}
		for (int i = 0; i < this->size; ++i) {
			Node<T>* current = &(this->arr[i]);
			while (current->next != current) {
				Node<T>* temp = current->next->next;
				delete current->next;
				temp->prev = current;
				current->next = temp;
			}
		}
	}
	bool isEmpty() {
		for (int i = 0; i < this->size; ++i) {
			Node<T>* temp = &(this->arr[i]);
			if (temp->next != temp) {
				return false;
			}
		}
		return true;
	}
	std::string toString() {
		std::string answer = "";
		for (int i = 0; i < this->size; ++i) {
			answer += std::to_string(i) + "::\n";
			Node<T>* temp = &(this->arr[i]);
			while (temp->next->value != nullptr) {
				answer += std::to_string(*(temp->next->value)) + "\n";
				temp = temp->next;
			}
		}
		return answer;
	}
	int hash(const T& obj) {
		return std::hash<T>()(obj) % this->size;
	}
	TableIterator<T>& headIterator() const {
		TableIterator<T>* temp = new TableIterator<T>(*this);
		return *temp;
	}
};