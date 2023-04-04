#include "pch.h"
#include "DynamicArray.h"

DynamicArray::DynamicArray() : DynamicArray(10) {
}

DynamicArray::DynamicArray(int size) {
	this->array = new int[size];
	this->size = size;
}

DynamicArray::DynamicArray(int size, int n) : DynamicArray(size) {
	for (int i = 0; i < this->size; ++i) {
		array[i] = n;
	}
}

DynamicArray::DynamicArray(int size, int n, int reserve) : DynamicArray(size + reserve, n) {
	this->size -= reserve;
	this->reserve_val = reserve;
}

DynamicArray::DynamicArray(const DynamicArray& array) : DynamicArray(array.size) {
	for (int i = 0; i < this->size; ++i) {
		this->array[i] = array.array[i];
	}
	this->reserve_val = array.reserve_val;
}

DynamicArray::DynamicArray(DynamicArray&& array) {
	this->array = array.array;
	this->size = array.size;
	this->reserve_val = array.reserve_val;
	array.array = nullptr;
	array.size = 0;
	array.reserve_val = 0;
}

DynamicArray::~DynamicArray() {
	if (array != nullptr) delete[] array;
	size = 0;
	reserve_val = 0;
}

int DynamicArray::length() {
	return size;
}

int& DynamicArray::operator[](int x) {
	if (x >= size || x < 0) {
		throw std::overflow_error("Invalid index\n");
	}
	return array[x];
}

void DynamicArray::resize(int newSize) {
	if (newSize < 0) return;
	int oldsize = size;
	if (newSize > size + reserve_val) {
		int* p = this->array;
		size += reserve_val;
		reserve_val = 0;
		this->array = new int[newSize];
		for (int i = 0; i < std::min(newSize, oldsize); ++i) {
			this->array[i] = p[i];
		}
		delete[] p;
	}
	else {
		reserve_val = reserve_val + size - newSize;
		size = newSize;
	}
	for (int i = std::min(newSize, oldsize); i < newSize; ++i) {
		this->array[i] = 0;
	}
}

void DynamicArray::reserve(int n) {
	if (n <= 0) return;
	this->reserve_val = n;
	int* p = this->array;
	this->array = new int[size + n];
	for (int i = 0; i < size; ++i) {
		this->array[i] = p[i];
	}
	for (int i = size; i < size + n; ++i) {
		this->array[i] = 0;
	}
	delete[] p;
}

int DynamicArray::capacity() {
	return reserve_val;
}

void DynamicArray::pushBack(int x) {
	resize(size + 1);
	this->array[size - 1] = x;
}

int DynamicArray::popBack() {
	if (size == 0) throw std::length_error("Array is empty\n");
	int x = this->array[size - 1];
	resize(size - 1);
	return x;
}

DynamicArray& DynamicArray::operator=(const DynamicArray& array) {
	if (this == &array) return *this;
	int* p = new int[array.size];
	delete[] this->array;
	this->array = p;
	this->size = array.size;
	for (int i = 0; i < this->size; ++i) {
		this->array[i] = array.array[i];
	}
	this->reserve_val = array.reserve_val;
	return *this;
}

DynamicArray& DynamicArray::operator=(DynamicArray&& array) {
	if (this == &array) return *this;
	this->array = array.array;
	this->size = size;
	this->reserve_val = array.reserve_val;
	array.array = nullptr;
	array.size = 0;
	array.reserve_val = 0;
	return *this;
}

bool operator==(const DynamicArray& array1, const DynamicArray& array2) {
	if (array1.size != array2.size || array1.reserve_val != array2.reserve_val) return false;
	for (int i = 0; i < array1.size; ++i) {
		if (array1.array[i] != array2.array[i]) {
			return false;
		}
	}
	return true;
}

bool operator!=(const DynamicArray& array1, const DynamicArray& array2) {
	return !(array1 == array2);
}

bool operator<(const DynamicArray& array1, const DynamicArray& array2) {
	for (int i = 0; i < std::min(array1.size, array2.size); ++i) {
		if (array1.array[i] >= array2.array[i]) {
			return false;
		}
	}
	return array1.size < array2.size;
}

bool operator<=(const DynamicArray& array1, const DynamicArray& array2) {
	bool flag = true;
	for (int i = 0; i < std::min(array1.size, array2.size); ++i) {
		if (array1.array[i] != array2.array[i]) {
			flag = false;
			break;
		}
	}
	return array1 < array2 || flag;
}

bool operator>(const DynamicArray& array1, const DynamicArray& array2) {
	return !(array1 <= array2);
}

bool operator>=(const DynamicArray& array1, const DynamicArray& array2) {
	return !(array1 < array2);
}

DynamicArray& operator+(const DynamicArray& array1, const DynamicArray& array2) {
	DynamicArray* temp = new DynamicArray(array1.size + array2.size);
	for (int i = 0; i < temp->size; ++i) {
		if (i < array1.size) {
			temp->array[i] = array1.array[i];
		}
		else {
			temp->array[i] = array2.array[i - array1.size];
		}
	}
	return *temp;
}

std::ostream& operator<<(std::ostream& out, const DynamicArray& array) {
	out << array.size << " ";
	for (int i = 0; i < array.size; ++i) {
		out << array.array[i] << " ";
	}
	out << array.reserve_val;
	return out;
}

std::istream& operator>>(std::istream& in, DynamicArray& array) {
	in >> array.size;
	for (int i = 0; i < array.size; ++i) {
		in >> array.array[i];
	}
	in >> array.reserve_val;
	return in;
}
