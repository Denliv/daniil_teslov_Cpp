#pragma once
#include "AbstractIterator.h"
template <typename T>
class AbstractList {
public:
	virtual void put(const T& x, AbstractIterator<T>& iterator) = 0;
	virtual void deleteElem(AbstractIterator<T>& iterator) = 0;
	virtual AbstractIterator<T>& firstInstanceIterator(const T& x) = 0;
	virtual void makeEmpty() = 0;
	virtual bool isEmpty() = 0;
	virtual int length() = 0;
	virtual AbstractIterator<T>& headIterator() const = 0;
	virtual ~AbstractList() {}
};