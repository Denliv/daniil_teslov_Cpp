#pragma once
#include <iostream>
class DynamicArray {
private:
	int* array = nullptr;
	int size = 0;
	int reserve_val = 0;
public:
	DynamicArray();
	DynamicArray(int size);
	DynamicArray(int size, int n);
	DynamicArray(int size, int n, int reserve);
	DynamicArray(const DynamicArray& array);
	DynamicArray(DynamicArray&& array);
	~DynamicArray();
	int length();
	int& operator[] (int);
	void resize(int newSize);
	void reserve(int n);
	int capacity();
	void pushBack(int x);
	int popBack();
	DynamicArray& operator= (const DynamicArray& array);
	DynamicArray& operator= (DynamicArray&& array);
	friend bool operator== (const DynamicArray& array1, const DynamicArray& array2);
	friend bool operator!= (const DynamicArray& array1, const DynamicArray& array2);
	friend bool operator< (const DynamicArray& array1, const DynamicArray& array2);
	friend bool operator<= (const DynamicArray& array1, const DynamicArray& array2);
	friend bool operator> (const DynamicArray& array1, const DynamicArray& array2);
	friend bool operator>= (const DynamicArray& array1, const DynamicArray& array2);
	friend DynamicArray& operator+ (const DynamicArray& array1, const DynamicArray& array2);
	friend std::ostream& operator<< (std::ostream&, const DynamicArray&);
	friend std::istream& operator>> (std::istream&, DynamicArray&);
};

