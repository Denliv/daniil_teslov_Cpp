#include "pch.h"
#include "Box.h"
namespace Task0 {
	Box::Box() {
		this->length = 0;
		this->width = 0;
		this->height = 0;
		this->weight = 0.0;
		this->value = 0;
	}

	Box::Box(int length, int width, int height, double weight, int value) {
		this->length = length;
		this->width = width;
		this->height = height;
		this->weight = weight;
		this->value = value;
	}

	int Box::valueSum(Box arr[], int size) {
		int sum = 0;
		for (int i = 0; i < size; ++i) {
			sum += arr[i].value;
		}
		return sum;
	}

	bool Box::correctBoxes(Box arr[], int size, int number) {
		for (int i = 0; i < size; ++i) {
			if (arr[i].length > number || arr[i].width > number || arr[i].height > number) {
				return false;
			}
		}
		return true;
	}

	double Box::maxCertainBoxesWeight(Box arr[], int size, double maxV) {
		double maxWeight = 0;
		for (int i = 0; i < size; ++i) {
			if (arr[i].height * arr[i].width * arr[i].length <= maxV) {
				maxWeight += arr[i].weight;
			}
		}
		return maxWeight;
	}

	bool Box::boxesCanBeInserted(Box arr[], int size) {
		std::sort(arr, arr + size,
			[](const Box& a, const Box& b) {
				return a.height * a.length * a.width < b.height* b.length* b.width;
			}
		);
		for (int i = 0; i < size - 1; ++i) {
			if (arr[i].height > arr[i + 1].height
				|| arr[i].length > arr[i + 1].length
				|| arr[i].width > arr[i + 1].width) {
				return false;
			}
		}
		return true;
	}

	int Box::getLength() {
		return this->length;
	}

	int Box::getWidth() {
		return this->width;
	}

	int Box::getHeight() {
		return this->height;
	}

	double Box::getWeight() {
		return this->weight;
	}

	int Box::getValue() {
		return this->value;
	}

	void Box::setLength(int length) {
		if (length <= 0) length = 0;
		this->length = length;
	}

	void Box::setWidth(int width) {
		if (width <= 0) width = 0;
		this->width = width;
	}

	void Box::setHeight(int height) {
		if (height <= 0) height = 0;
		this->height = height;
	}

	void Box::setWeight(double weight) {
		if (weight <= 0) weight = 0;
		this->weight = weight;
	}

	void Box::setValue(int value) {
		if (value <= 0) value = 0;
		this->value = value;
	}

	bool operator== (Box box1, Box box2) {
		return box1.height == box2.height
			&& box1.length == box2.length
			&& box1.width == box2.width
			&& box1.weight == box2.weight
			&& box1.value == box2.value;
	}

	std::ostream& operator<< (std::ostream& out, const Box& box) {
		return out
			<< box.length << " "
			<< box.width << " "
			<< box.height << " "
			<< box.weight << " "
			<< box.value;
	}

	std::istream& operator>> (std::istream& in, Box& box) {
		return in >> box.length >> box.width >> box.height >> box.weight >> box.value;
	}
}
